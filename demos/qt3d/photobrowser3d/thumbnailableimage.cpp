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

#include "thumbnailableimage.h"
#include "qareaallocator.h"
#include "qgltexture2d.h"
#include "qglmaterial.h"
#include "qatlas.h"

#include <QUrl>

class ThumbnailableImagePrivate
{
public:
    ThumbnailableImagePrivate();
    ~ThumbnailableImagePrivate();

    ThumbnailableImagePrivate *clone() const
    {
        ThumbnailableImagePrivate *temp = new ThumbnailableImagePrivate;
        temp->thumbnailed = thumbnailed;
        temp->pending = pending;
        temp->url = url;
        temp->data = data;
        temp->tex = tex;
        temp->mat = mat;
        temp->frame = frame;
        temp->scale = scale;
        temp->indices = indices;
        return temp;
    }

    QBasicAtomicInt ref;

    bool thumbnailed;
    bool pending;
    QUrl url;
    QImage data;
    QGLTexture2D *tex;
    QGLMaterial *mat;
    QRect frame;
    qreal scale;
    QGL::IndexArray indices;
};

ThumbnailableImagePrivate::ThumbnailableImagePrivate()
    : thumbnailed(false)
    , pending(false)
    , tex(0)
    , mat(0)
    , scale(15.0f)
{
    ref = 0;
}

ThumbnailableImagePrivate::~ThumbnailableImagePrivate()
{
}

ThumbnailableImage::ThumbnailableImage()
    : d(0)
{
}

/*!
    Construct ThumbnailableImage as a copy of \a other
*/
ThumbnailableImage::ThumbnailableImage(const ThumbnailableImage &other)
    : d(other.d)
{
    if (d)
        d->ref.ref();
}

/*!
    Destroys this ThumbnailableImage recovering any resources.
*/
ThumbnailableImage::~ThumbnailableImage()
{
    if (d && !d->ref.deref())
        delete d;
}

/*!
    Assigns this ThumbnailableImage to be a copy of \a other.
*/
ThumbnailableImage &ThumbnailableImage::operator=(const ThumbnailableImage &other)
{
    if (d != other.d)
    {
        if (d && !d->ref.deref())
            delete d;
        d = other.d;
        if (d)
            d->ref.ref();
    }
    return *this;
}

void ThumbnailableImage::setThumbnailed(bool enable)
{
    detach();
    if (enable != d->thumbnailed && !d->data.isNull())
    {
        if (enable)
        {
            if (d->frame.isNull())
            {
                Q_ASSERT(!d->data.isNull());
                QSize sz = (QSizeF(d->data.size()) / d->scale).toSize();
                QAtlas *atlas = QAtlas::instance();
                d->frame = atlas->allocate(sz, d->data, d->indices);
                d->pending = true;
            }
        }
        if (!d->pending)
            d->thumbnailed = enable;
    }
}

bool ThumbnailableImage::isThumbnailed() const
{
    bool result = false;
    if (d)
    {
        if (d->pending)
        {
            QList<QAtlasEntry> queue = QAtlas::instance()->allocationQueue();
            int i = 0;
            for ( ; i < queue.count(); ++i)
                if (d->frame == queue.at(i).rect)
                    break;
            if (i == queue.count())
            {
                d->pending = false;
                d->thumbnailed = true;
            }
        }
        result = d->thumbnailed;
    }
    return result;
}

QImage ThumbnailableImage::data() const
{
    QImage result;
    if (d)
        result = d->data;
    return result;
}

void ThumbnailableImage::setData(QImage data)
{
    detach();
    d->data = data;
}

QUrl ThumbnailableImage::url() const
{
    QUrl result;
    if (d)
        result = d->url;
    return result;
}

void ThumbnailableImage::setUrl(const QUrl &url)
{
    detach();
    d->url = url;
}

QRectF ThumbnailableImage::frame() const
{
    QRectF result;
    if (d)
        result = d->frame;
    return result;
}

qreal ThumbnailableImage::scale() const
{
    qreal result = 0.0f;
    if (d)
        result = d->scale;
    return result;
}

void ThumbnailableImage::minimize()
{
    if (!d)
        return;
    detach();
    if (!isMinimized())
    {
        if (d->thumbnailed)
        {
            // If thumbnailed, I don't really need the full size image
            d->data = QImage();
        }
        else
        {
            // If not thumbnailed, I don't need the atlas resources
            QAtlas *atlas = QAtlas::instance();
            atlas->release(d->frame);
            d->frame = QRect();
        }
    }
}

bool ThumbnailableImage::isMinimized() const
{
    bool result = true;
    if (d)
        result = (d->thumbnailed) ? (d->data.isNull()) : (d->frame.isNull());
    return result;
}

void ThumbnailableImage::setIndices(const QGL::IndexArray &indices)
{
    detach();
    d->indices = indices;
}

QGL::IndexArray ThumbnailableImage::indices() const
{
    QGL::IndexArray result;
    if (d)
        result = d->indices;
    return result;
}

/*!
    \internal
    You know what this is for.  No user serviceable parts below here.
*/
void ThumbnailableImage::detach()
{
    if (!d) // lazy creation of data block
    {
        d = new ThumbnailableImagePrivate;
        d->ref.ref();
    }
    else
    {
        if (d->ref > 1)  // being shared, must detach
        {
            ThumbnailableImagePrivate *temp = d->clone();
            d->ref.deref();
            d = temp;
            d->ref.ref();
        }
    }
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, const ThumbnailableImage &image)
{
    dbg << "ThumbnailableImage" << image.url() << "size:" << image.data().size() <<
            "minimized:" << image.isMinimized() << "-- thumbnailed:" << image.isThumbnailed()
            << "-- null:" << image.isNull() << "-- image loaded:" << (!image.data().isNull())
               << "-- index count:" << image.indices().count();
    return dbg;
}
#endif
