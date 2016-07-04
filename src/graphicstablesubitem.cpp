#include "graphicstablesubitem.h"

#include <QPainter>
#include <QDebug>
const int EDGE_WIDTH = 1;

GraphicsTextItemSized::GraphicsTextItemSized(QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
{}

GraphicsTextItemSized::GraphicsTextItemSized(const QString& text, QGraphicsItem* parent)
    : QGraphicsTextItem(text, parent)
{}

QRectF GraphicsTextItemSized::boundingRect() const
{
    QRectF rr = QGraphicsTextItem::boundingRect();
    return QRectF(rr.left(), rr.top(), forcedSize.width(), rr.height());
}

void GraphicsTextItemSized::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    QGraphicsTextItem::paint(painter, option,widget);
 //   painter->fillRect(boundingRect(), Qt::black);
}

void GraphicsTextItemSized::forcePos(qreal x1, qreal y1, qreal width, qreal height)
{
    forcedSize.setCoords(0,0,width,height);
    setPos(x1,y1);
}


GraphicsTableSubItem::GraphicsTableSubItem(const int &wid, const int hei, QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , _width(wid)
  , _height(hei)
  , _hovered(false)
  , _item(NULL)
  , _penStyle(Qt::SolidLine)
  , _selected_color(QColor("#1275c3"))
  , _selectTextColor(QColor("#ffffff"))
  , _defaultTextColor(QColor(25,100,159))
  , _gridLeftColor(QColor("#f5f6fa"))
  , _gridTopColor(QColor("#f5f6fa"))
  , _gridRightColor(QColor("#dee0ea"))
  , _gridBottomColor(QColor("#dee0ea"))
  , _gridSelectLeftColor(QColor("#1275c3"))
  , _gridSelectTopColor(QColor("#f5f6fa"))
  , _gridSelectRightColor(QColor("#1275c3"))
  , _gridSelectBottomColor(QColor("#dee0ea"))
{
//    this->setAcceptHoverEvents(true);
    _text = new GraphicsTextItemSized(this);
    _text->adjustSize();
//    _text->setTextWidth(200);
    _text->setDefaultTextColor(QColor(25,100,159));
}

QRectF GraphicsTableSubItem::boundingRect() const
{
    return QRectF(0,0, _width, _height);
}

void GraphicsTableSubItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    //draw rangel
    if (_hovered) {
        painter->fillRect( QRectF(EDGE_WIDTH, EDGE_WIDTH, _width - 2*EDGE_WIDTH, _height - 2*EDGE_WIDTH), _selected_color);
        painter->fillRect(QRectF(_width - EDGE_WIDTH , EDGE_WIDTH, EDGE_WIDTH, _height - 2*EDGE_WIDTH), _gridSelectRightColor);
        painter->fillRect(QRectF(0,EDGE_WIDTH, EDGE_WIDTH, _height - 2*EDGE_WIDTH), _gridSelectLeftColor);
        painter->fillRect(QRectF(0, _height - EDGE_WIDTH, _width, EDGE_WIDTH), _gridSelectBottomColor);
        painter->fillRect(QRectF(0,0,_width,EDGE_WIDTH), _gridSelectTopColor);
    }
    else {
        painter->fillRect( QRectF(EDGE_WIDTH, EDGE_WIDTH, _width - 2*EDGE_WIDTH, _height - 2*EDGE_WIDTH), _color);
    //draw right
    //    QPen rightpen(_gridRightColor);
    //    painter->setPen(rightpen);
        painter->fillRect(QRectF(_width - EDGE_WIDTH , EDGE_WIDTH, EDGE_WIDTH, _height - 2*EDGE_WIDTH), _gridRightColor);
    //draw left
    //    QPen leftPen(_gridLeftColor, 1, _penStyle, Qt::RoundCap, Qt::RoundJoin);
    //    painter->setPen(leftPen);
        painter->fillRect(QRectF(0,EDGE_WIDTH, EDGE_WIDTH, _height - 2*EDGE_WIDTH), _gridLeftColor);

    //draw bottom
    //    QPen bottompen(_gridBottomColor);
    //    painter->setPen(bottompen);
        painter->fillRect(QRectF(0, _height - EDGE_WIDTH, _width , EDGE_WIDTH), _gridBottomColor);
    //draw top
    //    QPen topPen(_gridTopColor, 1, _penStyle, Qt::RoundCap, Qt::RoundJoin);
    //    painter->setPen(topPen);
        painter->fillRect(QRectF(0,0,_width ,EDGE_WIDTH), _gridTopColor);
    }

    //draw icon
    int textLeft = 0;
    int iconRight = _width;

    for (int i = 0;i < _icons.size();i++) {
        icon_node icon = _icons.at(i);

    //    pixmap.load(icon._icon);
        if (icon._icon_show == GraphicsTableItem::allshow || (icon._icon_show == GraphicsTableItem::selectshow && _hovered)) {
            QRect rPix = icon._icon.rect();
            rPix.moveTop((_height - rPix.height()) /2 );
            if (icon._icon_style == GraphicsTableItem::left) {
                rPix.moveLeft(textLeft + 5);
                if (!icon._icon.isNull())
                    textLeft += rPix.right();
            }
            else if (icon._icon_style == GraphicsTableItem::right) {
                iconRight -= (rPix.width() + 5);
                rPix.setLeft(iconRight);
            }
            else
                rPix.setLeft((_width - rPix.width())/2);
            painter->drawPixmap(rPix, icon._icon);
        }
    }

    //text
    //ĿǰĬ��gifͼ��ʾ�����ࡣ
    for (int i = 0;i < _subItems.size();i++) {
        QGraphicsItem* item = _subItems.at(i);
        if (item->isVisible() && textLeft < item->boundingRect().right())
            textLeft =  item->boundingRect().right();
    }
    textLeft += 5;
//    _text->setPos(textLeft, _height/2 - _text->boundingRect().height() / 2);

    QFontMetrics metrics(_text->font());
    int textWidth = iconRight - textLeft;
    _text->forcePos(textLeft,_height/2  - _text->boundingRect().height() / 2, textWidth,  metrics.height());
}

void GraphicsTableSubItem::setColor(const QColor &color)
{
    _color = color;
}
void GraphicsTableSubItem::setSelectedColor(const QColor &color)
{
    _selected_color = color;
}
/*
void GraphicsTableSubItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
 //   _hovered = true;
    emit hoverEnter();
    QGraphicsItem::hoverEnterEvent(event);
}

void GraphicsTableSubItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
 //   _hovered = false;
    emit hoverLeave();
    QGraphicsItem::hoverLeaveEvent(event);
}
*/
void GraphicsTableSubItem::setHover(const bool &hovered)
{
    _hovered = hovered;
    if (_hovered) {
        _text->setDefaultTextColor(_selectTextColor);
        if (_strStyle == GraphicsTableItem::html)
            _text->setHtml(_selectedHtml);
    }
    else{
        _text->setDefaultTextColor(_defaultTextColor);
        if (_strStyle == GraphicsTableItem::html)
            _text->setHtml(_html);
    }
    update();
}
void GraphicsTableSubItem::setCustomGridStyle(const Qt::PenStyle& style,
                                              const QColor& leftcolor,
                                              const QColor& topcolor,
                                              const QColor& rightcolor,
                                              const QColor& bottomcolor)
{
     _penStyle = style;
     _gridLeftColor = leftcolor;
     _gridTopColor = topcolor;
     _gridRightColor = rightcolor;
     _gridBottomColor = bottomcolor;
}
void GraphicsTableSubItem::setCustomSelectedGridStyle(const Qt::PenStyle& style,
                                              const QColor& leftcolor,
                                              const QColor& topcolor,
                                              const QColor& rightcolor,
                                              const QColor& bottomcolor)
{
     _penStyle = style;
     _gridSelectLeftColor = leftcolor;
     _gridSelectTopColor = topcolor;
     _gridSelectRightColor = rightcolor;
     _gridSelectBottomColor = bottomcolor;
}
void GraphicsTableSubItem::setDefaultTextColor(const QColor &defaultTextColor)
{
    _defaultTextColor = defaultTextColor;
}
void GraphicsTableSubItem::setSelectTextColor(const QColor &selectTextColor)
{
    _selectTextColor = selectTextColor;
}
void GraphicsTableSubItem::setText(const QString &text,
                     const GraphicsTableItem::row_item_str_style &style,
                     const QString &icon,
                     const GraphicsTableItem::row_item_icon &icon_style,
                     const GraphicsTableItem::row_item_icon_show &icon_show)
{
    _strStyle = style;
    if (style == GraphicsTableItem::normalString) {
        _text->setPlainText(text);
    }
    else if (style == GraphicsTableItem::html){
        _html = text;
        _text->setHtml(text);
    }

 //   if (icon == "")
 //       return;

    for (QList<icon_node>::iterator iter = _icons.begin();
         iter != _icons.end();iter++) {

        icon_node ic = *iter;
        if (ic._icon_style == icon_style && ic._icon_show == icon_show) {
            iter->_icon = icon;
            return;
        }
    }
    icon_node ic;
    ic._icon.load(icon);
    ic._icon_show = icon_show;
    ic._icon_style = icon_style;
    _icons.push_back(ic);
}

void GraphicsTableSubItem::setRowItemSelHtml(const QString &val)
{
    if (_strStyle == GraphicsTableItem::html)
        _selectedHtml = val;
}

void GraphicsTableSubItem::addIcon(const QString &icon , const GraphicsTableItem::row_item_icon &icon_style,
                const GraphicsTableItem::row_item_icon_show &icon_show)
{
    if (icon == "")
        return;

    for (QList<icon_node>::iterator iter = _icons.begin();
         iter != _icons.end();iter++) {

        icon_node ic = *iter;
        if (ic._icon_style == icon_style && ic._icon_show == icon_show) {
            QPixmap p; 
            p.load(icon);
            iter->_icon = p;
         //   iter->_icon.load(icon);
            this->update();
            return;
        }
    }
    icon_node ic;
    ic._icon.load(icon);
    ic._icon_show = icon_show;
    ic._icon_style = icon_style;
    _icons.push_back(ic);
}

QVariant GraphicsTableSubItem::itemChange ( GraphicsItemChange change, const QVariant & value )
{
    if (change == QGraphicsItem::ItemVisibleChange && _hovered) {

         setHover(false);
     }
    return QGraphicsItem::itemChange(change,value);
}

void GraphicsTableSubItem::setIcon(const int &iconIndex, const QString &icon, const GraphicsTableItem::row_item_icon &icon_style,
                const GraphicsTableItem::row_item_icon_show &icon_show )
{

}

void GraphicsTableSubItem::removeIcon( const int &iconIndex)
{
    if (iconIndex >= 0&& iconIndex < _icons.size()) {
        QList<icon_node>::iterator iter = _icons.begin() + iconIndex;
        _icons.erase(iter);
        update();
    }
}

void GraphicsTableSubItem::addSubItem(QGraphicsItem* item, QPoint pos)
{
    if (!item)
        return;
    item->setParentItem(this);
    _subItems.append(item);
    item->setPos(pos);
}

void GraphicsTableSubItem::setSubItemVisible(const int &index, const bool &vis)
{
    if (index >= 0 && index < _subItems.size())
        _subItems.at(index)->setVisible(vis);
}

QGraphicsItem* GraphicsTableSubItem::getLowSubItem(const int &itemIndex)
{
    if (itemIndex >= 0 && itemIndex < _subItems.size())
        return _subItems.at(itemIndex);
    return NULL;
}

void GraphicsTableSubItem::setToolTipText(const QString &tips)
{
    _text->setToolTip(tips);
}
