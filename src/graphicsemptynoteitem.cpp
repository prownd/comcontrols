#include "graphicsemptynoteitem.h"
//#include "viewercontroler.h"
#include <QPainter>
#include <QCursor>
GraphicsEmptyNoteItem::GraphicsEmptyNoteItem(const QString &image, const QString &hoverImage,QGraphicsItem *parent) :
    QGraphicsItem(parent),
    _style(normal),
    _image(image),
    _hoverImage(hoverImage),
    _font("",9,QFont::Normal)
{
    setAcceptsHoverEvents(true);
    if (!_image.isEmpty())
        _pixmap.load(_image);
    if (!_hoverImage.isEmpty())
        _hoverPixmap.load(_hoverImage);
    _width = 100;
    _height = 100;
    _imgWidth = _pixmap.rect().width();
    _imgHeight = _pixmap.rect().height();

    _metrics = new QFontMetrics(_font);
}
QRectF GraphicsEmptyNoteItem::boundingRect() const
{
    return QRectF(0,0, _width, _height);
}
void GraphicsEmptyNoteItem::setText(const QString &firstLine, const QString &secondLine)
{
    _firstLine = firstLine;
    _secondLine = secondLine;
    update();
}
void GraphicsEmptyNoteItem::setSize(const int width, const int height)
{
    _width = width;
    _height = height;
    update();
}
void GraphicsEmptyNoteItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRect _imageRect = QRect((_width-_imgWidth)/2,0,_imgWidth, _imgHeight);
    this->setCursor(QCursor(Qt::PointingHandCursor));
    if(_style == normal)
    {
       painter->drawPixmap(_imageRect,_pixmap);
       painter->setPen(QPen(QColor("#cccccc")));
       painter->setFont(_font);
       QRect _firstLineRect = QRect((_width-_metrics->width(_firstLine))/2,_imgHeight+_metrics->height(),_metrics->width(_firstLine) + 1,_metrics->height());
       painter->drawText(_firstLineRect,_firstLine);
       this->setFont(QFont("",10,QFont::Bold));
       QRect _secondLineRect = QRect((_width-_metrics->width(_secondLine))/2,_imgHeight+2*_metrics->height(),_metrics->width(_firstLine),_metrics->height());
       painter->setFont(_font);
       painter->drawText(_secondLineRect, _secondLine);
       this->setFont(QFont("",9,QFont::Normal));

    }
    else if(_style == current_stay)
    {
        painter->drawPixmap(_imageRect,_hoverImage);
        painter->setPen(QPen(QColor("#19649f")));
        painter->setFont(_font);
        QRect _firstLineRect = QRect((_width-_metrics->width(_firstLine))/2,_imgHeight+_metrics->height(),_metrics->width(_firstLine) + 1,_metrics->height());
        painter->drawText(_firstLineRect,_firstLine);
        setFont(QFont("",10,QFont::Bold));
        QRect _secondLineRect = QRect((_width-_metrics->width(_secondLine))/2,_imgHeight+2*_metrics->height(),_metrics->width(_firstLine),_metrics->height());
        painter->setFont(_font);
        painter->drawText(_secondLineRect, _secondLine);
        this->setFont(QFont("",9,QFont::Normal));
    }
}
void GraphicsEmptyNoteItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    _style = GraphicsEmptyNoteItem::current_stay;
    update();

}
void GraphicsEmptyNoteItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _style = GraphicsEmptyNoteItem::normal;
    setFont(QFont("",9,QFont::Normal));
    update();
}
void GraphicsEmptyNoteItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit emptyNoteItemClicked();
}

void GraphicsEmptyNoteItem::setFont(const QFont &font)
{
    delete _metrics;
    _metrics = new QFontMetrics(font);
    _font = font;
}
