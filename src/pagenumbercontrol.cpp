#include <QtGui>
#include "pagenumbercontrol.h"

PageNumberControl::PageNumberControl(QWidget *parent)
    : IPageNumberControl(parent)
    ,_cluster(false)
{
    backgroundColor = QColor(0xFF,0xFF,0xFF,0xFF);
    _currentPageNumber = 1;
    _totalPageNumber = 1;

    setStyleSheet("QLabel{font-family:arial;font-size:14px; color:#19649F;}");
    currentPageLabel = new QLabel(this);
    middleLabel = new QLabel(tr("/"), this);
    totalPageLabel = new QLabel(this);

    forwardBtn = new CustomBtn(this);
    forwardBtn->SetImgs(":/resources/images/handleMenu_pagination_previous.png", ":/resources/images/handleMenu_pagination_previous.png", ":/resources/images/handleMenu_pagination_previous_disable.png", "");
    forwardBtn->resize(15, 15);
    forwardBtn->move(0,0);
    forwardBtn->setText("<", Qt::white, Qt::white, QFont("verdana", 10, QFont::Normal));
    connect(forwardBtn, SIGNAL(clicked()), this, SLOT(slotForwardPage()));

    backwardBtn = new CustomBtn(this);
    backwardBtn->SetImgs(":/resources/images/handleMenu_pagination_next.png", ":/resources/images/handleMenu_pagination_next.png", ":/resources/images/handleMenu_pagination_next_disable.png", "");
    backwardBtn->setText(">", Qt::white, Qt::white, QFont("verdana", 10, QFont::Normal));
    backwardBtn->resize(15, 15);
    backwardBtn->move(18,0);
    connect(backwardBtn, SIGNAL(clicked()), this, SLOT(slotBackwardPage()));

    updatePageNumber();

    resize(95, 15);
    setWindowFlags(Qt::FramelessWindowHint);
}

PageNumberControl::~PageNumberControl()
{

}

void PageNumberControl::setCurrentPage(int currentPageNumber)
{
    if (currentPageNumber > _totalPageNumber) {    //超出最大页
        _currentPageNumber = _totalPageNumber;
    }
    else if (currentPageNumber < 1) {              //设置超出最小范围
        _currentPageNumber = 1;
    }
    else {
        _currentPageNumber = currentPageNumber;    //正常
    }
    updatePageNumber();
}

void PageNumberControl::setTotalPage(int totalPageNumber)       //总页优先级高
{
    if (totalPageNumber < 1) {                          //总页设置超出最小范围
        if (_currentPageNumber <= 1)  _totalPageNumber = 1;
        else _totalPageNumber = _currentPageNumber;
    }
    else if (totalPageNumber < _currentPageNumber){     //总页设置小于当前页
        _totalPageNumber = totalPageNumber;
        _currentPageNumber = totalPageNumber;

    }
    else {
        _totalPageNumber = totalPageNumber;             //正常
    }
    updatePageNumber();
}

void PageNumberControl::setCurrentAndTotalPage(int currentPageNumber, int totalPageNumber)
{
    if (currentPageNumber > totalPageNumber)    //当前页范围过大，以总页数为优先级
        _currentPageNumber = totalPageNumber;
    setTotalPage(totalPageNumber);
    setCurrentPage(currentPageNumber);

}
void PageNumberControl::slotForwardPage()              //向前翻页
{
    _currentPageNumber--;
    emit currentPageChanged(_currentPageNumber);      //发送页面改变信号
    updatePageNumber();
}

void PageNumberControl::slotBackwardPage()             //向后翻页
{
    _currentPageNumber++;
    emit currentPageChanged(_currentPageNumber);      //发送页面改变信号
    updatePageNumber();
}
void PageNumberControl::updatePageNumber()
{
    //翻页更新
    if (_currentPageNumber <= 1) {
        forwardBtn->enabled(false);
    }
    else {
        forwardBtn->enabled(true);
    }
    if (_currentPageNumber >= _totalPageNumber) {
        backwardBtn->enabled(false);
    }
    else {
        backwardBtn->enabled(true);
    }
    QFontMetrics currentMetrics(currentPageLabel->font());
    int currentTextWidth = currentMetrics.width(QString::number(_currentPageNumber));
    int currentTextHeight = currentMetrics.height();
    QFontMetrics totalMetrics(totalPageLabel->font());
    int totalTextWidth = totalMetrics.width(QString::number(_totalPageNumber));
    int totalTextHeight = totalMetrics.height();

    currentPageLabel->resize(currentTextWidth, currentTextHeight);
    totalPageLabel->resize(totalTextWidth + 1, totalTextHeight);

    currentPageLabel->move(38, 0);
    middleLabel->move(39 + currentTextWidth, 0);
    totalPageLabel->move(44 + currentTextWidth, 0);

    currentPageLabel->setText(QString::number(_currentPageNumber));
    totalPageLabel->setText(QString::number(_totalPageNumber));
}
void PageNumberControl::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    update();
}

void PageNumberControl::setCluster(bool cluster)
{
    _cluster = cluster;
    if(_cluster){

    forwardBtn->setText("");


    backwardBtn->setText("");

    currentPageLabel->hide();
    middleLabel->hide();
    totalPageLabel->hide();
    }
}

void PageNumberControl::paintEvent(QPaintEvent *event)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, backgroundColor);
    setPalette(pal);

    QWidget::paintEvent(event);
}

