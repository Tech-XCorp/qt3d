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

import QtQuick 1.0
import Qt3D 1.0
import Qt3D.Shapes 1.0

// QTBUG-17408
Item {
    id: screen
    width: aTestCase.defaultWidth * 3
    height: aTestCase.defaultHeight * 4

    Flow {
        anchors.fill: parent
        TranslationVectorTestCase {
            id: aTestCase
            text: "X Translation\n(Left to Right)"
            translationVectorA: Qt.vector3d(-4,1,1)
            translationVectorB: Qt.vector3d(4,1,1)
        }

        TranslationVectorTestCase {
            text: "Y Translation\n(Bottom to Top)"
            translationVectorA: Qt.vector3d(1,-4,1)
            translationVectorB: Qt.vector3d(1,4,1)
        }

        TranslationVectorTestCase {
            text: "Z Translation\n(Back to Front)"
            translationVectorA: Qt.vector3d(1,1,-4)
            translationVectorB: Qt.vector3d(1,1,4)
        }

        TranslationVectorTestCase {
            text: "-X Translation\n(Right to Left)"
            translationVectorA: Qt.vector3d(4,1,1)
            translationVectorB: Qt.vector3d(-4,1,1)
        }

        TranslationVectorTestCase {
            text: "-Y Translation\n(Top to Bottom)"
            translationVectorA: Qt.vector3d(1,4,1)
            translationVectorB: Qt.vector3d(1,-4,1)
        }

        TranslationVectorTestCase {
            text: "-Z Translation\n(Front to Back)"
            translationVectorA: Qt.vector3d(1,1,4)
            translationVectorB: Qt.vector3d(1,1,-4)
        }

        TranslationVectorTestCase {
            text: "Sequential Translation in X,Y,Z\n(Previous 6 in order)"
            id: sequentialTestCase
            property real itemX:-4;
            property real itemY:-4;
            property real itemZ:-4;
            itemPosition: Qt.vector3d(itemX,itemY,itemZ)
            //            itemPosition: Qt.vector3d(itemX,4,4)
            SequentialAnimation {
                loops: Animation.Infinite
                running: true
                PropertyAnimation {
                    target: sequentialTestCase; property: "itemX";
                    to: 4; duration: 1000
                }
                PropertyAnimation {
                    target: sequentialTestCase; property: "itemY";
                    to: 4; duration: 1000
                }
                PropertyAnimation {
                    target: sequentialTestCase; property: "itemZ";
                    to: 4; duration: 1000
                }
                PropertyAnimation {
                    target: sequentialTestCase; property: "itemX";
                    to: -4; duration: 1000
                }
                PropertyAnimation {
                    target: sequentialTestCase; property: "itemY";
                    to: -4; duration: 1000
                }
                PropertyAnimation {
                    target: sequentialTestCase; property: "itemZ";
                    to: -4; duration: 1000
                }
            }
        }

        TranslationTestCase {
            text: "Translation in X,Y,Z properties\n(Smooth Animation)"
            id: attributeTestCase
            itemX: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 3.0);
            itemY: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 5.0);
            itemZ: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 7.0);
            animationDuration: 15000
        }

        TranslationVectorTestCase {
            text: "Translation in Qt.Vector3d(X,Y,Z)\n(Smooth Animation)"
            id: combinedVectorTestCase
            property real itemX: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 3.0);
            property real itemY: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 5.0);
            property real itemZ: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 7.0);
            itemPosition: Qt.vector3d(itemX,itemY,itemZ)
            animationDuration: 15000
        }

        AxesVsVectorTestCase {
            text: "Last two overlaid\n(Should look like one teapot)"
            id: axesVsVectorTestCase
            itemX: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 3.0);
            itemY: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 5.0);
            itemZ: 4 * Math.sin(animationFactor * Math.PI * 2.0 * 7.0);
            itemPosition: Qt.vector3d(itemX,itemY,itemZ)
            animationDuration: 15000
        }
    }
}
