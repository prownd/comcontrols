#ifndef GRAPHICSTABLEITEM_H
#define GRAPHICSTABLEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QMap>
#include <QCursor>
#include <QMenu>
#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT TableMenu : public QMenu
{
public:

    TableMenu(const QString & title, QWidget * parent = 0 ):QMenu(title, parent) {
        _data = NULL;
    }

    TableMenu(QWidget * parent = 0 ):QMenu(parent) {
        _data = NULL;
    }

    void setData(void* data) { _data = data;}
    void* data() { return _data;}

private:

    void* _data;
};

//暂时不考虑滚动条
class QMenu;
class QGraphicsProxyWidget;
class GraphicsTableRow;
class GraphicsTableColumn;
class LCONTROLSSHARED_EXPORT GraphicsTableItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:

    enum select_style {
        normal, whole_row
    };

    enum row_item_str_style {
        normalString, html
    };

    enum row_item_icon {
        left, center, right
    };

    enum row_item_icon_show {
        allshow, selectshow
    };

    enum column_style{
        flat, solid
    };

    explicit GraphicsTableItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setSelectStyle(const select_style &sstyle);
    void setColumnStyle(const column_style &st);
    void setColumnSum(const int &columnSum);
    void setColumnWidth(const int &index, const int &width);
    void setColumnHeight(const int &hei);
    void setColumnText(const int &index, const QString &text);
    void setRowHeight(const int &height);

    GraphicsTableRow* addRow();
    void setRowItemText(const int &rowIndex , const int &itemIndex,
                         const QString &val, const row_item_str_style &style = normalString,
                         const QString &icon = "", const row_item_icon &icon_style = left,
                        const row_item_icon_show &icon_show = allshow);

    void addRowIcon(const int &rowIndex , const int &itemIndex,
                    const QString &icon = "", const row_item_icon &icon_style = left,
                    const row_item_icon_show &icon_show = allshow);

    void setRowIcon(const int &rowIndex , const int &itemIndex, const int &iconIndex,
                    const QString &icon = "", const row_item_icon &icon_style = left,
                    const row_item_icon_show &icon_show = allshow);

    void removeRowIcon(const int &rowIndex , const int &itemIndex, const int &iconIndex);

    void setRowEnable(const int &rowIndex , const bool &enable = false);

    //被选中时显示的html
    void setRowItemSelHtml(const int &rowIndex , const int &itemIndex, const QString &val);

    void setRowData(const int &rowIndex, void* data);
    void* rowData(const int &rowIndex);

    bool removeRow(const int &index);
    void removeAllRows();

    void setRowCursor ( const QCursor & cursor );

    int rowCount();


    void addRowLowSubItem(const int &rowIndex , const int &index, QGraphicsItem* subItem, QPoint pos);
    void setRowLowSubItemVisible(const int &rowIndex , const int &index, const int &subItem, const bool &vis);
    QGraphicsItem* getLowSubItem(const int &rowIndex , const int &subIndex, const int &itemIndex);
    void setMenu(TableMenu* menu);
    // 设置网格线 by wj
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
    void setRowBgColor(const QColor& bg = QColor("#f0f1f7"));
    void setRowBgSelectedColor(const QColor& bg = QColor("#1275c3"));
    void setRowHoverAble(const bool &hoverable = true);
    void showBoardLine(const bool &board = true){ _showBoardLine = board;}
    GraphicsTableRow* rowAt(const int &index);
    void setToolTipText(const int &rowIndex , const int &itemIndex,const QString &tips);
signals:

    void rowClicked(const int &index);
    void rowRClicked(const int &index);

public slots:

    void rowClicked(GraphicsTableRow* row);
    void rowRClicked(GraphicsTableRow* row);
private:

    void refreshColumn();
    QString getColumnImg(const column_style &st);

private:


    int _width;
    int _height;
    int _rowHeight;
    int _columnHeight;
    bool _showBoardLine;
    typedef QMap<int,int> COLUMN_WIDTH;
    COLUMN_WIDTH _columnWidth;

    QList<GraphicsTableRow*> _rows;
    QList<GraphicsTableColumn*> _columns;

    select_style _sstyle;

    QCursor _cursor;

    TableMenu* _menu;

    column_style _colStyle;
};

#endif // GRAPHICSTABLEITEM_H
