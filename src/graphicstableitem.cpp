#include "graphicstableitem.h"
#include "graphicstablerow.h"
#include "graphicstablecolumn.h"

#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QGraphicsSceneContextMenuEvent>

const int EDGE_WIDTH = 1;

GraphicsTableItem::GraphicsTableItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
  , _sstyle(whole_row)
  , _menu(NULL)
  , _showBoardLine(true)
  , _colStyle(solid)
{

    this->setAcceptHoverEvents(true);
    _columnHeight = 29;
    _rowHeight = 40;

    _width = 0;
    _height = 0;
    _cursor = Qt::ArrowCursor;
}

QRectF GraphicsTableItem::boundingRect() const
{
    return QRectF(0,0 , _width, _height);
}

void GraphicsTableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    QPen pen(QColor("#dee0ea"));
    painter->setPen(pen);
//    pen.setWidth(EDGE_WIDTH);
    if(_showBoardLine)
        painter->drawRect(boundingRect());
}
void GraphicsTableItem::setColumnWidth(const int &index, const int &width)
{
    _columnWidth.insert(index, width);

    if (index >= 0 && index < _columns.size())
        _columns.at(index)->setWidth(width);

    _width = 0;
    for (COLUMN_WIDTH::iterator iter = _columnWidth.begin();iter != _columnWidth.end();iter++) {
        _width += iter.value();
    }
    refreshColumn();
}
GraphicsTableRow* GraphicsTableItem::rowAt(const int &index)
{
    if(index < _rows.size())
        return _rows.at(index);
    else
        return NULL;
}

void GraphicsTableItem::setToolTipText(const int &rowIndex, const int &itemIndex, const QString &tips)
{
    if (rowIndex < 0 || rowIndex >= _rows.size())
        return;
    _rows.at(rowIndex)->setToolTipText(itemIndex, tips);
}
GraphicsTableRow* GraphicsTableItem::addRow()
{
    GraphicsTableRow* row = new GraphicsTableRow(_rows.size(), _columns.size(), _columnWidth, _rowHeight,
                                                 GraphicsTableItem::whole_row,this);
    row->setPos(EDGE_WIDTH, _rowHeight * _rows.size() + _columnHeight+ 1);
    row->setCursor(_cursor);
    connect(row, SIGNAL(clicked(GraphicsTableRow*)), this, SLOT(rowClicked(GraphicsTableRow*)));
    connect(row, SIGNAL(rClicked(GraphicsTableRow*)), this, SLOT(rowRClicked(GraphicsTableRow*)));

    row->setMenu(_menu);

    _rows.push_back(row);

    if (_rows.size() %2 == 0)
        row->setColor(QColor("#f0f1f7"));
    else
        row->setColor(QColor("#f7f7f7"));
    _height = _rowHeight * _rows.size() + _columnHeight;

    return row;
}

void GraphicsTableItem::setRowItemText(const int &rowIndex , const int &itemIndex,
                                        const QString &val, const row_item_str_style &style,
                                        const QString &icon, const row_item_icon &icon_style,
                                        const GraphicsTableItem::row_item_icon_show &icon_show)
{
    if (rowIndex < 0 || rowIndex >= _rows.size())
        return;
    _rows.at(rowIndex)->setText(itemIndex, val, style, icon, icon_style, icon_show);

}
void GraphicsTableItem::setCustomGridStyle(const Qt::PenStyle& style ,
                                           const QColor& leftcolor ,
                                           const QColor& topcolor ,
                                           const QColor& rightcolor ,
                                           const QColor& bottomcolor)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setCustomGridStyle(style, leftcolor, topcolor, rightcolor, bottomcolor);
    }
}
void GraphicsTableItem::setCustomSelectedGridStyle(const Qt::PenStyle& style ,
                                           const QColor& leftcolor ,
                                           const QColor& topcolor ,
                                           const QColor& rightcolor ,
                                           const QColor& bottomcolor)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setCustomSelectedGridStyle(style, leftcolor, topcolor, rightcolor, bottomcolor);
    }
}
void GraphicsTableItem::setDefaultTextColor(const QColor &defaultTextColor)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setDefaultTextColor(defaultTextColor);
    }
}
void GraphicsTableItem::setSelectTextColor(const QColor &selectTextColor)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setSelectTextColor(selectTextColor);
    }
}
void GraphicsTableItem::setRowBgColor(const QColor &bg)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setColor(bg);
    }
}
void GraphicsTableItem::setRowBgSelectedColor(const QColor &bg)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setSelectedColor(bg);
    }
}
void GraphicsTableItem::setRowHoverAble(const bool &hoverable)
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setAcceptHoverEvents(hoverable);
    }
}
void GraphicsTableItem::setSelectStyle(const select_style &sstyle)
{
    _sstyle = sstyle;
}

void GraphicsTableItem::setColumnHeight(const int &hei)
{
    _columnHeight = hei;
    for (int i = 0;i < _columns.size();i++)
        _columns.at(i)->setHeight(hei);
}

void GraphicsTableItem::setRowHeight(const int &height)
{
    _rowHeight = height;
}

void GraphicsTableItem::setColumnSum(const int &columnSum)
{
    _columns.clear();
    for (int i = 0;i < columnSum;i++) {
        GraphicsTableColumn* column = new GraphicsTableColumn(this);
        column->setHeight(_columnHeight);
        column->setPos(0,0);
        column->setImage(getColumnImg(_colStyle));
        _columns.push_back(column);
    }
}

void GraphicsTableItem::setColumnText(const int &index, const QString &text)
{
    if (index < 0 || index >= _columns.size())
        return;
    _columns.at(index)->setText(text);
}

void GraphicsTableItem::refreshColumn()
{
    int left = EDGE_WIDTH;
    for (int i = 0;i < _columns.size();i++) {
        _columns.at(i)->setPos(left, EDGE_WIDTH);
        COLUMN_WIDTH::iterator iter = _columnWidth.find(i);
        if (iter != _columnWidth.end())
            left += iter.value();
    }
}

void GraphicsTableItem::removeAllRows()
{
    for (int i = 0;i < _rows.size();i++) {
        _rows.at(i)->setParent(NULL);
        delete _rows.at(i);
    }
    _rows.clear();
    _height = _columnHeight;
    update();
}

void GraphicsTableItem::setRowItemSelHtml(const int &rowIndex , const int &itemIndex, const QString &val)
{
    if (rowIndex <0 || rowIndex >= _rows.size())
        return;
    _rows.at(rowIndex)->setRowItemSelHtml(itemIndex,val);
}

void GraphicsTableItem::setRowData(const int &rowIndex, void* data)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->setData(data);
}

void* GraphicsTableItem::rowData(const int &rowIndex)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        return _rows.at(rowIndex)->data();
    return NULL;
}

void GraphicsTableItem::rowClicked(GraphicsTableRow* row)
{
    emit rowClicked(row->id());
}

void GraphicsTableItem::rowRClicked(GraphicsTableRow* row)
{
    emit rowRClicked(row->id());
}

void GraphicsTableItem::setRowCursor ( const QCursor & cursor )
{
    _cursor = cursor;
    for (int i = 0;i < _rows.size();i++)
        _rows.at(i)->setCursor(cursor);
}

int GraphicsTableItem::rowCount()
{
    return _rows.size();
}

void GraphicsTableItem::addRowIcon(const int &rowIndex , const int &itemIndex,
                                   const QString &icon , const row_item_icon &icon_style,
                                   const row_item_icon_show &icon_show )
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->addItemIcon(itemIndex, icon, icon_style, icon_show);
}

void GraphicsTableItem::setMenu(TableMenu* menu)
{
    _menu = menu;
}

bool GraphicsTableItem::removeRow(const int &index)
{
    if (index < 0 || index >= _rows.size())
        return false;

    QList<GraphicsTableRow*>::iterator iter = _rows.begin() + index;
    (*iter)->setParentItem(NULL);
    delete *iter;
    *iter = NULL;
    _rows.erase(iter);

    for (int i = index;i < _rows.size();i++) {
        _rows.at(i)->animationMove(QPointF(EDGE_WIDTH, _rowHeight * i + _columnHeight + 1));
        _rows.at(i)->setID(i);
    }
    _height = _rowHeight * _rows.size() + _columnHeight;
    update();
    return true;
}

void GraphicsTableItem::setRowIcon(const int &rowIndex , const int &itemIndex, const int &iconIndex,
                const QString &icon, const row_item_icon &icon_style,
                const row_item_icon_show &icon_show)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->setItemIcon(itemIndex,iconIndex,  icon, icon_style, icon_show);
}

void GraphicsTableItem::setRowEnable(const int &rowIndex , const bool &enable)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->setEnable(enable);
}

void GraphicsTableItem::removeRowIcon(const int &rowIndex , const int &itemIndex, const int &iconIndex)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->removeItemIcon(itemIndex, iconIndex);
}


void GraphicsTableItem::addRowLowSubItem(const int &rowIndex , const int &index, QGraphicsItem* subItem, QPoint pos)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->addLowSubItem(index, subItem, pos);
}

void GraphicsTableItem::setRowLowSubItemVisible(const int &rowIndex , const int &index, const int &subItem, const bool &vis)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        _rows.at(rowIndex)->setLowSubItemVisible(index, subItem, vis);
}

QGraphicsItem* GraphicsTableItem::getLowSubItem(const int &rowIndex , const int &subIndex, const int &itemIndex)
{
    if (rowIndex >= 0 && rowIndex < _rows.size())
        return _rows.at(rowIndex)->getLowSubItem(subIndex, itemIndex);
    return NULL;
}

QString GraphicsTableItem::getColumnImg(const column_style &st)
{
    QString img = ":/resources/images/table_thead_bg.png";
    if (st == flat)
        img = ":/resources/images/table_thead_bg_flat.png";

    return img;
}

void GraphicsTableItem::setColumnStyle(const column_style &st)
{
    _colStyle = st;
    for(int i = 0;i < _columns.size();i++)
        _columns.at(i)->setImage(getColumnImg(st));
}
