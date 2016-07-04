#include "graphicstablerow.h"
#include "graphicstablesubitem.h"
#include "graphicstableitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QAction>
#include <QPalette>
#include <QMenu>
#include <QGraphicsItemAnimation>
#include <QTimeLine>
#include <QDebug>
#include <QToolTip>

GraphicsTableRow::GraphicsTableRow(const int &id, const int &itemSum, QMap<int ,int > itemWidth, const int &height,
                                   const GraphicsTableItem::select_style &style, QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , _height(height)
  , _style(style)
  , _id(id)
  , _menu(NULL)
  , _enable(true)
  , _isHovered(false)
{
//    QPalette palette = QToolTip::palette();
//    palette.setBrush(QPalette::Window, QBrush(QColor(0xff19649f)));
//    QToolTip::setPalette(palette);

 //   this->setToolTip("333");

    _timer = new QTimeLine(200);
    _timer->setFrameRange(0, 100);

    _ani = new QGraphicsItemAnimation;
    _ani->setItem(this);
    _ani->setTimeLine(_timer);


    _menuPopup = false;
    this->setAcceptHoverEvents(true);

    int wid = 0;
    int left = 0;
    for (int i = 0;i < itemSum;i++) {
        QMap<int, int >::iterator iter = itemWidth.find(i);
        if (iter != itemWidth.end())
            wid = iter.value();
        GraphicsTableSubItem* item = new GraphicsTableSubItem(wid,height, this);
        item->setPos(left, 0);
        _items.push_back(item);

     //   connect()
        left += wid;
    }

    _width = 0;
    for (QMap<int ,int>::iterator iter = itemWidth.begin();iter != itemWidth.end();iter++)
        _width += iter.value();
}

GraphicsTableRow::~GraphicsTableRow()
{
    if (_timer->state() == QTimeLine::Running)
        _timer->stop();

    delete _timer;
    _timer = NULL;
    delete _ani;
    _ani = NULL;
}

void GraphicsTableRow::contextMenuEvent ( QGraphicsSceneContextMenuEvent * event )
{
    if (!_menu)
        return;

    _menu->setData(_data);
    _menuPopup = true;
 //   _menu->exec(event->screenPos());

    _menu->popup(event->screenPos());
//    hoverLeave();
    _menuPopup = false;
}
QRectF GraphicsTableRow::boundingRect() const
{
    return QRectF(0,0,_width ,_height);
}

void GraphicsTableRow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{

}

void GraphicsTableRow::hoverLeave()
{
    if (_style == GraphicsTableItem::whole_row)
        for (int i = 0;i < _items.size();i++)
            _items.at(i)->setHover(false);
}

void GraphicsTableRow::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
    if (_style == GraphicsTableItem::whole_row)
        for (int i = 0;i < _items.size();i++)
            _items.at(i)->setHover(true);
    _isHovered = true;
    emit hoverEnter(this);

}
void GraphicsTableRow::setCustomGridStyle(const Qt::PenStyle &style,
                                          const QColor& leftcolor,
                                          const QColor& topcolor,
                                          const QColor& rightcolor,
                                          const QColor& bottomcolor)
{
    for(int i = 0; i < _items.size(); i++)
    {
         _items.at(i)->setCustomGridStyle(style, leftcolor, topcolor, rightcolor, bottomcolor);
    }
}
void GraphicsTableRow::setCustomSelectedGridStyle(const Qt::PenStyle &style,
                                          const QColor& leftcolor,
                                          const QColor& topcolor,
                                          const QColor& rightcolor,
                                          const QColor& bottomcolor)
{
    for(int i = 0; i < _items.size(); i++)
    {
         _items.at(i)->setCustomSelectedGridStyle(style, leftcolor, topcolor, rightcolor, bottomcolor);
    }
}
void GraphicsTableRow::setDefaultTextColor(const QColor &defaultTextColor)
{
    for(int i = 0; i < _items.size(); i++)
    {
         _items.at(i)->setDefaultTextColor(defaultTextColor);
    }
}
void GraphicsTableRow::setSelectTextColor(const QColor &selectTextColor)
{
    for(int i = 0; i < _items.size(); i++)
    {
         _items.at(i)->setSelectTextColor(selectTextColor);
    }
}
void GraphicsTableRow::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (_menuPopup)
        return;

    hoverLeave();
    _isHovered = false;
    emit hoverLeave(this);
    QGraphicsItem::hoverLeaveEvent(event);
}


void GraphicsTableRow::setText(const int &itemIndex,
             const QString &text,
             const GraphicsTableItem::row_item_str_style &style,
             const QString &icon,
             const GraphicsTableItem::row_item_icon &icon_style,
             const GraphicsTableItem::row_item_icon_show &icon_show)
{
    if (itemIndex < 0 || itemIndex >= _items.size())
        return;
    _items.at(itemIndex)->setText(text, style, icon, icon_style, icon_show);
}

void GraphicsTableRow::setColor(const QColor &color)
{
    for (int i = 0;i < _items.size();i++) {
        _items.at(i)->setColor(color);
        _items.at(i)->update();
    }
}
void GraphicsTableRow::setSelectedColor(const QColor &color)
{
    for (int i = 0;i < _items.size();i++) {
        _items.at(i)->setSelectedColor(color);
        _items.at(i)->update();
    }
}

void GraphicsTableRow::setRowItemSelHtml(const int &itemIndex, const QString &val)
{
    if (itemIndex >= 0 && itemIndex < _items.size())
        _items.at(itemIndex)->setRowItemSelHtml(val);
}

void GraphicsTableRow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!_enable)
        return;

    if (event->button() == Qt::LeftButton)
        emit clicked(this);
    else if (event->button() == Qt::RightButton)
        emit rClicked(this);
//    QGraphicsItem::mousePressEvent(event);
}

void GraphicsTableRow::setData(void* data)
{
    _data = data;
}

void* GraphicsTableRow::data()
{
    return _data;
}

int GraphicsTableRow::id()
{
    return _id;
}

void GraphicsTableRow::addItemIcon(const int &itemIndex,
                const QString &icon, const GraphicsTableItem::row_item_icon &icon_style,
                const GraphicsTableItem::row_item_icon_show &icon_show)
{
    if (itemIndex >= 0 && itemIndex < _items.size())
        _items.at(itemIndex)->addIcon(icon, icon_style, icon_show);
}

void GraphicsTableRow::setMenu(TableMenu* menu)
{
    _menu = menu;
}

void GraphicsTableRow::setID(const int &id)
{
    _id = id;
}

void GraphicsTableRow::animationMove(const QPointF &end)
{
    _ani->setPosAt(0.0, this->pos());
    _ani->setPosAt(1.0, end);
    if (_timer->state() == QTimeLine::Running)
        _timer->stop();
    _timer->start();
}

void GraphicsTableRow::setItemIcon(const int &itemIndex, const int &iconIndex,
                const QString &icon, const GraphicsTableItem::row_item_icon &icon_style,
                const GraphicsTableItem::row_item_icon_show &icon_show)
{
    if (itemIndex >= 0 && itemIndex < _items.size())
        _items.at(itemIndex)->setIcon(iconIndex, icon, icon_style, icon_show);
}

void GraphicsTableRow::removeItemIcon(const int &itemIndex, const int &iconIndex)
{
    if (itemIndex >= 0 && itemIndex < _items.size())
        _items.at(itemIndex)->removeIcon(iconIndex);
}

void GraphicsTableRow::addLowSubItem(const int &index, QGraphicsItem* subItem, QPoint pos)
{
    if (index >= 0 && index < _items.size())
        _items.at(index)->addSubItem(subItem, pos);
}

void GraphicsTableRow::setLowSubItemVisible(const int &index, const int &subItem, const bool &vis)
{
    if (index >= 0 && index < _items.size())
        _items.at(index)->setSubItemVisible(subItem, vis);
}

QGraphicsItem* GraphicsTableRow::getLowSubItem(const int &subIndex, const int &itemIndex)
{
    if (subIndex >= 0 && subIndex < _items.size())
        return _items.at(subIndex)->getLowSubItem(itemIndex);
    return NULL;
}

void GraphicsTableRow::setToolTipText(const int &itemIndex, const QString &tips)
{
    if (itemIndex < 0 || itemIndex >= _items.size())
        return;
    _items.at(itemIndex)->setToolTipText(tips);
}
