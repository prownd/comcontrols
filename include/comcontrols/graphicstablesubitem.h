#ifndef GRAPHICSTABLESUBITEM_H
#define GRAPHICSTABLESUBITEM_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>
#include "graphicstableitem.h"
#include <QColor>

#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT GraphicsTextItemSized : public QGraphicsTextItem
{

public:

    GraphicsTextItemSized(QGraphicsItem* parent = 0);

    GraphicsTextItemSized(const QString& text, QGraphicsItem* parent = 0);


    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event )
    {
        event->ignore();
    }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);


    void   forcePos(qreal x1, qreal y1, qreal x2, qreal y2);

private:

    QRectF forcedSize;

};


class QGraphicsTextItem;
class LCONTROLSSHARED_EXPORT GraphicsTableSubItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit GraphicsTableSubItem(const int &wid, const int hei,
                                  QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setColor(const QColor &color);
    void setSelectedColor(const QColor &color);
    void setHover(const bool &hovered);


    void setText(const QString &text, const GraphicsTableItem::row_item_str_style &style = GraphicsTableItem::normalString,
                         const QString &icon = "",
                 const GraphicsTableItem::row_item_icon &icon_style = GraphicsTableItem::left,
                 const GraphicsTableItem::row_item_icon_show &icon_show = GraphicsTableItem::allshow);

    void setRowItemSelHtml(const QString &val);

    void contextMenuEvent ( QGraphicsSceneContextMenuEvent * event )
    {
        event->ignore();
    }

    void addIcon(const QString &icon, const GraphicsTableItem::row_item_icon &icon_style,
                    const GraphicsTableItem::row_item_icon_show &icon_show );

    void setIcon(const int &iconIndex, const QString &icon, const GraphicsTableItem::row_item_icon &icon_style,
                    const GraphicsTableItem::row_item_icon_show &icon_show );

    void removeIcon( const int &iconIndex);
    void setCustomGridStyle(const Qt::PenStyle& style = Qt::SolidLine, const QColor& leftcolor = QColor("#f5f6fa"),
                            const QColor& topcolor = QColor("#f5f6fa"),
                            const QColor& rightcolor = QColor("#dee0ea"),
                            const QColor& bottomcolor = QColor("#dee0ea"));
    void setCustomSelectedGridStyle(const Qt::PenStyle& style = Qt::SolidLine, const QColor& leftcolor = QColor("#1275c3"),
                            const QColor& topcolor = QColor("#f5f6fa"),
                            const QColor& rightcolor = QColor("#1275c3"),
                            const QColor& bottomcolor = QColor("#dee0ea"));
    void setDefaultTextColor(const QColor& defaultTextColor);
    void setSelectTextColor(const QColor& selectTextColor);
    void addSubItem(QGraphicsItem* item, QPoint pos);
    void setSubItemVisible(const int &index, const bool &vis);
    QGraphicsItem* getLowSubItem(const int &itemIndex);
    void setToolTipText(const QString &tips);
protected:

    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );

 //   void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
 //   void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

signals:
    
    void hoverEnter();
    void hoverLeave();

public slots:
    
private:

    struct icon_node{

        GraphicsTableItem::row_item_icon _icon_style;
        GraphicsTableItem::row_item_icon_show _icon_show;
        QPixmap _icon;
    };

    QList<icon_node> _icons;
    QList<QGraphicsItem*> _subItems;

    int _width;
    int _height;

    QColor _color;
    QColor _selected_color;

    bool _hovered;
    Qt::PenStyle _penStyle;
    QColor _gridLeftColor;
    QColor _gridTopColor;
    QColor _gridRightColor;
    QColor _gridBottomColor;
    QColor _gridSelectLeftColor;
    QColor _gridSelectTopColor;
    QColor _gridSelectRightColor;
    QColor _gridSelectBottomColor;
    QColor _selectTextColor;
    QColor _defaultTextColor;
    GraphicsTableItem::row_item_str_style _strStyle;
    GraphicsTextItemSized* _text;

    QString _html;
    QString _selectedHtml;

    QGraphicsItem* _item;

};

#endif // GRAPHICSTABLESUBITEM_H
