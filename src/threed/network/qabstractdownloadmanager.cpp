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

/*!
    \class QAbstractDownloadManager
    \brief The QAbstractDownloadManager class provides a base class for asset data download capability.
    \since 4.8
    \ingroup qt3d
    \ingroup qt3d::network

    QDownloadManager encapsulates the functions needed for the downloading
    of asset data (eg. textures) from a network URL (eg. a website).

    The QAbstractDownloadManager provides only the framework for this, and
    should be extended/overidden by the user to provide a specific implementation.

    There is currently a single implementation using this base class: QDownloadManager, which
    provides for asynchronous data transfer using the standard Qt networking classes.
*/

/*!
    \fn QAbstractDownloadManager::QAbstractDownloadManager(QObject *parent)
    Constructs a new instance of the QDownloadManager and attach it
    to a \a parent QObject.
*/

/*!
    \fn QAbstractDownloadManager::beginDownload(QUrl url)
    Instructs the QDownloadManager to download the content specified
    in \a url.  This may be a texture, 3d model, or similar.

    A return value of true indicates that the network request was
    successfully queued for sending, while a return value of false
    indicates a problem with sending (possibly a poorly specified URL, or
    network failure).
*/

/*!
    \fn QAbstractDownloadManager::downloadComplete(QByteArray assetData)
    \internal
    This signal is emitted when the network request has been completed.

    The \a assetData transmitted by the signal contains the content which
    has been downloaded as a QByteArray.

    If this value is NULL then the download has failed.
*/
