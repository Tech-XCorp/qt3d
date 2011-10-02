/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtQuick3D module of the Qt Toolkit.
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

#include <QtWidgets/QApplication>
#include <QtCore/QThread>

#include "photobrowser3dview.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(photobrowser3d);

    QApplication app(argc, argv);

    // for QSettings
    QCoreApplication::setOrganizationName("Nokia");
    QCoreApplication::setOrganizationDomain("nokia.com");
    QCoreApplication::setApplicationName("photobrowser3d");

    int result = 0;
    {
        PhotoBrowser3DView view;

        if (view.stereoType() != QGLView::RedCyanAnaglyph)
            view.camera()->setEyeSeparation(0.3f);
        QStringList args = QCoreApplication::arguments();
        int w_pos = args.indexOf("-width");
        int h_pos = args.indexOf("-height");
        if (w_pos >= 0 && h_pos >= 0)
        {
            bool ok = true;
            int w = args.at(w_pos + 1).toInt(&ok);
            if (!ok)
            {
                qWarning() << "Could not parse width argument:" << args;
                return 1;
            }
            int h = args.at(h_pos + 1).toInt(&ok);
            if (!ok)
            {
                qWarning() << "Could not parse height argument:" << args;
                return 1;
            }
            view.resize(w, h);
        }
        else
        {
            view.resize(800, 600);
        }
        view.show();

        result = app.exec();
    }
    return result;
}
