/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt3D module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import Qt 4.7
import Qt3D 1.0
import Qt3D.Shapes 1.0
import QtQuickTest 1.0

Viewport {
    id: viewport

    Sphere {
        id: sphere1
    }

    Sphere {
        id: sphere2
        radius: 3.5
        levelOfDetail: 2
        axis: Qt.YAxis
    }

    Sphere {
        id: sphere3
        radius: -3.5
        levelOfDetail: 23   // Valid, but clamped during drawing
        axis: Qt.XAxis
    }

    Sphere {
        id: sphere4
        property int radChanged: 0
        property int lodChanged: 0
        property int axChanged: 0
        onRadiusChanged: ++radChanged
        onLevelOfDetailChanged: ++lodChanged
        onAxisChanged: ++axChanged
    }

    TestCase {
        name: "Sphere"

        function test_defaults() {
            compare(sphere1.radius, 0.5, "radius");
            compare(sphere1.levelOfDetail, 5, "levelOfDetail");
            compare(sphere1.axis, Qt.ZAxis, "axis");
        }

        function test_properties() {
            compare(sphere2.radius, 3.5, "radius");
            compare(sphere2.levelOfDetail, 2, "levelOfDetail");
            compare(sphere2.axis, Qt.YAxis, "axis");
            compare(sphere3.radius, -3.5, "radius (B)");
            compare(sphere3.levelOfDetail, 10, "levelOfDetail (B)");
            compare(sphere3.axis, Qt.XAxis, "axis (B)");
        }

        function test_radiusChanged() {
            compare(sphere4.radius, 0.5, "radius");
            compare(sphere4.radChanged, 0, "changed 1");
            sphere4.radius = 3.5
            compare(sphere4.radChanged, 1, "changed 2");
            compare(sphere4.radius, 3.5, "radius modified");
            sphere4.radius = 3.5
            compare(sphere4.radChanged, 1, "changed 3");
        }

        function test_levelOfDetailChanged() {
            compare(sphere4.levelOfDetail, 5, "levelOfDetail");
            compare(sphere4.lodChanged, 0, "changed 1");
            sphere4.levelOfDetail = 2
            compare(sphere4.lodChanged, 1, "changed 2");
            compare(sphere4.levelOfDetail, 2, "levelOfDetail modified");
            sphere4.levelOfDetail = 2
            compare(sphere4.lodChanged, 1, "changed 3");
        }

        function test_axisChanged() {
            compare(sphere4.axis, Qt.ZAxis, "axis");
            compare(sphere4.axChanged, 0, "changed 1");
            sphere4.axis = Qt.YAxis
            compare(sphere4.axChanged, 1, "changed 2");
            compare(sphere4.axis, Qt.YAxis, "axis modified");
            sphere4.axis = Qt.YAxis
            compare(sphere4.axChanged, 1, "changed 3");
        }
    }
}
