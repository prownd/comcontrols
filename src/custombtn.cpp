#include "custombtn.h"
//#include "qvmanager.h"
#include <QPainter>
#include <QColor>
#include <QFont>
#include <QDesktopServices>
#include <QFontMetrics>
#include <QByteArray>
#include <QTextCodec>
#include <QKeyEvent>
#include <QDebug>
#include <QToolTip>
#include <QLabel>
#include <QMovie>

void DrawImg(QPainter* pPainter, const QString &strImgPath, const QRect &rect);
void DrawImg(QPainter* pPainter, const QString &strImgPath, const int &x, const int &y, const QSize &size);
CustomLabel::CustomLabel(QWidget *parent) : QWidget(parent,Qt::FramelessWindowHint)
  , _bePressed(false)
  , _beHovered(false)
  , _enable(false)
{
    setStyleSheet("background-color:rgba(0,0,0,0)");
    QTextCodec *codec = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//    connect(QvManager::getManager(), SIGNAL(newNodeAdded(Node*)), this, SLOT(refresh()));
}

void CustomLabel::setEnable(bool enable)
{
    this->setEnabled(enable);
    _enable = enable;
    if (!_enable)
        setCursor(Qt::ArrowCursor);
    else
        setCursor(Qt::PointingHandCursor);
}
void CustomLabel::refresh()
{
    this->update();
}

void CustomLabel::paintEvent(QPaintEvent *event)
{
//    if(QvManager::getManager()->count() == 0)
//        _enable = false;
//    else
//        _enable = true;
    QPainter painter(this);
    painter.setFont(QFont("",11,QFont::Bold));

    QFontMetrics metrics(painter.font());
    if(!_enable)
    {
        painter.setPen(QColor(96,96,96,255));
        painter.drawText(QRectF(width() / 2 - metrics.width("?")/2, 0, width(), height()),QString("?"));
    }
    else
    {
        painter.setPen(QColor(255,255,255,255));
        painter.drawText(QRectF(width() / 2 - metrics.width("?")/2, 0, width(), height()),QString("?"));
    }

}
void CustomLabel::mousePressEvent(QMouseEvent *event)
{
    _bePressed = true;
    if(_enable)
    {
  //      QUrl _url = QString("http://") + QvManager::getManager()->at(0)->host() + QString("/faq.html");
  //      QDesktopServices::openUrl(_url);
    }
}
void CustomLabel::mouseReleaseEvent(QMouseEvent *event)
{
    _bePressed = false;
    QWidget::mouseReleaseEvent(event);
}
void CustomLabel::enterEvent(QEvent *event)
{
    _beHovered = true;
    QWidget::enterEvent(event);
}
void CustomLabel::leaveEvent(QEvent *event)
{
    _beHovered = false;
    QWidget::leaveEvent(event);
}

CustomBtn::CustomBtn(QWidget *parent , const style &stl) :
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
}

void CustomBtn::resizeEvent ( QResizeEvent * event )
{
    _movieLabel->move(width() / 2 - 8, height() / 2 - 8);
}

void CustomBtn::paintEvent(QPaintEvent *event)
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
            painter.setPen(QPen(QColor("#9ca3a5")));
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

        if (_textUnderLine)
            painter.drawLine(tR.left(),tR.bottom(), tR.right(), tR.bottom());
    }

    QWidget::paintEvent(event);
}

void CustomBtn::mousePressEvent ( QMouseEvent * event)
{
    if (!_bEnabled)
        return;

    if (_bCurrent && _style == current_stay) {
        repaint();
        emit mousePressed();
        return;
    }

    _bPressed = true;

    if (_style == current_stay && _bEnabled)
        _bCurrent = true;
    repaint();
  //  if (!_style == current_stay || !_bCurrent) {
        emit clicked(this);
        emit clicked();
        emit mousePressed();
 //   }
//    QWidget::mousePressEvent(event);
}

void CustomBtn::mouseReleaseEvent ( QMouseEvent * event )
{
    _bPressed = false;
    repaint();
    QWidget::mouseReleaseEvent(event);
}

void CustomBtn::SetHoverImg(const QString &strOn,
                            const int &imgWidth , const int &imgHeight)
{
    _strHover = strOn;
    _hoverImage.load(_strHover);
 
    if (imgWidth != -1 && imgHeight != -1) {
        _hoverImage = _hoverImage.scaled(imgWidth, imgHeight);
    }
}

void CustomBtn::SetNormalImg(const QString &strOff,
                             const int &imgWidth , const int &imgHeight)
{
    _strNormal = strOff;
    _normalImage.load(_strNormal);
    if (imgWidth != -1 && imgHeight != -1) {
        _normalImage = _normalImage.scaled(imgWidth, imgHeight);
    }
}

void CustomBtn::clearState()
{
    _bHover = false;
    _bPressed = false;
    _bCurrent = false;
    repaint();
}

void CustomBtn::enterEvent ( QEvent * event )
{
    QToolTip::showText( QCursor::pos(), _tooltipText);
    _bHover = true;
    repaint();
}

void CustomBtn::leaveEvent ( QEvent * event )
{
    _bHover = false;
    repaint();
}

void CustomBtn::SetHover(const bool &bOn)
{
    _bHover = bOn;
}


void CustomBtn::closeEvent ( QCloseEvent * event )
{
    clearState();
    QWidget::closeEvent(event);
}

void CustomBtn::setText(const QString &strText,
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

void CustomBtn::enabled(const bool &bEnable)
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

void CustomBtn::SetDisabledImg(const QString &strEnabled,
                               const int &imgWidth , const int &imgHeight)
{
    _strDisable = strEnabled;
    _disableImage.load(_strDisable);
    if (imgWidth != -1 && imgHeight != -1) {
        _disableImage = _disableImage.scaled(imgWidth, imgHeight);
    }
}

int CustomBtn::ID()
{
    return _id;
}

void CustomBtn::setID(const int &id)
{
    _id = id;
}

QString CustomBtn::text()
{
    return _text;
}

void CustomBtn::SetCurrentImg(const QString &strCurrent,
                              const int &imgWidth , const int &imgHeight)
{
    _strCurrent = strCurrent;
    _currentImage.load(_strCurrent);
    if (imgWidth != -1 && imgHeight != -1) {
        _currentImage = _currentImage.scaled(imgWidth, imgHeight);
    }
}

void CustomBtn::setErrorImg(const QString &errorImg,
                 const int &imgWidth, const int &imgHeight)
{
    _errorImg = errorImg;
    _errorNoteImage.load(_errorImg);
    if (imgWidth != -1 && imgHeight != -1) {
        _errorNoteImage = _errorNoteImage.scaled(imgWidth, imgHeight);
    }
}
void CustomBtn::SetImgs(const QString &strOn, const QString &strOff,
             const QString &disabled, const QString &strCurrent,
                        const int &imgWidth , const int &imgHeight)
{
    this->SetNormalImg(strOff, imgWidth, imgHeight);
    this->SetHoverImg(strOn, imgWidth, imgHeight);
    this->SetDisabledImg(disabled, imgWidth, imgHeight);
    this->SetCurrentImg(strCurrent, imgWidth, imgHeight);
}

void CustomBtn::currentRelease()
{
    _bCurrent = false;
    _bPressed = false;
    _bHover = false;
    repaint();
}

void CustomBtn::setCurrent(const bool &cur)
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

void CustomBtn::focusOutEvent ( QFocusEvent * event )
{
    _bHover = false;
    setCurrent(false);
    update();
}

void CustomBtn::focusInEvent ( QFocusEvent * event )
{
    _bHover = true;
    setCurrent(true);
    update();
}

void CustomBtn::keyPressEvent ( QKeyEvent * event )
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

void CustomBtn::setError(const bool &err)
{
    _bError = err;
    repaint();
}

void CustomBtn::showGif(const bool &Gif)
{
    if (Gif)
        _movie->start();
    else
        _movie->stop();

    _movieLabel->setVisible(Gif);
}

void CustomBtn::setGif(const QString &fileName)
{
    _movie->setFileName(fileName);
    if (_movie->state() == QMovie::Running) {
        _movie->stop();
        _movie->start();
    }
}

void CustomBtn::setBackgroundColor(QColor backColor, QColor backHoverColor)
{
    _backColor = backColor;
    _backHoverColor = backHoverColor;
    _fillColor = true;
}

//////////////////////////////////////////////////////////////
CustomRadioButton::CustomRadioButton(QWidget * parent)
    : QRadioButton(parent)
    , _data(NULL)
{
    _showTextCount = 10;

    connect(this, SIGNAL(toggled(bool)), this , SLOT(choosen(bool)));
}

void CustomRadioButton::paintEvent ( QPaintEvent *event )
{
    QRadioButton::paintEvent(event);

    QPainter painter(this);
    painter.setPen(QPen(_textColor));
    QFontMetrics met(this->font());
    painter.drawText(QRect(20,height() / 2 - met.height() / 2,width(), 20), _text);
}

void CustomRadioButton::setText(const QString &text, const QColor &textColor)
{
    this->setToolTip(text);
    _text = text;
    if (text.length() > _showTextCount) {
        _text = text.mid(0, _showTextCount);
        _text += "...";
    }
    _textColor = textColor;
}

void CustomRadioButton::choosen(const bool &che)
{
    if (che)
        emit checked(_data);
}

