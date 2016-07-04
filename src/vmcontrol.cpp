#include "vmcontrol.h"
#include "custombtn.h"
//#include "warningcenter.h"

#include <QtDebug>
#include <QVariant>

const int WIDTH_SIZE = 232;
const int HEIGHT_SIZE = 43;

VmmComboBox::VmmComboBox(QWidget *parent, QString hint) :
    QComboBox(parent)
    ,_error(false)
    ,_hint(hint)
{
    resize(WIDTH_SIZE,HEIGHT_SIZE);
    _input = new QImage(":/resources/images/input.png");
    _hover = new QImage(":/resources/images/input_focus.png");
    _errorImg = new QImage(":/resources/images/input_error.png");

    _dropDownButton = new QImage(":/resources/images/mode_warn.png");

    setImgs( _input);

    setStyleSheet("QComboBox{margin-left: 7px;margin-right: 7px;border: 0px;background:rgba(255,255,255,0);"
                 " border-style:flat;color:#19649f;}QComboBox::drop-down{image:url(:/resources/images/input_drop_down.png);"
                  " border-style:flat;position: relative;top: 14px; left: -8px;}"
                  "QComboBox QAbstractItemView::item{max-width: 60px;min-height: 20px}");

    QListView *listView = new QListView;
    listView->setStyleSheet("QListView{font-size: 11px;width:80px}"
                           " QListView::item:!selected{color: #19649f}"
                            "QListView::item:selected:active{background-color: #1275c3}"
                            "QListView::item:selected{color: white}");

    setView(listView);

    _defaultText.clear();
}

VmmComboBox::~VmmComboBox()
{

}
void VmmComboBox::setError(const bool &error)
{
    _error = error;
    if (_error)
        setImgs( _errorImg);
    else
        setImgs( _input);
}

void VmmComboBox::paintEvent(QPaintEvent *event)
{
    QComboBox::paintEvent(event);
    QPainter painter(this);
    if (currentIndex() == -1)
        painter.drawText(10, height()/2 + 5, _defaultText);

    *_showImg = _showImg->scaled(width(), height());
    painter.drawImage(QRect(0,0,width(), height()), *_showImg);
    if (currentIndex() != -1)
        return;
    QRect rt = rect();
    painter.setPen(QPen(QColor("#999999")));
    painter.drawText(rt.translated(10,0), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextHideMnemonic, _hint);
}

void VmmComboBox::setImgs(QImage *img)
{
    _showImg = img;
    repaint();
}

void VmmComboBox::focusInEvent(QFocusEvent *event)
{
    if (!_error)
        setImgs(_hover);
    QComboBox::focusInEvent(event);
}

void VmmComboBox::focusOutEvent(QFocusEvent *event)
{
    if (!_error)
        setImgs( _input);
    QComboBox::focusOutEvent(event);
}

VmmLineEdit::VmmLineEdit(QString hint, QWidget *parent, const bool &showImg)
    : QLineEdit(parent)
    , _input(NULL)
    , _hover(NULL)
    , _focus(NULL)
    , _abnormal(NULL)
    , _center(NULL)
    , _hint(hint)
    , _error(false)
    ,_focusFlag(false)
{
    setMouseTracking(true);
    setContextMenuPolicy(Qt::NoContextMenu);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Text, QColor(QRgb(0xff19649f)));
    setPalette(palette);

    resize(WIDTH_SIZE, HEIGHT_SIZE);
   // setMinimumSize(WIDTH_SIZE, HEIGHT_SIZE);

    setStyleSheet("border: 0px solid gray; background:rgba(255,255,255,0); margin-left:5px;margin-right:5px;");

    if (showImg) {
        _input = new QImage(":/resources/images/input.png");
        _hover = new QImage(":/resources/images/input_focus.png");
        _abnormal = new QImage(":/resources/images/input_error.png");
        _focus = new QImage(":/resources/images/input_focus.png");
    }
    setImgs(_input);
}

VmmLineEdit::~VmmLineEdit()
{

}

void VmmLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);
    QPainter painter(this);

    if (_center)
        painter.drawImage(QRect(0, 0, width(), height()), *_center);
    if (!text().isEmpty())
        return;
    QRect rt = rect();
    painter.setPen(QPen(QColor("#999999")));
    painter.drawText(rt.translated(10,0), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextHideMnemonic, _hint);
}

void VmmLineEdit::setImgs(QImage *img)
{
    _center = img;
    repaint();
}

void VmmLineEdit::focusInEvent(QFocusEvent *event)
{
    if (!_error) {
        setImgs(_focus);
    }
    _focusFlag = true;
    QLineEdit::focusInEvent(event);
}

void VmmLineEdit::focusOutEvent(QFocusEvent *event)
{
    if (!_error) {
        setImgs(_input);
    }
    _focusFlag = false;

    //emit loseFocus();
    QLineEdit::focusOutEvent(event);
}

void VmmLineEdit::enterEvent ( QEvent * event )
{
    if (!_error)
        setImgs(_hover);

    QLineEdit::enterEvent(event);
}

void VmmLineEdit::leaveEvent ( QEvent * event )
{
    if (!_error) {
        if(_focusFlag == true)  setImgs(_focus);
        else  setImgs(_input);
    }
    //emit loseFocus();
    QLineEdit::leaveEvent(event);
}

void VmmLineEdit::setError(const bool &error)
{
    _error = error;
    if (_error)
        setImgs(_abnormal);
    else if(_focusFlag == true)
        setImgs(_focus);
    else
        setImgs( _input);
}

void VmmLineEdit::resizeWidth(const int &width)
{
    resize(width, height());
    *_input = (*_input).scaled(QSize(width , height()));
    *_hover = (*_hover).scaled(QSize(width, height()));
    *_focus = (*_focus).scaled(QSize(width, height()));
    *_abnormal = (*_abnormal).scaled(QSize(width, height()));
    update();
}
void VmmLineEdit::setImgs(const QString &img, const QString &hoverImg,
             const QString &focusImg, const QString &abnormal)
{
    if (_input)
        _input->load(img);
    if (_hover)
        _hover->load(hoverImg);
    if (_focus)
        _focus->load(focusImg);
    if (_abnormal)
        _abnormal->load(abnormal);
}

///////////////////////////////////////////////////////////

VmmButtonLineEdit::VmmButtonLineEdit(QString hint , QWidget *parent, const bool &showImg)
    : VmmLineEdit(hint, parent, showImg)
{
    _btn = new CustomBtn(this);
    _btn->setCursor(QCursor(Qt::PointingHandCursor));

    _btn->installEventFilter(this);
    connect(_btn, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));

    _preDsp = new QLabel(this);
    _preDsp->move(0,0);
    _preDsp->setStyleSheet("color: #19649f;");

    setSize();

    setStyleSheet("border: 0px solid gray; background:rgba(255,255,255,0);");

}

void VmmButtonLineEdit::setButtonText(const QString &text)
{
    QFont font = this->font();
    font.setUnderline(true);
    _btn->setText(text, QColor("#5c9e2c"), QColor("#5c9e2c"), font);
    _btn->update();
    QFontMetrics metrics(this->font());

    _btn->setGeometry(QRect(width() - metrics.width(text) - 8,
                      height() / 2 - metrics.height() / 2,
                      metrics.width(text),
                      metrics.height()));
}

QString VmmButtonLineEdit::buttonText()
{
    return _btn->text();
}

void VmmButtonLineEdit::setPreDsp(const QString &dsp)
{
    int margin = 6;
    int frameWidth = 2;
    _preDsp->setText(dsp);
    QFontMetrics metrics(this->font());

    this->setTextMargins(metrics.width(dsp) + margin, 7, width() - _btn->x(), 10);
    _preDsp->setGeometry(QRect(frameWidth + margin, 15, metrics.width(dsp),metrics.height()));
}

void VmmButtonLineEdit::paintEvent ( QPaintEvent * event)
{
    if (!this->isReadOnly()) {
        QPainter painter(this);
        int left, right, top, bottom;
        this->getTextMargins(&left, &top, &right, &bottom);
        painter.drawLine(left, 27, left + 22, 27);
    }
    VmmLineEdit::paintEvent(event);
}

void VmmButtonLineEdit::setSize()
{
    setButtonText(buttonText());
}

void VmmButtonLineEdit::resizeEvent(QResizeEvent *event)
{
    setSize();

    QLineEdit::resizeEvent(event);
}

QString VmmButtonLineEdit::preDspText()
{
    return _preDsp->text();
}

////////////////////////////////////////////////////////////////

BtnEdit::BtnEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setContextMenuPolicy(Qt::NoContextMenu);
    setStyleSheet("border: 0px solid gray; background:rgba(255,255,255,0); color: #19649f;");
}

BtnEdit::~BtnEdit()
{

}

void BtnEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);

    QPainter painter(this);
    int left, right, top, bottom;
    this->getTextMargins(&left, &top, &right, &bottom);
#ifdef QT_WIN_CONFIG
    painter.drawLine(left, 14, left + 22, 14);
#else
    painter.drawLine(left + 2, 14, left + 22, 14);
#endif
}

void BtnEdit::focusInEvent(QFocusEvent *event)
{
    if (!hasFocus())
        setFocus();

    QLineEdit::focusInEvent(event);
}

void BtnEdit::focusOutEvent(QFocusEvent *event)
{
    emit focusOut();

    QLineEdit::focusOutEvent(event);
}

VmmLabel::VmmLabel(QWidget *parent)
    : QLabel(parent)
    , _error(false)

{
    setContextMenuPolicy(Qt::NoContextMenu);

    resize(WIDTH_SIZE, HEIGHT_SIZE);
    //setMinimumSize(WIDTH_SIZE, HEIGHT_SIZE);

    setStyleSheet("border: 0px solid gray; background:rgba(255,255,255,0);");

    _inputLeft = new QImage(":/resources/images/input_left_bg.png");
    _inputCenter = new QImage(":/resources/images/input_center_bg.png");
    _inputRight = new QImage(":/resources/images/input_right_bg.png");

    _hoverLeft = new QImage(":/resources/images/input_left_hover_bg.png");
    _hoverCenter = new QImage(":/resources/images/input_center_hover_bg.png");
    _hoverRight = new QImage(":/resources/images/input_right_hover_bg.png");

    _errorLeft = new QImage(":/resources/images/input_left_error_bg.png");
    _errorCenter = new QImage(":/resources/images/input_center_error_bg.png");
    _errorRight = new QImage(":/resources/images/input_right_error_bg.png");

    setImgs(_inputLeft, _inputCenter, _inputRight);

    _preDsp = new QLabel(this);
    _preDsp->move(0,0);
    _preDsp->setStyleSheet("color: #19649f;");

    _lineEdit = new BtnEdit(this);
    _lineEdit->resize(31, 15);
#ifdef QT_WIN_CONFIG
    _lineEdit->move(_preDsp->width() + 7, 8);
#else
    _lineEdit->move(_preDsp->width() + 8, 9);
#endif
    _lineEdit->installEventFilter(this);

//    QValidator *validator = new QIntValidator(0, 255, this);
    QValidator *validator = new QRegExpValidator(QRegExp(QString("(([1-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-4]))")), this );

    _lineEdit->setValidator(validator);
    _lineEdit->setVisible(false);

    _btn = new CustomBtn(this);
    _btn->setCursor(QCursor(Qt::PointingHandCursor));
    _btn->installEventFilter(this);

    connect(_lineEdit, SIGNAL(textChanged(QString)), this, SIGNAL(textChanged(QString)));
    connect(_lineEdit, SIGNAL(focusOut()), this, SIGNAL(focusOut()));
    connect(_btn, SIGNAL(clicked()), this, SIGNAL(buttonClicked()));
}

VmmLabel::~VmmLabel()
{

}

void VmmLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter painter(this);

    painter.drawImage(QRect(0, 0, _left->width(), height()), *_left);
    painter.drawImage(QRect(width() - _right->width(), 0, _right->width(), height()), *_right);
    painter.drawImage(QRect(_left->width(),0,width() - _left->width() - _right->width(), height()), *_center);
}

void VmmLabel::setImgs(QImage *strLeft, QImage *strCenter, QImage *strRight)
{
    _left = strLeft;
    _center = strCenter;
    _right = strRight;
    repaint();
}

void VmmLabel::setButtonText(const QString &text)
{
    QFont font = this->font();
    font.setUnderline(true);
    _btn->setText(text, QColor("#5c9e2c"), QColor("#5c9e2c"), font);
    _btn->update();
    QFontMetrics metrics(this->font());

    _btn->setGeometry(QRect(width() - metrics.width(text) - 8,
                            height() / 2 - metrics.height() / 2,
                            metrics.width(text),metrics.height()));
}

QString VmmLabel::buttonText()
{
    return _btn->text();
}

void VmmLabel::setPreDsp(const QString &dsp)
{
    int margin = 6;
    int frameWidth = 2;
    _preDsp->setText(dsp);
    QFontMetrics metrics(this->font());

    _preDsp->setGeometry(QRect(frameWidth + margin, 10, metrics.width(dsp), metrics.height()));
}

void VmmLabel::setLineEdit(const QString &text)
{
    _lineEdit->setText(text);
    _lineEdit->move(_preDsp->width() + 7, 8);
}

void VmmLabel::setSize()
{
    setButtonText(buttonText());
}

void VmmLabel::resizeEvent(QResizeEvent *event)
{
    setSize();

    QLabel::resizeEvent(event);
}

QString VmmLabel::preDspText()
{
    return _preDsp->text();
}

QString VmmLabel::lineEditText()
{
    return _lineEdit->text();
}

void VmmLabel::setLineEditShow(const bool &show)
{
    if (show) {
        _lineEdit->setVisible(true);

        /*
        if (!_lineEdit->hasFocus())
            _lineEdit->setFocus();
        */
    }
    else {
        _lineEdit->setVisible(false);
    }
}

void VmmLabel::setColor(const bool &out)
{
    if (!_error) {
        if (!out)
            setImgs(_hoverLeft, _hoverCenter,_hoverRight);
        else
            setImgs(_inputLeft, _inputCenter, _inputRight);
    }
}

void VmmLabel::setError(const bool &error)
{
    _error = error;
    if (_error)
        setImgs(_errorLeft, _errorCenter, _errorRight);
    else
        setImgs(_hoverLeft, _hoverCenter,_hoverRight);
}

void VmmLabel::resizeWidth(const int &width)
{
    resize(width, height());
}

//////////////////////////////////////////////////////////////


VmmSpinBox::VmmSpinBox(QWidget *parent) :
    QSpinBox(parent)
{
    resize(WIDTH_SIZE,HEIGHT_SIZE);
    setContextMenuPolicy(Qt::NoContextMenu);

    _inputLeft = new QImage(":/resources/images/input_left_bg.png");
    _inputCenter = new QImage(":/resources/images/input_center_bg.png");
    _inputRight = new QImage(":/resources/images/input_right_bg.png");

    _hoverLeft = new QImage(":/resources/images/input_left_hover_bg.png");
    _hoverCenter = new QImage(":/resources/images/input_center_hover_bg.png");
    _hoverRight = new QImage(":/resources/images/input_right_hover_bg.png");

    _errorLeft = new QImage(":/resources/images/input_left_error_bg.png");
    _errorCenter = new QImage(":/resources/images/input_center_error_bg.png");
    _errorRight = new QImage(":/resources/images/input_right_error_bg.png");

    setImgs(_inputLeft, _inputCenter, _inputRight);

    setStyleSheet("QSpinBox{margin-left:5px; border: 0px solid gray;\
                  background:rgba(255,255,255,0); border-style:flat;}\
                  QSpinBox::up-arrow{image:url(:/resources/images/input_pull_up.png);border-style:flat;}\
                  QSpinBox::down-arrow{image:url(:/resources/images/input_pull_down.png);border-style:flat; right:50px}");


    connect(this, SIGNAL(valueChanged(int)), this, SLOT(valChanged(int)));
}

VmmSpinBox::~VmmSpinBox()
{

}
QValidator::State VmmSpinBox::validate(QString &input, int &pos) const
{
    if(input == "0")
        return QValidator::Invalid;
    return QValidator::Acceptable;
}

void VmmSpinBox::paintEvent(QPaintEvent *event)
{
    QSpinBox::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, _left->width(), height()), *_left);
    painter.drawImage(QRect(width() - _right->width(), 0, _right->width(), height()), *_right);
    painter.drawImage(QRect(_left->width(),0,width() - _left->width() - _right->width(), height()), *_center);
}

void VmmSpinBox::setImgs(QImage *strLeft, QImage *strCenter, QImage *strRight)
{
    _left = strLeft;
    _center = strCenter;
    _right = strRight;
    repaint();
}

void VmmSpinBox::valChanged(int i)
{
    if ((i == minimum()) && (i == maximum()))
    {
        setStyleSheet("QSpinBox{margin-left:5px; border: 0px solid gray;\
                      background:rgba(255,255,255,0); border-style:flat;}\
                      QSpinBox::up-arrow{image:url(:/resources/images/input_drop_up_disabled.png);border-style:flat;}\
                      QSpinBox::down-arrow{image:url(:/resources/images/input_drop_down_disabled.png);border-style:flat; right:50px}");
    }
    else if (i == maximum()) {
        setStyleSheet("QSpinBox{margin-left:5px; border: 0px solid gray;\
                      background:rgba(255,255,255,0); border-style:flat;}\
                      QSpinBox::up-arrow{image:url(:/resources/images/input_drop_up_disabled.png);border-style:flat;}\
                      QSpinBox::down-arrow{image:url(:/resources/images/input_pull_down.png);border-style:flat; right:50px}");
    }
    else if (i == minimum()) {
        setStyleSheet("QSpinBox{margin-left:5px; border: 0px solid gray;\
                      background:rgba(255,255,255,0); border-style:flat;}\
                      QSpinBox::up-arrow{image:url(:/resources/images/input_pull_up.png);border-style:flat;}\
                      QSpinBox::down-arrow{image:url(:/resources/images/input_drop_down_disabled.png);border-style:flat; right:50px}");
    }
    else  {
        setStyleSheet("QSpinBox{margin-left:5px; border: 0px solid gray;\
                      background:rgba(255,255,255,0); border-style:flat;}\
                      QSpinBox::up-arrow{image:url(:/resources/images/input_pull_up.png);border-style:flat;}\
                      QSpinBox::down-arrow{image:url(:/resources/images/input_pull_down.png);border-style:flat; right:50px}");
    }
}

void VmmSpinBox::focusInEvent(QFocusEvent *event)
{
    setImgs(_hoverLeft, _hoverCenter,_hoverRight);
    QSpinBox::focusInEvent(event);
}

void VmmSpinBox::focusOutEvent(QFocusEvent *event)
{
    setImgs(_inputLeft, _inputCenter, _inputRight);
    QSpinBox::focusOutEvent(event);
}

VmmDoubleSpinBox::VmmDoubleSpinBox(QWidget *parent) :
    QDoubleSpinBox(parent)
{

    resize(WIDTH_SIZE,HEIGHT_SIZE);
    setContextMenuPolicy(Qt::NoContextMenu);

    _inputLeft = new QImage(":/resources/images/input_left_bg.png");
    _inputCenter = new QImage(":/resources/images/input_center_bg.png");
    _inputRight = new QImage(":/resources/images/input_right_bg.png");

    _hoverLeft = new QImage(":/resources/images/input_left_hover_bg.png");
    _hoverCenter = new QImage(":/resources/images/input_center_hover_bg.png");
    _hoverRight = new QImage(":/resources/images/input_right_hover_bg.png");

    _errorLeft = new QImage(":/resources/images/input_left_error_bg.png");
    _errorCenter = new QImage(":/resources/images/input_center_error_bg.png");
    _errorRight = new QImage(":/resources/images/input_right_error_bg.png");

    setImgs(_inputLeft, _inputCenter, _inputRight);

    setStyleSheet("QDoubleSpinBox{margin-left:5px; border: 0px solid gray;background:rgba(255,255,255,0);border-style:flat;}\
                  QDoubleSpinBox::up-arrow{image:url(:/resources/images/input_pull_up.png);border-style:flat;}\
                  QDoubleSpinBox::down-arrow{image:url(:/resources/images/input_pull_down.png);border-style:flat;}");
}

VmmDoubleSpinBox::~VmmDoubleSpinBox()
{

}

void VmmDoubleSpinBox::paintEvent(QPaintEvent *event)
{
    QDoubleSpinBox::paintEvent(event);
    QPainter painter(this);
    painter.drawImage(QRect(0, 0, _left->width(), height()), *_left);
    painter.drawImage(QRect(width() - _right->width(), 0, _right->width(), height()), *_right);
    painter.drawImage(QRect(_left->width(),0,width() - _left->width() - _right->width(), height()), *_center);
}

void VmmDoubleSpinBox::setImgs(QImage *strLeft, QImage *strCenter, QImage *strRight)
{
    _left = strLeft;
    _center = strCenter;
    _right = strRight;
    repaint();
}

void VmmDoubleSpinBox::focusInEvent(QFocusEvent *event)
{
    setImgs(_hoverLeft, _hoverCenter,_hoverRight);
    QDoubleSpinBox::focusInEvent(event);
}

void VmmDoubleSpinBox::focusOutEvent(QFocusEvent *event)
{
    setImgs(_inputLeft, _inputCenter, _inputRight);
    QDoubleSpinBox::focusOutEvent(event);
}


VmmTextEdit::VmmTextEdit(QString hint, QWidget *parent)
    : QTextEdit(parent)
    , _hint(hint)
{
    setContextMenuPolicy(Qt::NoContextMenu);
    resize(221, 69);
    setContentsMargins(0, 0, 0, 0);
    setAlignment(Qt::AlignLeft);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Text, QColor(QRgb(0xff19649f)));
    palette.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    setPalette(palette);

//    setStyleSheet("border: 0px solid gray; background:rgba(255,255,255,0); margin-left:5px;");

    setWordWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    setStyleSheet("QTextEdit {Border:Opx none black;}");
    _img = new QImage(":/resources/images/bewrite_input_bg.png");
}

VmmTextEdit::~VmmTextEdit()
{

}

void VmmTextEdit::paintEvent ( QPaintEvent * event )
{
    QTextEdit::paintEvent(event);
    QPainter painter(this->viewport());

   //     QPixmap pixmap(":/resources/images/bewrite_input_bg.png");
    //    painter.drawPixmap(rect(), pixmap);
        painter.drawImage(rect(), *_img);

        if (!toPlainText().isEmpty())
            return;
        QRect rt = rect();
        painter.setPen(QPen(QColor("#999999")));
   //     this->setPlainText(_hint);
        painter.drawText(QRect(7, 3, width(),40), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextHideMnemonic, _hint);
}

void VmmTextEdit::focusInEvent(QFocusEvent *event)
{
    if (!_error)
        _img->load(":/resources/images/bewrite_input_bg_hover.png");

    repaint();
    QTextEdit::focusInEvent(event);
}

void VmmTextEdit::focusOutEvent(QFocusEvent *event)
{
    if (!_error)
        _img->load(":/resources/images/bewrite_input_bg.png");

    QTextEdit::focusOutEvent(event);
}

void VmmTextEdit::setError(const bool &error)
{
    _error = error;
    if (_error)
        _img->load(":/resources/images/bewrite_input_bg_error.png");
    else
        _img->load(":/resources/images/bewrite_input_bg_hover.png");
}
//////////////////////////////////////////////////////////////////

