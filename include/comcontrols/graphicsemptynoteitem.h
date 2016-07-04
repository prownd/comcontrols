#ifndef GRAPHICSEMPTYNOTEITEM_H
#define GRAPHICSEMPTYNOTEITEM_H

#include <QGraphicsItem>
#include <QFontMetrics>
#include <QFont>
#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT GraphicsEmptyNoteItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum style {
        current_stay, normal
    };
    explicit GraphicsEmptyNoteItem(const QString &image,const QString &hoverImage,QGraphicsItem *parent = 0);
    void setText(const QString &firstLine, const QString &secondLine);
    void setSize(const int width, const int height);
    void setFont(const QFont &);
    QRectF boundingRect() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    
signals:
    void emptyNoteItemClicked();
    
public slots:
private:
    int _width;
    int _height;
    int _imgWidth;
    int _imgHeight;
    style _style;
    QString _firstLine;
    QString _secondLine;
    QString _image;
    QString _hoverImage;
    QPixmap _pixmap;
    QPixmap _hoverPixmap;

    QFontMetrics* _metrics;
    QFont _font;
    
};

#endif // GRAPHICSEMPTYNOTEITEM_H
