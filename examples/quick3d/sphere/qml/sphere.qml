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

import QtQuick 1.0
import Qt3D 1.0
import Qt3D.Shapes 1.0

Viewport {
    width: 800; height: 480

    Item3D {
        effect: Effect { color: "#aaca00" }

        Sphere {
            radius: 0.5
            x: -2.5
            y: 0.6
            levelOfDetail: 1

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: -1.25
            y: 0.6
            levelOfDetail: 2

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: 0
            y: 0.6
            levelOfDetail: 3

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: 1.25
            y: 0.6
            levelOfDetail: 4

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: 2.5
            y: 0.6
            levelOfDetail: 5

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: -2.5
            y: -0.6
            levelOfDetail: 6

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: -1.25
            y: -0.6
            levelOfDetail: 7

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: 0
            y: -0.6
            levelOfDetail: 8

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: 1.25
            y: -0.6
            levelOfDetail: 9

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }

        Sphere {
            radius: 0.5
            x: 2.5
            y: -0.6
            levelOfDetail: 10

            transform: Rotation3D {
                angle: 45
                axis: Qt.vector3d(1, -1, 1)
            }
        }
    }
}
