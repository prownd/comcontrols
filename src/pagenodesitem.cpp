#include "pagenodesitem.h"

#include "graphicsitembutton.h"
#include "custombtn.h"

const int NODE_WIDTH = 12;
const int NODE_SPACING = 5;


PageNodesWidget::PageNodesWidget(QWidget* parent)
    : QWidget(parent, Qt::FramelessWindowHint)
    , _sum(1)
    , _current(0)
{

    QPalette palette = this->palette();
    palette.setBrush(QPalette::Window,QBrush(QColor(0,0,0,0)));
    setPalette(palette);
}

void PageNodesWidget::paintEvent ( QPaintEvent * event )
{

}

void PageNodesWidget::resizeEvent ( QResizeEvent * event )
{

}

void PageNodesWidget::update(const int &sum, const int &cur)
{
    _sum = sum;
    _current = cur;


    resize(NODE_WIDTH * _sum + NODE_SPACING * (_sum - 1), NODE_WIDTH);

    for (int i = 0;i < _nodes.size();i++) {
//        _nodes.at(i)->setParentItem(NULL);
        delete _nodes.at(i);
    }
    _nodes.clear();

    if (_sum <= 1)
        return;

    for (int i = 0;i < sum;i++) {
        CustomBtn* node = new CustomBtn(this, CustomBtn::current_stay);

        node->SetImgs(":/resources/images/page_number.png",
                      ":/resources/images/page_number.png","",":/resources/images/page_number_current.png");
        node->resize(12,12);
        node->move(QPoint((NODE_WIDTH + NODE_SPACING) * i , 0));
        node->show();
        if (i == cur)
            node->setCurrent(true);
        _nodes.push_back(node);
        connect(node, SIGNAL(clicked(CustomBtn*)), this, SLOT(clickNode(CustomBtn* )));
    }
}

void PageNodesWidget::setCurrent(const int &cur)
{
    if (cur >= 0 && cur < _nodes.size()) {
        if (_current >= 0 && _current < _nodes.size())
            _nodes.at(_current)->setCurrent(false);
        _current = cur;
        _nodes.at(_current)->setCurrent(true);
    }
}

void PageNodesWidget::clickNode(CustomBtn* node)
{
    for (int i = 0;i < _nodes.size();i++) {
        if (_nodes.at(i)->isVisible()) {
            if (_nodes.at(i) == node) {
                emit choosePage(i);
                _current = i;
            }
            else {
                _nodes.at(i)->setCurrent(false);

            }
        }
    }
}

////////////////////////////////////////////////////////////////
PageNodesItem::PageNodesItem(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent)
{
    _nodes = new PageNodesWidget;
    this->setWidget(_nodes);
    _nodes->show();

    connect(_nodes, SIGNAL(choosePage(int)), this, SIGNAL(choosePage(int)));
}

void PageNodesItem::update(const int &sum , const int &cur)
{
    resize(NODE_WIDTH * sum + NODE_SPACING * (sum - 1), NODE_WIDTH);
    _nodes->update(sum, cur);
}

void PageNodesItem::setCurrent(const int &cur)
{
    _nodes->setCurrent(cur);
}
void PageNodesItem::setSum(const int &sum)
{
    _nodes->setSum(sum);
}
int PageNodesItem::getCurrent()
{
    return _nodes->getCurrent();
}
void PageNodesItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter(true);
    QGraphicsProxyWidget::hoverEnterEvent(event);
}
void PageNodesItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter(false);
    QGraphicsProxyWidget::hoverLeaveEvent(event);
}
