#ifndef GIFPROXYITEM_H
#define GIFPROXYITEM_H

#include <QGraphicsProxyWidget>
#include "comcontrols_global.h"

class QLabel;
class LCONTROLSSHARED_EXPORT GifProxyItem : public QGraphicsProxyWidget
{
public:
    GifProxyItem(const QString &gifPath, QGraphicsItem * parent = 0);

    void setGeometry ( const QRectF & rect );

    void setGifPath(const QString &gifPath);

private:


    QLabel* _movieLabel;
    QMovie* _movie;
};

#endif // GIFPROXYITEM_H
