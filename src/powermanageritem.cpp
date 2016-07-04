#include "powermanageritem.h"
#include "graphicsitembutton.h"
#include <QTimer>
#include <QListWidget>
#include <QGraphicsProxyWidget>
PowerManagerItem::PowerManagerItem(QGraphicsItem* parent):QGraphicsItem(parent)
, _itemWidth(100)
, _itemHeight(10)
, _show(false)
, _hover(false)
, _buttonClicked(false)
{ 
    setFiltersChildEvents(true);
    setAcceptHoverEvents(true);
    _listBtn = new GraphicsItemButton("",
                                      "",
                                      "",
                                      "",
                                       GraphicsItemButton::normal,this);

    _listBtn->setPos(0,0);
    _listBtn->installEventFilter(this);
    _listWidget = new QListWidget(NULL);
    _listWidget->setStyleSheet("QListWidget{background-color:transparent;color:#19649F;border:0px solid gray;}"
                                          "QListWidget::item{background-color:transparent;border:0px solid gray;padding-left:28px;color:#b4e5fd}"
                                          "QListWidget::item:selected{background-image:url(:/resources/images/handleMenu_lixt_bg_selected.png);}"
                                          );
      
    _proxy = new QGraphicsProxyWidget(this);
    _proxy->setWidget(_listWidget);
    _proxy->setVisible(_show);

    _listWidget->setMouseTracking(true);
    _listWidget->setFocusPolicy(Qt::NoFocus);
    _listWidget->installEventFilter(this);
    QPalette pal;
    pal.setColor(QPalette::Background, QColor(0xFF,0xFF,0xFF,0x00));
    _listWidget->setPalette(pal);

    _timer = new QTimer(this);
    _timerForFocus = new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(slotTimeOut()));
    connect(_timerForFocus,SIGNAL(timeout()),this,SLOT(slotFocusOut()));
    connect(_listBtn,SIGNAL(clicked()),this,SLOT(slotBtnClicked()));
}

void PowerManagerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
}

QRectF PowerManagerItem::boundingRect() const
{
    return QRectF(0, _listBtn->boundingRect().height(), _width, _height - _listBtn->boundingRect().height());
}
void PowerManagerItem::setSize(const int &width, const int &height)
{
    _width = width;
    _height = height;
    _listBtn->setSize(_width, _height);
    _listBtn->setPos((_width - _listBtn->boundingRect().width())/2, (_height - _listBtn->boundingRect().height())/2);
    _proxy->setPos((_width - _itemWidth)/2, _listBtn->boundingRect().bottom());
}
void PowerManagerItem::setImage(const QString &image, const QString &hoverImage,
                  const QString &currentImage, const QString &disableImage,
                  const int &imgWidth , const int &imgHeight)
{
    _listBtn->setImage(image, hoverImage, currentImage, disableImage, imgWidth, imgHeight);
}
 
void PowerManagerItem::addItem(const QString& item)
{
    _listWidget->addItem(item);
}
void PowerManagerItem::addItems(const QStringList& list)
{
    _listWidget->addItems(list);
}
int PowerManagerItem::itemCount()
{
    return _listWidget->count();
}
void PowerManagerItem::clear()
{
    _listWidget->clear();
}
void PowerManagerItem::setItemEnable(const int& count, const bool& able)
{
    if(count >= itemCount() || count < 0)
        return;
    _listWidget->item(count)->setEnabled(able);
}
void PowerManagerItem::setMenuItemSize(const int& width, const int& height)
{
    _itemWidth = width;
    _itemHeight = height;
}
bool PowerManagerItem::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::FocusIn)
    {
        if(obj == _listWidget)
        {
            _buttonClicked = false;
        }
    }
    if(event->type() == QEvent::FocusOut)
    {
        if (obj == _listWidget) {
        _timerForFocus->start(100);    
        return true;
        }
    }
    return QObject::eventFilter(obj, event);
}

void PowerManagerItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{

    _hover = true;
    _timer->stop();
}

void PowerManagerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _hover = false;
    _timer->start(1500);
}

void PowerManagerItem::slotBtnClicked()
{
    _buttonClicked = true;
    _listBtn->setCurrent(true);

    if(!_show){
    _listWidget->setVisible(!_show);
    _listWidget->setGeometry(QRect(0,_height, _itemWidth, _itemHeight*count()));
    QPropertyAnimation *animation = new QPropertyAnimation(_listWidget, "geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom()));
    animation->setEndValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom() + _itemHeight*count()));
    animation->start();
    _listWidget->setFocus();
    _show = true;
    }
    else{
        QPropertyAnimation *animation = new QPropertyAnimation(_listWidget, "geometry");
        animation->setDuration(300);
        animation->setEndtValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom()));
        animation->setStartValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom() + _itemHeight*count()));
        animation->start();
        _show = false;
        _listBtn->setCurrent(false);
        _listWidget->clearFocus();
    }
}

void PowerManagerItem::slotTimeOut()
{
    _timer->stop();
    if(_show){

        QPropertyAnimation *animation = new QPropertyAnimation(_clusterWidget, "geometry");
        animation->setDuration(300);
        animation->setEndtValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom()));
        animation->setStartValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom() + _itemHeight*count()));
        animation->start();
        _show = false; 
        _buttonClicked = false;
        _listBtn->setCurrent(false);
        _clusterWidget->clearFocus();
    }
}
void PowerManagerItem::slotFocusOut()
{
        _timerForFocus->stop();
        if(_show && !_buttonClicked){
            QPropertyAnimation *animation = new QPropertyAnimation(_clusterWidget, "geometry");
            animation->setDuration(100);
            animation->setEndtValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom()));
            animation->setStartValue(QRect(0,_listBtn->bottom(),_itemWidth,_listBtn->bottom() + _itemHeight*count()));
            animation->start();
         _listBtn->setCurrent(false);
         _show = false;
         _buttonClicked = false;
         if(_timer->isActive())
             _timer->stop();
        }

}

