#include "graphicstablecolumn.h"

#include <QPainter>
#include <QPen>

const int EDGE_WIDTH = 1;

GraphicsTableColumn::GraphicsTableColumn(QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , _width(0)
  , _height(0)
{
    _table_thead_bg.load(":/resources/images/table_thead_bg.png");
}

QRectF GraphicsTableColumn::boundingRect() const
{
    return QRectF(0,0, _width, _height);
}

void GraphicsTableColumn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    QPixmap topmap;
    topmap = _table_thead_bg;
    topmap.scaled(_width, _height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    painter->drawPixmap(QRect(0,0,_width, _height), topmap);

    //line
    QPen lightPen(QColor("#f5f6fa"));
    lightPen.setWidth(1);
    painter->setPen(lightPen);
    painter->drawLine(0,0, 0, _height);

    QPen pen(QColor("#dee0ea"));
    pen.setWidth(1);
    painter->setPen(pen);
    painter->drawLine(_width - EDGE_WIDTH, 0, _width - EDGE_WIDTH, _height);

    //draw text
    QFontMetrics metrics(painter->font());
    QPen textPen(QColor(25,100,159));
    painter->setPen(textPen);
    painter->drawText(QRect(10, (_height - metrics.height()) / 2, _width, _height) ,  _text);
}

void GraphicsTableColumn::setWidth(const int &width)
{
    _width = width;
    update();
}

void GraphicsTableColumn::setHeight(const int &height)
{
    _height = height;
    update();
}

void GraphicsTableColumn::setText(const QString &text)
{
    _text = text;
}

void GraphicsTableColumn::setImage(const QString &img)
{
    _table_thead_bg.load(img);
}
