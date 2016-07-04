#include "customlineedit.h"
CustomLineEdit::CustomLineEdit(QString hint, QWidget *parent, const bool &showImg):QLineEdit(parent)
, _hint(hint)
, _error(false)
, _focusFlag(false)
, _state(edit_normal)
, _showImg(showImg)
{
    setMinimumSize(QSize(10, 10));
    setContextMenuPolicy(Qt::NoContextMenu);

    setStyleSheet("border: 0px solid gray; background:transparent; margin-left:5px;margin-right:5px;");
    LineEditImage* normalImg = creLineEditImage(edit_normal);
    loadImage(normalImg, QString(":/resources/images/input_left.png"), QString(":/resources/images/input_right.png"), QString(":/resources/images/input_upside.png"), QString(":/resources/images/input_bottom.png"), QString(":/resources/images/input_topLeft.png"), QString(":/resources/images/input_bottomLeft"), QString(":/resources/images/input_topRight.png"), QString(":/resources/images/input_bottomRight.png"));
    _imageList << normalImg;
    LineEditImage* hoverImg = creLineEditImage(edit_hover);
    loadImage(hoverImg, QString(":/resources/images/input_left_hover.png"), QString(":/resources/images/input_right_hover.png"), QString(":/resources/images/input_upside_hover.png"), QString(":/resources/images/input_bottom_hover.png"), QString(":/resources/images/input_topLeft_hover.png"), QString(":/resources/images/input_bottomLeft_hover.png"), QString(":/resources/images/input_topRight_hover.png"), QString(":/resources/images/input_bottomRight_hover.png"));

    _imageList << hoverImg;
    LineEditImage* focusImg = creLineEditImage(edit_focus);
    loadImage(focusImg, QString(":/resources/images/input_left_focus.png"), QString(":/resources/images/input_right_focus.png"), QString(":/resources/images/input_upside_focus.png"), QString(":/resources/images/input_bottom_focus.png"), QString(":/resources/images/input_topLeft_focus.png"), QString(":/resources/images/input_bottomLeft_focus.png"), QString(":/resources/images/input_topRight_focus.png"), QString(":/resources/images/input_bottomRight_focus.png"));
    _imageList << focusImg;

    LineEditImage* abnormalImg = creLineEditImage(edit_abnormal);
    loadImage(abnormalImg, QString(":/resources/images/input_left_error.png"), QString(":/resources/images/input_right_error.png"), QString(":/resources/images/input_upside_error.png"), QString(":/resources/images/input_bottom_error.png"), QString(":/resources/images/input_topLeft_error.png"), QString(":/resources/images/input_bottomLeft_error"), QString(":/resources/images/input_topRight_error.png"), QString(":/resources/images/input_bottomRight_error.png"));
    _imageList << abnormalImg;
   
    resize(100, 20);    
}
CustomLineEdit::~CustomLineEdit()
{

}
void CustomLineEdit::paintEvent(QPaintEvent *event)
{
    QLineEdit::paintEvent(event);
    QPainter painter(this);

    if (_showImg)
    {
        LineEditImage* img = getLineEditImage(_state); 
        if(img)
        {
            painter.drawImage(QRect(0, 0, img->leftTop->width(), img->leftTop->height()), *(img->leftTop));
            painter.drawImage(QRect(img->leftTop->width(), 0, img->top->width(), img->top->height()), *(img->top));
            painter.drawImage(QRect(width() - img->rightTop->width(), 0, img->rightTop->width(), img->rightTop->height()), *(img->rightTop));
            painter.drawImage(QRect(0, img->leftTop->height(), img->left->width(), img->left->height()), *(img->left));
            painter.drawImage(QRect(width() - img->rightTop->width(), img->rightTop->height(), img->right->width(), img->right->height()), *(img->right));
            painter.drawImage(QRect(0, height() - img->leftBottom->height(), img->leftBottom->width(), img->leftBottom->height()), *(img->leftBottom));
            painter.drawImage(QRect(img->leftBottom->width(), height() - img->leftBottom->height(), img->bottom->width(), img->bottom->height()), *(img->bottom));
            painter.drawImage(QRect(width() - img->rightBottom->width(), height() - img->rightBottom->height(), img->rightBottom->width(), img->rightBottom->height()), *(img->rightBottom));
        }
    }
    if (!text().isEmpty())
        return;
    QFontMetrics fontMetrics = painter.fontMetrics();
    QRect rt = rect();
    int length = (rt.width() - fontMetrics.width(_hint))/2;
    painter.setPen(QPen(QColor("#999999")));
    painter.drawText(rt.translated(length,0), Qt::AlignLeft | Qt::AlignVCenter | Qt::TextHideMnemonic, _hint);
}

void CustomLineEdit::setState(LineEditState state)
{
    _state = state;
    repaint();
}

void CustomLineEdit::focusInEvent(QFocusEvent *event)
{
    if (!_error) {
        setState(edit_focus);
    }
    _focusFlag = true;
    emit focusIn();
    QLineEdit::focusInEvent(event);
}

void CustomLineEdit::focusOutEvent(QFocusEvent *event)
{
    if (!_error) {
        setState(edit_normal);
    }
    _focusFlag = false;

    //emit loseFocus();
    QLineEdit::focusOutEvent(event);
}

void CustomLineEdit::enterEvent ( QEvent * event )
{
    if (!_error)
        setState(edit_hover);

    QLineEdit::enterEvent(event);
}

void CustomLineEdit::resizeEvent(QResizeEvent* event)
{
    QLineEdit::resizeEvent(event);
    for(int i = 0 ; i < _imageList.size(); i++)
    {
        _imageList.at(i)->scaled(width(), height());
    }
}
void CustomLineEdit::leaveEvent ( QEvent * event )
{
    if (!_error) {
        if(_focusFlag == true)  setState(edit_focus);
        else  setState(edit_normal);
    }
    //emit loseFocus();
    QLineEdit::leaveEvent(event);
}

void CustomLineEdit::setError(const bool &error)
{
    _error = error;
    if (_error)
        setState(edit_abnormal);
    else if(_focusFlag == true)
        setState(edit_focus);
    else
        setState(edit_normal);
}

LineEditImage* CustomLineEdit::creLineEditImage(LineEditState state)
{
    LineEditImage* image = new LineEditImage;
        image->state = state;
    return image;
}
LineEditImage* CustomLineEdit::getLineEditImage(LineEditState state)
{
    for(int i = 0; i < _imageList.size(); i++)
    {
        if(_imageList.at(i)->state ==state)
             return _imageList.at(i);
    }
    return NULL;
}

void CustomLineEdit::loadImage(LineEditImage* image, QString left, QString right,
             QString top,  QString bottom, QString leftTop,QString leftBottom,QString rightTop,QString rightBottom)
{
    if(!image)
        return;
    if(!left.isEmpty())
       image->left = new QImage(left);
    if(!right.isEmpty())
       image->right = new QImage(right);
    if(!top.isEmpty())
       image->top = new QImage(top);
    if(!bottom.isEmpty())
       image->bottom = new QImage(bottom);
    if(!leftTop.isEmpty())
       image->leftTop = new QImage(leftTop);
    if(!leftBottom.isEmpty())
       image->leftBottom = new QImage(leftBottom);
    if(!rightTop.isEmpty())
       image->rightTop = new QImage(rightTop);
    if(!rightBottom.isEmpty())
       image->rightBottom = new QImage(rightBottom);
}

