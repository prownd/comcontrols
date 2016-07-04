#include "faderitem.h"
#include <QPointF>
#include <QPainter>
#include <QTextCodec>
#include <QSizeF>
#include <QApplication>
#include <QDebug>
FaderItem::FaderItem(QGraphicsItem *parentItem):QGraphicsItem(parentItem)
  , _running(false)
  , _fixed(false)
{
    this->setAcceptHoverEvents(true);
    setCacheMode(NoCache);
    setOpacity(1);
    timeline=new QTimeLine(8000,this);
    timeline->setFrameRange(0,300);
    changenumber=0;
    setVisible(false);
    picture_heigth=30;

    _tipsBox_error_left.load(":/resources/images/tipsBox_error_left.png");
    _tipsBox_error_center.load(":/resources/images/tipsBox_error_center.png");
    _tipsBox_error_right.load(":/resources/images/tipsBox_error_right.png");

    _tipsBox_note_left.load(":/resources/images/tipsBox_note_left.png");
    _tipsBox_note_center.load(":/resources/images/tipsBox_note_center.png");
    _tipsBox_note_right.load(":/resources/images/tipsBox_note_right.png");

    _tipsBox_succeed_left.load(":/resources/images/tipsBox_succeed_left.png");
    _tipsBox_succeed_center.load(":/resources/images/tipsBox_succeed_center.png");
    _tipsBox_succeed_right.load(":/resources/images/tipsBox_succeed_right.png");

    connect(timeline,SIGNAL(frameChanged(int)),this,SLOT(fade_on_fade_in(int)));
    connect(timeline, SIGNAL(finished()), this, SLOT(timeFinished()));

}
void FaderItem::fade_on_fade_in(int counter)
{
    this->setVisible(true);
    changenumber=counter;

    if(changenumber<=10)
    {
        this->setPos(0,view_height-changenumber*picture_heigth/10);
    }
    else if(changenumber<250)
    {
        this->setPos(0,view_height-picture_heigth);
        if (_fixed)
            timeline->setPaused(true);
    }
    else if(changenumber<300)
    {
        this->setPos(0,view_height-3*picture_heigth+changenumber*picture_heigth/100);
    }
    else
    {
     timeline->stop();
     this->setVisible(false);
    }
}

void FaderItem::setTranslate(qreal view_width, qreal view_heigth)
{
    this->view_width=view_width;
    this->view_height=view_heigth;
}

void FaderItem::receiveStatus(int status,int tip_change_rate,QString content)
{
    if (_fixed)
        return;

     timeline->stop();
     this->status=status;
     this->tip_change_rate=tip_change_rate;

     timeline->setCurrentTime(0);
     qDebug()<<"fader currenttime:"<<timeline->currentTime();
     timeline->setUpdateInterval(this->tip_change_rate);
     timeline->setDuration(300*(this->tip_change_rate));
     this->_content=content;
     timeline->start();
     _running = true;
}

QRectF FaderItem::boundingRect() const
{
    return QRectF(QPointF(0,0),QSizeF(view_width,picture_heigth));
}
void FaderItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QString string;
    switch (status){

    case 1:
        pixmap1 = _tipsBox_error_left;
        pixmap2 = _tipsBox_error_center;
        pixmap3 = _tipsBox_error_right;
        string=QString(tr("%1").arg(_content));
        break;
       case 2:
        pixmap1 = _tipsBox_note_left;
        pixmap2 = _tipsBox_note_center;
        pixmap3 = _tipsBox_note_right;
        string=QString(tr("%1").arg(_content));
         break;
       case 3:
        pixmap1 = _tipsBox_succeed_left;
        pixmap2 = _tipsBox_succeed_center;
        pixmap3 = _tipsBox_succeed_right;
        string=QString(tr("%1").arg(_content));
        break;
    }
//    painter->setFont(QFont(QString::fromLocal8Bit("ËÎÌו"),13,-1,false));
    painter->setPen(QPen(QColor(255,255,255)));
//    painter->drawPixmap(0,0,30,picture_heigth,pixmap1);
    pixmap2 = pixmap2.scaled(view_width,picture_heigth);
    painter->drawPixmap(0,0,view_width,picture_heigth,pixmap2);
//    painter->drawPixmap(view_width-30,0,30,picture_heigth,pixmap3);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    int textWidth = painter->fontMetrics().width(string);
    if(textWidth < 1)
        return;
    if(textWidth < view_width)
        painter->drawText((view_width-textWidth)/2,20,string);
    if(textWidth > view_width)
        painter->drawText(0,20,string);
}

void FaderItem::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    if (_running)
        timeline->setPaused(true);
}

void FaderItem::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
    if (_running)
        timeline->resume();
}

void FaderItem::timeFinished()
{
    _running = false;
}

void FaderItem::setFixed(const bool &fix)
{
    _fixed = fix;
    if (!fix && timeline->state() == QTimeLine::Paused)
        timeline->resume();
}


/////////////////////////////////////////////////////////////////////////////////////////
FaderWidget::FaderWidget(QWidget *parent)
  : QWidget(parent)
  , _running(false)
  , _fixed(false)
{

    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    timeline=new QTimeLine(8000,this);
    timeline->setFrameRange(0,300);
    changenumber=0;
    picture_heigth=30;

    _tipsBox_error_left.load(":/resources/images/tipsBox_error_left.png");
    _tipsBox_error_center.load(":/resources/images/tipsBox_error_center.png");
    _tipsBox_error_right.load(":/resources/images/tipsBox_error_right.png");

    _tipsBox_note_left.load(":/resources/images/tipsBox_note_left.png");
    _tipsBox_note_center.load(":/resources/images/tipsBox_note_center.png");
    _tipsBox_note_right.load(":/resources/images/tipsBox_note_right.png");

    _tipsBox_succeed_left.load(":/resources/images/tipsBox_succeed_left.png");
    _tipsBox_succeed_center.load(":/resources/images/tipsBox_succeed_center.png");
    _tipsBox_succeed_right.load(":/resources/images/tipsBox_succeed_right.png");

    connect(timeline,SIGNAL(frameChanged(int)),this,SLOT(fade_on_fade_in(int)));
    connect(timeline, SIGNAL(finished()), this, SLOT(timeFinished()));

}
void FaderWidget::fade_on_fade_in(int counter)
{
    this->setVisible(true);
    changenumber=counter;

    if(changenumber<=10)
    {
        this->move(0,view_height-changenumber*picture_heigth/10);
    }
    else if(changenumber<250)
    {
        this->move(0,view_height-picture_heigth);
        if (_fixed)
            timeline->setPaused(true);
    }
    else if(changenumber<300)
    {
        this->move(0,view_height-3*picture_heigth+changenumber*picture_heigth/100);
    }
    else
    {
     timeline->stop();
     this->setVisible(false);
    }
}

void FaderWidget::setTranslate(qreal view_width, qreal view_heigth)
{
    this->view_width=view_width;
    this->view_height=view_heigth;
}

void FaderWidget::receiveStatus(int status,int tip_change_rate,QString content)
{
    if (_fixed)
        return;

     timeline->stop();
     this->status=status;
     this->tip_change_rate=tip_change_rate;
     timeline->setUpdateInterval(this->tip_change_rate);
     timeline->setDuration(300*(this->tip_change_rate));
     timeline->setCurrentTime(0);
     this->_content=content;
     timeline->start();
     _running = true;
}

void FaderWidget::timeFinished()
{
    _running = false;
}

void FaderWidget::setFixed(const bool &fix)
{
    _fixed = fix;
    if (!fix && timeline->state() == QTimeLine::Paused)
        timeline->resume();
}

void FaderWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pixmap1;
    QPixmap pixmap2;
    QPixmap pixmap3;
    QString string;
    switch (status){

    case 1:
        pixmap1 = _tipsBox_error_left;
        pixmap2 = _tipsBox_error_center;
        pixmap3 = _tipsBox_error_right;
        string=QString(tr("%1").arg(_content));
        break;
       case 2:
        pixmap1 = _tipsBox_note_left;
        pixmap2 = _tipsBox_note_center;
        pixmap3 = _tipsBox_note_right;
        string=QString(tr("%1").arg(_content));
         break;
       case 3:
        pixmap1 = _tipsBox_succeed_left;
        pixmap2 = _tipsBox_succeed_center;
        pixmap3 = _tipsBox_succeed_right;
        string=QString(tr("%1").arg(_content));
        break;
    }
    painter.setPen(QPen(QColor(255,255,255)));
    pixmap2 = pixmap2.scaled(view_width,picture_heigth);
    painter.drawPixmap(0,0,view_width,picture_heigth,pixmap2);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    int textWidth = painter.fontMetrics().width(string);
    if(textWidth < 1)
        return;
    if(textWidth < view_width)
        painter.drawText((view_width-textWidth)/2,20,string);
    if(textWidth > view_width)
        painter.drawText(0,20,string);
}

void FaderWidget::enterEvent(QEvent *)
{
    if (_running)
        timeline->setPaused(true);
}

void FaderWidget::leaveEvent(QEvent *)
{
    if (_running)
        timeline->resume();
}


