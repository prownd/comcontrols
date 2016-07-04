#include "gifproxyitem.h"

#include <QLabel>
#include <QMovie>

GifProxyItem::GifProxyItem(const QString &gifPath, QGraphicsItem * parent)
    : QGraphicsProxyWidget(parent)
{
    _movieLabel = new QLabel;
    _movie = new QMovie(gifPath);
    _movieLabel->setMovie(_movie);
    _movie->start();

    setWidget(_movieLabel);
}

void GifProxyItem::setGeometry ( const QRectF & rect )
{
    _movieLabel->setGeometry(QRect(rect.left(), rect.top(), rect.width(), rect.height()));
    QGraphicsProxyWidget::setGeometry(rect);
}

void GifProxyItem::setGifPath(const QString &gifPath)
{
    _movie->setFileName(gifPath);
    _movie->stop();
    _movie->start();
}
