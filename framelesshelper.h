/*
 * MIT License
 *
 * Copyright (C) 2020 by wangwenx190 (Yuhang Zhao)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <QHash>
#include <QObject>
#include <QPointer>
#include <QRect>

QT_BEGIN_NAMESPACE
QT_FORWARD_DECLARE_CLASS(QWindow)
QT_END_NAMESPACE

class FramelessHelper : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FramelessHelper)

public:
    explicit FramelessHelper(QObject *parent = nullptr);
    ~FramelessHelper() override = default;

    static void updateQtFrame(QWindow *window, const int titleBarHeight);
    static void moveWindowToDesktopCenter(QObject *obj);

    int getBorderWidth() const;
    void setBorderWidth(const int val);

    int getBorderHeight() const;
    void setBorderHeight(const int val);

    int getTitleBarHeight() const;
    void setTitleBarHeight(const int val);

    QList<QRect> getIgnoreAreas(QObject *obj) const;
    void setIgnoreAreas(QObject *obj, const QList<QRect> &val);
    void addIgnoreArea(QObject *obj, const QRect &val);
    void clearIgnoreAreas(QObject *obj);

    QList<QRect> getDraggableAreas(QObject *obj) const;
    void setDraggableAreas(QObject *obj, const QList<QRect> &val);
    void addDraggableArea(QObject *obj, const QRect &val);
    void clearDraggableAreas(QObject *obj);

    QList<QObject *> getIgnoreObjects(QObject *obj) const;
    void setIgnoreObjects(QObject *obj, const QList<QObject *> &val);
    void addIgnoreObject(QObject *obj, QObject *val);
    void clearIgnoreObjects(QObject *obj);

    QList<QObject *> getDraggableObjects(QObject *obj) const;
    void setDraggableObjects(QObject *obj, const QList<QObject *> &val);
    void addDraggableObject(QObject *obj, QObject *val);
    void clearDraggableObjects(QObject *obj);

    bool getResizable(QObject *obj) const;
    void setResizable(QObject *obj, const bool val);

    bool getTitleBarEnabled(QObject *obj) const;
    void setTitleBarEnabled(QObject *obj, const bool val);

    void removeWindowFrame(QObject *obj);

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    // ### TODO: The default border width and height on Windows is 8 pixels if
    // the scale factor is 1.0. Don't know how to acquire these values on UNIX
    // platforms through native API.
    int m_borderWidth = 8, m_borderHeight = 8, m_titleBarHeight = 30;
    QHash<QObject *, QList<QRect>> m_ignoreAreas = {}, m_draggableAreas = {};
    QHash<QObject *, QList<QPointer<QObject>>> m_ignoreObjects = {}, m_draggableObjects = {};
    QHash<QObject *, bool> m_fixedSize = {}, m_disableTitleBar = {};
};
