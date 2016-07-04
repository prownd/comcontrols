#include "graphicstextitem.h"

#include <QGraphicsProxyWidget>
#include <QPainter>


GraphicsTextItem::GraphicsTextItem(QGraphicsItem *parent)
    : _error(false)
{
    setContextMenuPolicy(Qt::NoContextMenu);
    _proxy = new QGraphicsProxyWidget(parent);
    _proxy->setWidget(this);
//    setAttribute(Qt::WA_TranslucentBackground);
     QPalette palette = this->palette();
  //   palette.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
     palette.setColor(QPalette::WindowText, QColor("#006699"));
     setPalette(palette);

     setStyleSheet("QLineEdit{border-width:0;border-style:outset;background-color: rgba(0,0,0,0);color:rgba(25,100,159)}");
}

void GraphicsTextItem::focusOutEvent ( QFocusEvent * event )
{
    QLineEdit::focusOutEvent(event);
    emit focusOut(this);
}

void GraphicsTextItem::paintEvent ( QPaintEvent * event)
{
    if (!isVisible())
        return;
    QLineEdit::paintEvent(event);
    QPainter painter(this);

    if (this->hasFocus()) {
        if (_error)
            painter.setPen(Qt::red);
        else
            painter.setPen(QPen(QColor(25,100,159)));
        painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
    }
}

void GraphicsTextItem::focusInEvent ( QFocusEvent * event )
{

    QLineEdit::focusInEvent(event);
    emit textChanged(this->text());
}
