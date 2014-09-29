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

#ifndef QT3D_BULLETPHYSICS_QRIGIDBODY_H
#define QT3D_BULLETPHYSICS_QRIGIDBODY_H

#include <Qt3DBulletPhysics/qt3dbulletphysics_global.h>

#include <Qt3DCore/qcomponent.h>
#include <QtGui/qvector3d.h>

QT_BEGIN_NAMESPACE

namespace Qt3D {

class QNode;

namespace BulletPhysics {

class QRigidBodyPrivate;

class QT3DBULLETPHYSICSSHARED_EXPORT QRigidBody : public Qt3D::QComponent
{
    Q_OBJECT

    Q_PROPERTY(float mass READ mass WRITE setMass NOTIFY massChanged)
    Q_PROPERTY(QVector3D centerOfMass READ centerOfMass WRITE setCenterOfMass NOTIFY centerOfMassChanged)

public:
    explicit QRigidBody(Qt3D::QNode *parent = 0);

    void setMass(float mass);
    float mass() const;

    void setCenterOfMass(const QVector3D &centerOfMass);
    QVector3D centerOfMass() const;

Q_SIGNALS:
    void massChanged();
    void centerOfMassChanged();

protected:
    QRigidBody(QRigidBodyPrivate &dd, Qt3D::QNode *parent = 0);

private:
    Q_DECLARE_PRIVATE(QRigidBody)
    QRigidBody *doClone() const Q_DECL_OVERRIDE;
};

} // namespace BulletPhysics
} // namespace Qt3D

QT_END_NAMESPACE

#endif // QT3D_BULLETPHYSICS_QRIGIDBODY_H
