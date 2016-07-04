#ifndef GRAPHICSTABLECOLUMN_H
#define GRAPHICSTABLECOLUMN_H

#include <QGraphicsItem>
#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT GraphicsTableColumn : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    explicit GraphicsTableColumn(QGraphicsItem *parent = 0);

    void setImage(const QString &img);
    void setWidth(const int &width);
    void setHeight(const int &height);

    void setText(const QString &text);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

signals:
    
public slots:
    
private:

    int _width;
    int _height;
    QPixmap _table_thead_bg;
    QString _text;
};

#endif // GRAPHICSTABLECOLUMN_H
