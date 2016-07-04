#include "custompagenumber.h"

CustomPageNumber::CustomPageNumber(QWidget *parent)
    : QWidget(parent)
    , pageTitle("")
    , sumNumber(0)
    , _homeText(QString("home"))
    , _lastText(QString("last"))
    , _currentColor(QColor("#2894ca"))
    , _hoverColor(QColor("#666666"))
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);

    backgroundColor = QColor(0xFF,0xFF,0xFF,0x00);
    _currentPageNumber = 1;
    _totalPageNumber = 1;

    currentPageLabel = new QLabel(this);
    currentPageLabel->setFont(QFont("arial", 10, QFont::Normal));
    currentPageLabel->setStyleSheet("color:#666666");

    forwardBtn = new CustomBtnSELF(this);
    forwardBtn->SetImgs(":/resources/images/pagination_previous_hover.png", ":/resources/images/pagination_previous.png", ":/resources/images/pagination_previous_disable.png", "");
    forwardBtn->resize(18, 18);
    connect(forwardBtn, SIGNAL(clicked()), this, SLOT(slotForwardPage()));

    backwardBtn = new CustomBtnSELF(this);
    backwardBtn->SetImgs(":/resources/images/pagination_next_hover.png", ":/resources/images/pagination_next.png", ":/resources/images/pagination_next_disable.png", "");
    backwardBtn->resize(17, 18);
    connect(backwardBtn, SIGNAL(clicked()), this, SLOT(slotBackwardPage()));


    firstPageBtn = new CustomBtnSELF(this);
    firstPageBtn->setText(_homeText,
                          _currentColor,
                          _hoverColor,
                          QFont("", 9, QFont::Black),
                          CustomBtnSELF::center,
                          true);
    firstPageBtn->resize(30, 18);
    connect(firstPageBtn, SIGNAL(clicked()), this, SLOT(slotFirstPage()));
    lastPageBtn = new CustomBtnSELF(this);
    lastPageBtn->setText(_lastText,
                          _currentColor,
                          _hoverColor,
                          QFont("", 9, QFont::Black),
                          CustomBtnSELF::center,
                          true);
    lastPageBtn->resize(30, 18);
    connect(lastPageBtn, SIGNAL(clicked()), this, SLOT(slotLastPage()));

    //updatePageNumber();

    //resize(695, 15);
    setWindowFlags(Qt::FramelessWindowHint);
}

CustomPageNumber::~CustomPageNumber()
{
}

void CustomPageNumber::setHomeAndLastText(const QString &home, const QString& last)
{
    _homeText = home;
    _lastText = last;
    firstPageBtn->setText(_homeText,
                          _currentColor,
                          _hoverColor,
                          QFont("", 9, QFont::Black),
                          CustomBtnSELF::center,
                          true);
    firstPageBtn->setUnableColor(_hoverColor);
    lastPageBtn->setText(_lastText,
                          _currentColor,
                          _hoverColor,
                          QFont("", 9, QFont::Black),
                          CustomBtnSELF::center,
                          true);
    lastPageBtn->setUnableColor(_hoverColor);

}
void CustomPageNumber::setTitle(const QString &strTitle, const int sum)
{
     pageTitle = strTitle;
     sumNumber = sum;
     updatePageNumber();
}

void CustomPageNumber::setColor(const QColor &currentColor, const QColor &hoverColor)
{
    _currentColor = currentColor;
    _hoverColor = hoverColor;
    firstPageBtn->setText(_homeText,
                          _currentColor,
                          _hoverColor,
                          QFont("", 9, QFont::Black),
                          CustomBtnSELF::center,
                          true);
    firstPageBtn->setUnableColor(_hoverColor);
    lastPageBtn->setText(_lastText,
                          _currentColor,
                          _hoverColor,
                          QFont("", 9, QFont::Black),
                          CustomBtnSELF::center,
                          true);
    lastPageBtn->setUnableColor(_hoverColor);

}

void CustomPageNumber::setCurrentPage(int currentPageNumber)
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

void CustomPageNumber::setTotalPage(int totalPageNumber)       //总页优先级高
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

void CustomPageNumber::setCurrentAndTotalPage(int currentPageNumber, int totalPageNumber)
{
    if (currentPageNumber > totalPageNumber)    //当前页范围过大，以总页数为优先级
        _currentPageNumber = totalPageNumber;
    setTotalPage(totalPageNumber);
    setCurrentPage(currentPageNumber);

}
void CustomPageNumber::slotForwardPage()              //向前翻页
{
    _currentPageNumber--;
    updatePageNumber();
    emit currentPageChanged(_currentPageNumber);      //发送页面改变信号
}

void CustomPageNumber::slotBackwardPage()             //向后翻页
{
    _currentPageNumber++;
    updatePageNumber();
    emit currentPageChanged(_currentPageNumber);      //发送页面改变信号
}

void CustomPageNumber::slotFirstPage()
{
    _currentPageNumber = 1;
    updatePageNumber();
    emit currentPageChanged(_currentPageNumber);      //发送页面改变信号
}

void CustomPageNumber::slotLastPage()
{
    _currentPageNumber = _totalPageNumber;
    updatePageNumber();
    emit currentPageChanged(_currentPageNumber);      //发送页面改变信号
}
void CustomPageNumber::updatePageNumber()
{
    //翻页更新
    if (_currentPageNumber <= 1) {
        forwardBtn->enabled(false);
        firstPageBtn->enabled(false);
    }
    else {
        forwardBtn->enabled(true);
        firstPageBtn->enabled(true);
    }
    if (_currentPageNumber >= _totalPageNumber) {
        backwardBtn->enabled(false);
        lastPageBtn->enabled(false);
    }
    else {
        backwardBtn->enabled(true);
        lastPageBtn->enabled(true);
    }
    QString inforLabel = QString(tr("%1:%2  %3/%4").arg(pageTitle).arg(QString::number(sumNumber))  \
                                 .arg(QString::number(_currentPageNumber)).arg(QString::number(_totalPageNumber)));

    currentPageLabel->setText(inforLabel);
    resize(boundingRect().width(), boundingRect().height());
}
QRectF CustomPageNumber::boundingRect()
{
    QFontMetrics currentMetrics(currentPageLabel->font());
    int currentTextWidth = currentMetrics.width(currentPageLabel->text());
    int currentTextHeight = currentMetrics.height();
    return QRectF(0, 0, currentTextWidth + 110, forwardBtn->height());
   
}
void CustomPageNumber::setBackgroundColor(const QColor &color)
{
    backgroundColor = color;
    update();
}
void CustomPageNumber::paintEvent(QPaintEvent *event)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, backgroundColor);
    setPalette(pal);

    QWidget::paintEvent(event);
}

void CustomPageNumber::resizeEvent(QResizeEvent *event)
{
    currentPageLabel->setGeometry(0, 0, width() - 106, height());
    firstPageBtn->move(width() - 18*2 - 5 - 30*2, 0);
    lastPageBtn->move(width() - 18*2 - 5 - 30 , 0);
    forwardBtn->move(width() - 18*2, 0);
    backwardBtn->move(width() - 18, 0);
}
////////////////////////////////////////////////////////////
CustomPageNodeItem::CustomPageNodeItem(QGraphicsItem *parent) :
    QGraphicsProxyWidget(parent)
{
    _nodes = new CustomPageNumber;
    this->setWidget(_nodes);
    _nodes->show();

    connect(_nodes, SIGNAL(currentPageChanged(int)), this, SIGNAL(choosePage(int)));
}

void CustomPageNodeItem::update(const int &sum , const int &cur)
{
    _nodes->setCurrentAndTotalPage(cur, sum);
    QRectF rect = _nodes->boundingRect();
    resize(rect.width(), rect.height());
}

void CustomPageNodeItem::setCurrent(const int &cur)
{
    _nodes->setCurrentPage(cur);
}
void CustomPageNodeItem::setSum(const int &sum)
{
    _nodes->setTotalPage(sum);
}
int CustomPageNodeItem::getCurrent()
{
    return _nodes->getCurrent();
}
void CustomPageNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter(true);
    QGraphicsProxyWidget::hoverEnterEvent(event);
}
void CustomPageNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    emit hoverEnter(false);
    QGraphicsProxyWidget::hoverLeaveEvent(event);
}

void CustomPageNodeItem::setTitle(const QString &strTitle, const int sum)
{
    _nodes->setTitle(strTitle, sum);
}

void CustomPageNodeItem::setHomeAndLastText(const QString &home, const QString& last)
{
    _nodes->setHomeAndLastText(home, last);
}

void CustomPageNodeItem::setColor(const QColor &currentColor, const QColor &hoverColor)
{
    _nodes->setColor(currentColor, hoverColor);
}
/******************************************/
CustomBtnSELF::CustomBtnSELF(QWidget *parent , const style &stl) :
    QWidget(parent, Qt::FramelessWindowHint)
  , _bHover(false)
  , _bEnabled(true)
  , _bPressed(false)
  , _bCurrent(false)
  , _bError(false)
  , _textUnderLine(false)
  , _id(-1)
  , _style(stl)
  , _fillColor(false)
  , _key(0)
  , _textLength(-1)
  , _data(NULL)
{
    setStyleSheet("background-color:rgba(0,0,0,0)");

    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    setCursor(Qt::PointingHandCursor);
    _movieLabel = new QLabel(this);
    _movie = new QMovie(":/resources/images/loading.gif");
    _movieLabel->setMovie(_movie);
//    _movie->start();
    _movieLabel->move(0,0);
    _movieLabel->setVisible(false);

    unableColor = QColor("#9ca3a5");
}

void CustomBtnSELF::resizeEvent ( QResizeEvent * event )
{
    _movieLabel->move(width() / 2 - 8, height() / 2 - 8);
}

void CustomBtnSELF::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int pixWidth = 0;

 //   painter.fillRect(this->rect(), Qt::black);
    if (_fillColor) {
        if (_bHover)
            painter.fillRect(this->rect(), _backHoverColor);
        else
            painter.fillRect(this->rect(), _backColor);
    }
    else {
        QPixmap pixmap;
        if (!_movieLabel->isVisible()) {
            if (_bError) {
                if (!_errorImg.isEmpty())
                    pixmap = _errorNoteImage;
            }
            else if (!_bEnabled) {
                if (!_strDisable.isEmpty())
                    pixmap = _disableImage;
            }
            else if ((_bPressed || _bCurrent) && _strCurrent != "") {
                pixmap = _currentImage;
            }
            else if(_bHover) {
                if (!_strHover.isEmpty())
                    pixmap = _hoverImage;
            }
            else {
                if (!_strNormal.isEmpty())
                    pixmap = _normalImage;
            }

            painter.drawPixmap(pixmap.rect(),pixmap);
            pixWidth = pixmap.width();
        }
    }
    if (_text != "") {

        if (!_bEnabled)
            painter.setPen(QPen(unableColor));
  //      if ((_bPressed || _bCurrent || _bHover) && _strCurrent != "")
   //     else if (_bPressed || _bCurrent || _bHover)
        else if (_bCurrent || _bHover)
            painter.setPen(QPen(_textHoverColor));
        else
            painter.setPen(QPen(_textColor));

        painter.setFont(_font);
        QFontMetrics metrics(painter.font());
        int textWidth = metrics.width(_text);
        int textHeight = metrics.height();

        int leftP = (width() - textWidth)/2;
        if (_text_pos == right)
            leftP = pixWidth + 3;
        else if (_text_pos == left)
            leftP = 8;
        int top = (height() - textHeight)/2;
        QByteArray data = _text.toAscii();
        if (_textLength != -1) {
            data = _text.mid(0, _textLength).toAscii();
            if (_text.length() > _textLength)
                data += "...";
        }
   //     QRect tR = QRect(leftP ,top ,width() - 2*leftP, height() - 2 * top);
        QRect tR = QRect(leftP ,top ,textWidth + 2, height() - 2 * top);
        painter.drawText(tR, QString::fromLocal8Bit(data.data()));

        if (_textUnderLine && !_bPressed && !_bHover && _bEnabled)
            painter.drawLine(tR.left(),tR.bottom(), tR.right(), tR.bottom());
    }

    QWidget::paintEvent(event);
}

void CustomBtnSELF::mousePressEvent ( QMouseEvent * event)
{
    if (!_bEnabled)
        return;


    if (_bCurrent && _style == current_stay) {
        repaint();
        return;
    }

    _bPressed = true;

    if (_style == current_stay && _bEnabled)
        _bCurrent = true;
    repaint();
  //  if (!_style == current_stay || !_bCurrent) {
        emit clicked(this);
        emit clicked();
 //   }
//    QWidget::mousePressEvent(event);
}

void CustomBtnSELF::mouseReleaseEvent ( QMouseEvent * event )
{
    _bPressed = false;
    repaint();
    QWidget::mouseReleaseEvent(event);
}

void CustomBtnSELF::SetHoverImg(const QString &strOn,
                            const int &imgWidth , const int &imgHeight)
{
    _strHover = strOn;
    _hoverImage.load(_strHover);

    if (imgWidth != -1 && imgHeight != -1) {
        _hoverImage = _hoverImage.scaled(imgWidth, imgHeight);
    }
}

void CustomBtnSELF::SetNormalImg(const QString &strOff,
                             const int &imgWidth , const int &imgHeight)
{
    _strNormal = strOff;
    _normalImage.load(_strNormal);
    if (imgWidth != -1 && imgHeight != -1) {
        _normalImage = _normalImage.scaled(imgWidth, imgHeight);
    }
}

void CustomBtnSELF::clearState()
{
    _bHover = false;
    _bPressed = false;
    _bCurrent = false;
    repaint();
}

void CustomBtnSELF::setUnableColor(const QColor &color)
{
    unableColor = color;
}

void CustomBtnSELF::enterEvent ( QEvent * event )
{
    QToolTip::showText( QCursor::pos(), _tooltipText);
    _bHover = true;
    repaint();
}

void CustomBtnSELF::leaveEvent ( QEvent * event )
{
    _bHover = false;
    repaint();
}

void CustomBtnSELF::SetHover(const bool &bOn)
{
    _bHover = bOn;
}


void CustomBtnSELF::closeEvent ( QCloseEvent * event )
{
    clearState();
    QWidget::closeEvent(event);
}

void CustomBtnSELF::setText(const QString &strText,
                        const QColor &textColor,
                        const QColor &textCurColor,
                        const QFont &font,
                        const text_pos &text_pos,
                        const bool &underLine)
{
    _textUnderLine = underLine;
    _text = strText;
    _showText = strText;
    if (_textLength != -1) {
        _showText = _text.mid(0, _textLength);
        if (_text.length() > _textLength)
            _showText += "...";
    }

    _textColor = textColor;
    _textHoverColor = textCurColor;
    _font = font;

    _text_pos = text_pos;
}

void CustomBtnSELF::enabled(const bool &bEnable)
{
    _bEnabled = bEnable;
    if (!bEnable) {
        _bPressed = false;
        _bCurrent = false;
        _bHover = false;
//        _movieLabel->setVisible(false);
        setCursor(Qt::ArrowCursor);
        this->releaseMouse();
    }
    else {
        setCursor(Qt::PointingHandCursor);
    }
    setEnabled(bEnable);
    repaint();
//    update();
}

void CustomBtnSELF::SetDisabledImg(const QString &strEnabled,
                               const int &imgWidth , const int &imgHeight)
{
    _strDisable = strEnabled;
    _disableImage.load(_strDisable);
    if (imgWidth != -1 && imgHeight != -1) {
        _disableImage = _disableImage.scaled(imgWidth, imgHeight);
    }
}

int CustomBtnSELF::ID()
{
    return _id;
}

void CustomBtnSELF::setID(const int &id)
{
    _id = id;
}

QString CustomBtnSELF::text()
{
    return _text;
}

void CustomBtnSELF::SetCurrentImg(const QString &strCurrent,
                              const int &imgWidth , const int &imgHeight)
{
    _strCurrent = strCurrent;
    _currentImage.load(_strCurrent);
    if (imgWidth != -1 && imgHeight != -1) {
        _currentImage = _currentImage.scaled(imgWidth, imgHeight);
    }

}

void CustomBtnSELF::setErrorImg(const QString &errorImg,
                 const int &imgWidth, const int &imgHeight)
{
    _errorImg = errorImg;
    _errorNoteImage.load(_errorImg);
    if (imgWidth != -1 && imgHeight != -1) {
        _errorNoteImage = _errorNoteImage.scaled(imgWidth, imgHeight);
    }
}
void CustomBtnSELF::SetImgs(const QString &strOn, const QString &strOff,
             const QString &disabled, const QString &strCurrent,
                        const int &imgWidth , const int &imgHeight)
{
    this->SetNormalImg(strOff, imgWidth, imgHeight);
    this->SetHoverImg(strOn, imgWidth, imgHeight);
    this->SetDisabledImg(disabled, imgWidth, imgHeight);
    this->SetCurrentImg(strCurrent, imgWidth, imgHeight);
}

void CustomBtnSELF::currentRelease()
{
    _bCurrent = false;
    _bPressed = false;
    _bHover = false;
    repaint();
}

void CustomBtnSELF::setCurrent(const bool &cur)
{
    if (_style != current_stay)
        return;

    _bCurrent = cur;
    if (!cur) {
        _bPressed = false;
        _bHover = false;
    }
    repaint();
}

void CustomBtnSELF::focusOutEvent ( QFocusEvent * event )
{
    _bHover = false;
    setCurrent(false);
    update();
}

void CustomBtnSELF::focusInEvent ( QFocusEvent * event )
{
    _bHover = true;
    setCurrent(true);
    update();
}

void CustomBtnSELF::keyPressEvent ( QKeyEvent * event )
{
    update();
    if ((_bCurrent &&
             event->key() == Qt::Key_Return )||
              event->key() == _key) {
        emit clicked();
        emit clicked(this);
    }
    QWidget::keyPressEvent(event);
}

void CustomBtnSELF::setError(const bool &err)
{
    _bError = err;
    repaint();
}

void CustomBtnSELF::showGif(const bool &Gif)
{
    if (Gif)
        _movie->start();
    else
        _movie->stop();

    _movieLabel->setVisible(Gif);
}

void CustomBtnSELF::setGif(const QString &fileName)
{
    _movie->setFileName(fileName);
    if (_movie->state() == QMovie::Running) {
        _movie->stop();
        _movie->start();
    }
}

void CustomBtnSELF::setBackgroundColor(QColor backColor, QColor backHoverColor)
{
    _backColor = backColor;
    _backHoverColor = backHoverColor;
    _fillColor = true;
}
