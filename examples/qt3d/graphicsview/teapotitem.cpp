/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt3D examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "teapotitem.h"
#include "qglpainter.h"
#include "qplane3d.h"
#include "qtriangle3d.h"
#include <QtCore/qnumeric.h>

TeapotItem::TeapotItem(QGraphicsItem *parent)
    : ModelItem(parent)
{
    QGLBuilder builder;
    builder.newSection(QGL::Faceted);
    builder << teapot;
    teapotNode = builder.finalizedSceneNode();
}

TeapotItem::~TeapotItem()
{
    delete teapotNode;
}

void TeapotItem::paintGL(QGLPainter *painter)
{
    GLuint textureId = this->textureId();
    if (textureId) {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        painter->setFaceColor(QGL::AllFaces, QColor(0, 0, 0, 200));
        painter->setStandardEffect(QGL::LitDecalTexture2D);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (painter->isFixedFunction())
            glEnable(GL_TEXTURE_2D);
        glCullFace(GL_FRONT);
        glEnable(GL_CULL_FACE);
        teapotNode->draw(painter);
        glCullFace(GL_BACK);
        teapotNode->draw(painter);
        glDisable(GL_CULL_FACE);
        glBindTexture(GL_TEXTURE_2D, 0);
        if (painter->isFixedFunction())
            glDisable(GL_TEXTURE_2D);
    } else {
        painter->setStandardEffect(QGL::LitMaterial);
        teapotNode->draw(painter);
    }
}

QPointF TeapotItem::intersection(const QRay3D &ray, int *actualFace) const
{
    QVector2D tc;
    QGLBezierPatches patches = teapot.transformed(camera()->modelViewMatrix());
    if (pressedFace() == -1) {
        // Intersect with the whole teapot.
        qreal t = patches.intersection(ray, &tc, actualFace);
        if (!qIsNaN(t))
            return QPointF(tc.x(), tc.y());
    } else {
        // Only intersect with the patch that was pressed previously.
        QGLBezierPatches subpatches;
        subpatches.setPositions
            (patches.positions().mid(pressedFace() * 16, 16));
        qreal t = subpatches.intersection(ray, &tc);
        if (!qIsNaN(t)) {
            *actualFace = pressedFace();
            return QPointF(tc.x(), tc.y());
        }

        // The mouse has moved outside the boundary of the patch.
        // Use the plane containing the patch to extend the hit
        // area out to infinity.
        QTriangle3D triangle(subpatches.positions()[0],
                             subpatches.positions()[3],
                             subpatches.positions()[12]);
        t = triangle.plane().intersection(ray);
        if (!qIsNaN(t)) {
            *actualFace = pressedFace();
            QVector2D uv = triangle.uv(ray.point(t));
            QVector2D tc1(0, 0);
            QVector2D tc2(1, 0);
            QVector2D tc3(0, 1);
            QVector2D tc =
                uv.x() * tc1 + uv.y() * tc2 + (1 - uv.x() - uv.y()) * tc3;
            return QPointF(tc.x(), tc.y());
        }
    }
    *actualFace = -1;
    return QPointF();
}
