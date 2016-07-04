#ifndef PAGENODESITEM_H
#define PAGENODESITEM_H

#include <QWidget>
#include <QGraphicsProxyWidget>

#include "comcontrols_global.h"

class CustomBtn;
class LCONTROLSSHARED_EXPORT PageNodesWidget: public QWidget
{
    Q_OBJECT
public:

    PageNodesWidget(QWidget* parent = 0);

    void update(const int &sum, const int &cur = 0);
    void setCurrent(const int &cur);
    int getCurrent() {return _current;}
    void setSum(const int &sum){_sum = sum;}
protected:

    void paintEvent ( QPaintEvent * event );
    void resizeEvent ( QResizeEvent * event );


signals:

    void choosePage(const int &page);

public slots:

    void clickNode(CustomBtn* node);
private:


    QList<CustomBtn*> _nodes;

    int _sum;
    int _current;
};

//////////////////////////////////////////////////////////////
//class GraphicsItemButton;
class LCONTROLSSHARED_EXPORT PageNodesItem :  public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    explicit PageNodesItem(QGraphicsItem *parent = 0);

    void update(const int &sum, const int &cur = 0);
    void setCurrent(const int &cur);
    int getCurrent();
    void setSum(const int &sum);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    
    void choosePage(const int &page);
    void hoverEnter(bool);
private:

    PageNodesWidget* _nodes;
};

#endif // PAGENODESITEM_H
