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

#ifndef QT3D_QMATRIXTRANSFORM_H
#define QT3D_QMATRIXTRANSFORM_H

#include <Qt3DCore/qabstracttransform.h>
#include <Qt3DCore/qt3dcore_global.h>

#include <QMatrix4x4>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class QMatrixTransformPrivate;

class QT3DCORESHARED_EXPORT QMatrixTransform : public Qt3D::QAbstractTransform
{
    Q_OBJECT
    Q_PROPERTY(QMatrix4x4 matrix READ matrix WRITE setMatrix NOTIFY matrixChanged)
public:
    explicit QMatrixTransform(QNode *parent = 0);
    QMatrixTransform(const QMatrix4x4& m, QNode *parent = 0);

    QMatrix4x4 matrix() const;
    void setMatrix(const QMatrix4x4 &matrix);

    QMatrix4x4 transformMatrix() const Q_DECL_OVERRIDE;

Q_SIGNALS:
    void matrixChanged();

protected:
    Q_DECLARE_PRIVATE(QMatrixTransform)
    QMatrixTransform(QMatrixTransformPrivate &dd, QNode *parent = 0);
    QMatrixTransform *doClone() const Q_DECL_OVERRIDE;
};

} // namespace Qt3D

QT_END_NAMESPACE

#endif // QT3D_QMATRIXTRANSFORM_H
