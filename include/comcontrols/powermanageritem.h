#ifndef POWERMANAGERITEM_H
#define POWERMANAGERITEM_H
#include "lcontrols_global.h"
#include <QObject> 
#include <QGraphicsItem>
class GraphicsItemButton;
class QTimer;
class QListWidget;
class QGraphicsProxyWidget;
class LCONTROLSSHARED_EXPORT PowerManagerItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit PowerManagerItem(QGraphicsItem* parent = 0);
    void setSize(const int&width, const int&height);
    void setImage(const QString &image, const QString &hoverImage,
                  const QString &currentImage, const QString &disableImage,
                  const int &imgWidth , const int &imgHeight);
    void addItem(const QString&);
    void addItems(const QStringList&);
    int  itemCount();
    void clear();
    void setItemEnable(const int& count, const bool& able);
    void setMenuItemSize(const int& width, const int& height);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    bool eventFilter(QObject *obj, QEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void slotBtnClicked();
    void slotTimeOut();
    void slotFocusOut();
private:
    int _width;
    int _height;
    int _itemWidth;
    int _itemHeight;

    GraphicsItemButton*      _listBtn;
    QGraphicsProxyWidget*    _proxy;
    QListWidget*             _listWidget;
    bool                     _show;
    bool                     _buttonClicked;
    bool                     _hover;
    QTimer*                  _timer;
    QTimer*                  _timerForFocus;
}
;
#endif
