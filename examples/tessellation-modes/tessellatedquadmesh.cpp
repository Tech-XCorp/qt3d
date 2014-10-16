/****************************************************************************
**
** Copyright (C) 2014 Klaralvdalens Datakonsult AB (KDAB).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "tessellatedquadmesh.h"

#include <Qt3DRenderer/qattribute.h>
#include <Qt3DRenderer/qbuffer.h>
#include <Qt3DRenderer/qmeshdata.h>

TessellatedQuadMesh::TessellatedQuadMesh(Qt3D::QNode *parent)
    : Qt3D::QAbstractMesh(parent)
{
}

class TessellatedQuadMeshFunctor : public Qt3D::QAbstractMeshFunctor
{
public:
    TessellatedQuadMeshFunctor() {}

    Qt3D::QAbstractMeshDataPtr operator ()() Q_DECL_OVERRIDE
    {
        const float positionData[] = {
            -0.8f, -0.8f, 0.0f,
             0.8f, -0.8f, 0.0f,
             0.8f,  0.8f, 0.0f,
            -0.8f,  0.8f, 0.0f
        };

        const int nVerts = 4;
        const int size = nVerts * 3 * sizeof(float);
        QByteArray positionBytes;
        positionBytes.resize(size);
        memcpy(positionBytes.data(), positionData, size);

        Qt3D::BufferPtr vertexBuffer(new Qt3D::Buffer(QOpenGLBuffer::VertexBuffer));
        vertexBuffer->setUsage(QOpenGLBuffer::StaticDraw);
        vertexBuffer->setData(positionBytes);

        Qt3D::QMeshDataPtr mesh(new Qt3D::QMeshData(GL_PATCHES));
        mesh->addAttribute(Qt3D::QAbstractMeshData::defaultPositionAttributeName(),
                           Qt3D::AttributePtr(new Qt3D::Attribute(vertexBuffer, GL_FLOAT_VEC3, nVerts)));
        mesh->setVerticesPerPatch(4);
        return mesh;
    }

    bool operator ==(const Qt3D::QAbstractMeshFunctor &other) const
    {
        const TessellatedQuadMeshFunctor *otherFunctor = dynamic_cast<const TessellatedQuadMeshFunctor *>(&other);
        if (otherFunctor != Q_NULLPTR)
            return true;
        return false;
    }
};

Qt3D::QAbstractMeshFunctorPtr TessellatedQuadMesh::meshFunctor() const
{
    return Qt3D::QAbstractMeshFunctorPtr(new TessellatedQuadMeshFunctor);
}
