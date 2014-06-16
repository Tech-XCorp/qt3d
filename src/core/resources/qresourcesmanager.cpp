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

/*!
 * \class QAbstractResourcesManager
 *
 * \brief The QAbstractResourcesManager allocates memory for resources that can be referenced by a
 * QHandle.
 *
 * Using a QHandleManager for handles management, the QAbstractResourcesManager responsibility lies
 * in providing memory for a resource and offering ways to interact with the resource through
 * the QHandle.
 *
 * Using the QHandle obtained when acquiring a resource, the resource can be retrieved and
 * released when not needed any longer.
 *
 * Internally, memory can be reorganized for best performances while being transparent to the user.
 * QAbstractResourcesManager cannot be instanced directly. You should instanciate one of its subclasses
 * which implements a specific memory allocation scheme.
 *
 * \since 5.3
 * \namespace Qt3D
 */

/*!
 *
 * \class QArrayResourcesManager
 *
 * \brief Subclass of QAbstractResourcesManager which allocates memory in a contiguous space trying to
 * minimize fragmentation and cache misses.
 *
 * Once the maximum number of entities reached, no more allocations can be made until some resources are
 * released
 *
 * \since 5.3
 * \namespace Qt3D
 * \sa QAbstractResourcesManager
 * \sa QListResourcesManager
 */

/*!
 *
 * \class QListResourcesManager
 *
 * \brief Subclass of QAbstractResourcesManager which allocates resources in a list.
 *
 * It is best to use it when you don't need to iterate over an entire set of resources, in which
 * case QArrayResourcesManager is faster. It can store a non predefined amount of resources, though
 * there might not be enough handles at some point, depending on the INDEXBITS used.
 * It's main use case is to manage resources that are accessed in an independent manner from other
 * resources of the same type.
 *
 * \since 5.3
 * \namespace Qt3D
 * \sa QAbstractResourcesManager
 * \sa QArrayResourcesManager
 */