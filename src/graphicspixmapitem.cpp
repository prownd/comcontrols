#include "graphicspixmapitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <QPainterPath>

GraphicsMaskItem::GraphicsMaskItem(QGraphicsItem *parent)
    : QWidget(NULL, Qt::CustomizeWindowHint|Qt::FramelessWindowHint)
{
    _proxy = new QGraphicsProxyWidget(parent);
    _proxy->setWidget(this);

    setStyleSheet("background-color:rgba(0,0,0,35)");
}

//////////////////////////////////////////////////////////////////////////////////////
GraphicsPixmapItem::GraphicsPixmapItem(const int width, const int height, const QString &picPath, QGraphicsItem * parent)
    : QGraphicsPixmapItem(parent)
    , _width(width)
    , _height(height)
    , _picPath(picPath)
    , _color(0,0,0,35)
    , _hover(false)
{
    this->setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setAcceptDrops(true);

    if (!_picPath.isEmpty())
        _pixmap.load(_picPath);
}

QRectF GraphicsPixmapItem::boundingRect() const
{
    return QRectF(0,0,_width,_height);
}
QPainterPath GraphicsPixmapItem::shape() const
{
    QRectF rect = boundingRect();
    QPainterPath path;
    path.addRoundRect(rect, 1, 1);
    return path;
}
void GraphicsPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    painter->fillRect(QRectF(0,0,_width,_height), QBrush(_color));
    if (!_pixmap.isNull() && !_hover) {
        painter->drawPixmap(_pixmap.rect(),_pixmap);
    }
    else if(!_hover_pixmap.isNull() && _hover)
        painter->drawPixmap(_hover_pixmap.rect(),_hover_pixmap);
}

void GraphicsPixmapItem::setSize(const int width, const int height)
{
    _width = width;
    _height = height;
    if (!_pixmap.isNull())
        _pixmap = _pixmap.scaled(_width,_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    if (!_hover_pixmap.isNull())
        _hover_pixmap = _hover_pixmap.scaled(_width,_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

}

void GraphicsPixmapItem::setColor(const QColor &color)
{
    _color = color;
}
void GraphicsPixmapItem::setImage(const QString& normalPicPath, const QString& hoverPicPath)
{
    if (!normalPicPath.isEmpty())
        _pixmap.load(normalPicPath);
    if (!hoverPicPath.isEmpty())
        _hover_pixmap.load(hoverPicPath);
}
void GraphicsPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->ignore();
//    event->accept();
//    QGraphicsItem::mousePressEvent(event);
}
void GraphicsPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _hover = true;
    emit mouseHovered(true);
    update();
}
void GraphicsPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _hover = false;
    emit mouseHovered(false);
    update();
}
