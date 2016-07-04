#ifndef GRAPHICSTABLEROW_H
#define GRAPHICSTABLEROW_H

#include <QGraphicsItem>
#include "graphicstableitem.h"

#include "comcontrols_global.h"

class QTimeLine;
class QGraphicsItemAnimation;
class QMenu;
class QGraphicsProxyWidget;
class GraphicsTableSubItem;
class LCONTROLSSHARED_EXPORT GraphicsTableRow : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:


    explicit GraphicsTableRow(const int &id, const int &itemSum, QMap<int ,int > itemWidth, const int &height,
                              const GraphicsTableItem::select_style &style = GraphicsTableItem::normal,
                              QGraphicsItem *parent = 0);

    ~GraphicsTableRow();

    void setText(const int &itemIndex,
                 const QString &text,
                 const GraphicsTableItem::row_item_str_style &style = GraphicsTableItem::normalString,
                 const QString &icon = "",
                 const GraphicsTableItem::row_item_icon &icon_style = GraphicsTableItem::left,
                 const GraphicsTableItem::row_item_icon_show &icon_show = GraphicsTableItem::allshow);

    void setRowItemSelHtml(const int &itemIndex, const QString &val);
    void setColor(const QColor &color);
    void setSelectedColor(const QColor &color);


    void addItemIcon(const int &itemIndex,
                    const QString &icon = "", const GraphicsTableItem::row_item_icon &icon_style = GraphicsTableItem::left,
                    const GraphicsTableItem::row_item_icon_show &icon_show = GraphicsTableItem::allshow);

    void setItemIcon(const int &itemIndex, const int &iconIndex,
                    const QString &icon = "", const GraphicsTableItem::row_item_icon &icon_style = GraphicsTableItem::left,
                    const GraphicsTableItem::row_item_icon_show &icon_show = GraphicsTableItem::allshow);
    void setCustomGridStyle(const Qt::PenStyle& style = Qt::SolidLine,
                            const QColor& leftcolor = QColor("#f5f6fa"),
                            const QColor& topcolor = QColor("#f5f6fa"),
                            const QColor& rightcolor = QColor("#dee0ea"),
                            const QColor& bottomcolor = QColor("#dee0ea"));
    void setCustomSelectedGridStyle(const Qt::PenStyle& style = Qt::SolidLine,
                            const QColor& leftcolor = QColor("#f5f6fa"),
                            const QColor& topcolor = QColor("#f5f6fa"),
                            const QColor& rightcolor = QColor("#dee0ea"),
                            const QColor& bottomcolor = QColor("#dee0ea"));
    void setDefaultTextColor(const QColor& defaultTextColor);
    void setSelectTextColor(const QColor& selectTextColor);
    void removeItemIcon(const int &itemIndex, const int &iconIndex);

    void setData(void* data);
    void* data();

    int id();
    void setID(const int &id);


    void setMenu(TableMenu* menu);


    void animationMove(const QPointF &end);

    void setEnable(const bool &enable){ _enable = enable;}
    bool isHovered(){return _isHovered;}

    void addLowSubItem(const int &index, QGraphicsItem* subItem, QPoint pos);
    void setLowSubItemVisible(const int &index, const int &subItem, const bool &vis);
    QGraphicsItem* getLowSubItem(const int &subIndex, const int &itemIndex);
    void setToolTipText(const int &itemIndex,const QString &tips);
public:

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

signals:
    
    void updateData(GraphicsTableRow* row);
    void clicked(GraphicsTableRow* row);
    void rClicked(GraphicsTableRow* row);


    void hoverEnter(GraphicsTableRow* row);
    void hoverLeave(GraphicsTableRow* row);

public slots:

    void updateData() { emit updateData(this); }

protected:

    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event );
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:

    void hoverLeave();

private:

    int _height;
    int _width;

    QList<GraphicsTableSubItem*> _items;
    GraphicsTableItem::select_style _style;

    void* _data;
    int _id;

    TableMenu* _menu;
    bool _menuPopup;
    bool _isHovered;


    QTimeLine *_timer;
    QGraphicsItemAnimation* _ani;

    bool _enable;
};

#endif // GRAPHICSTABLEROW_H
