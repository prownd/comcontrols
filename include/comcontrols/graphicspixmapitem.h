#ifndef GRAPHICSPIXMAPITEM_H
#define GRAPHICSPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QWidget>
#include "comcontrols_global.h"

class QGraphicsProxyWidget;
class LCONTROLSSHARED_EXPORT GraphicsMaskItem : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicsMaskItem(QGraphicsItem *parent = 0);

    QGraphicsProxyWidget* proxy() { return _proxy; }
    void mousePressEvent ( QMouseEvent * event ){}
    void mouseMoveEvent ( QMouseEvent * event ) {}

private:

    QGraphicsProxyWidget* _proxy;
};

///////////////////////////////////////////////////////////
class LCONTROLSSHARED_EXPORT GraphicsPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GraphicsPixmapItem(const int width, const int height, const QString &picPath, QGraphicsItem * parent = 0);


    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setSize(const int width, const int height);

    void setColor(const QColor &color);
    
    void setImage(const QString &, const QString &);

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void mouseHovered(const bool&);
private:

    int _width;
    int _height;
    QString _picPath;
    QColor _color;
    QPixmap _pixmap;
    QPixmap _hover_pixmap;
    bool    _hover;
};

#endif // GRAPHICSPIXMAPITEM_H
