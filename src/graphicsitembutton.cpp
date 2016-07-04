#include "graphicsitembutton.h"
#include <QImage>
#include <QPainter>
#include <QFontMetrics>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsTextItem>
#include <QMimeData>
#include <QCursor>
#include <QDebug>
#include <QToolTip>

GraphicsItemButton::GraphicsItemButton(const QString &image, const QString &hoverImage,
                                       const QString &currentImage, const QString &disableImage,
                                       const style &stl
                                       , QGraphicsItem * parent,
                                       const int &imgWidth , const int &imgHeight, const text_pos &tp,
                                       const icon_pos &icp)
    : QGraphicsItem(parent)
    , _image(image)
    , _hoverImage(hoverImage)
    , _currentImage(currentImage)
    , _style(stl)
    , _font("", 9, QFont::Normal)
    , _textPos(tp)
    , _data(NULL)
    , _textColor(0,0,0)
    , _current(false)
    , _enable(true)
    , _hovered(false)
    , _menuHover(false)
    , _dragOver(false)
    , _underLine(false)
    , _hoverUnderLine(false)
    , _imgWidth(-1)
    , _iconPos(icp)
    , _hoverCursor(Qt::PointingHandCursor)
    , _textShowLen(1024)
    , _hoverToolTipText("")
{
    setAcceptHoverEvents(true);

    if (!image.isEmpty())
        _pixmap.load(image);
    if (!hoverImage.isEmpty())
        _hoverPixmap.load(hoverImage);
    if (!currentImage.isEmpty())
        _currentPixmap.load(currentImage);
    if (!disableImage.isEmpty())
        _disablePixmap.load(disableImage);


    _imgWidth = _pixmap.rect().width();
    if (imgWidth != -1 && imgHeight != -1){
        _imgWidth = imgWidth;
        if (!_pixmap.isNull())
            _pixmap = _pixmap.scaled(imgWidth, imgHeight);
        if (!_hoverPixmap.isNull())
            _hoverPixmap = _hoverPixmap.scaled(imgWidth, imgHeight);
        if (!_currentPixmap.isNull())
            _currentPixmap = _currentPixmap.scaled(imgWidth, imgHeight);
        if (!_disablePixmap.isNull())
            _disablePixmap = _disablePixmap.scaled(imgWidth, imgHeight);
    }

    _metrics = new QFontMetrics(_font);

    _width = 10;
    _height = 10;

    _textColor_hover = _textColor;
    _textColor_selected = _textColor;

    _viewSwitch_dropDown_hover.load(":/resources/images/viewSwitch_dropDown_hover.png");
    _viewSwitch_dropDown.load(":/resources/images/viewSwitch_dropDown.png");
}

QRectF GraphicsItemButton::boundingRect() const
{
    return QRectF(0,0,_width, _height);
}
void GraphicsItemButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    QColor textColor;

    int icon_top_pos = 0;

    if (!_enable) {
        textColor = QColor("#9ca3a5");
        if (_iconPos == icon_center)
            icon_top_pos = _height / 2 - _disablePixmap.height() / 2;
        painter->drawPixmap(QRect(0, icon_top_pos, _disablePixmap.width(), _disablePixmap.height()), _disablePixmap);
    }
    else if(_current && _currentImage != "") {
        textColor = _textColor_selected;
        if (_iconPos == icon_center)
            icon_top_pos = _height / 2 - _currentPixmap.height() / 2;
        painter->drawPixmap(QRect(0, icon_top_pos, _currentPixmap.width(), _currentPixmap.height()), _currentPixmap);

    }
    else if ( _hovered) {
        textColor = _textColor_hover;
        if (_iconPos == icon_center)
            icon_top_pos = _height / 2 - _hoverPixmap.height() / 2;
        painter->drawPixmap(QRect(0, icon_top_pos, _hoverPixmap.width(), _hoverPixmap.height()), _hoverPixmap);
    }
    else {
        textColor = _textColor;
        if (_iconPos == icon_center)
            icon_top_pos = _height / 2 - _pixmap.height() / 2;
        painter->drawPixmap(QRect(0, icon_top_pos, _pixmap.width(), _pixmap.height()), _pixmap);
    }

    //draw menu
    if (_menus.size() > 0) {
        QPixmap menuPixmap;
        if (_menuHover)
            menuPixmap = _viewSwitch_dropDown_hover;
        else
            menuPixmap = _viewSwitch_dropDown;

        painter->drawPixmap(_menuRect, menuPixmap);
    }

    //draw drag
    if (acceptDrops() && _dragEnterImage != "") {
        QPixmap pixmap;
        pixmap = _dragEnterImageImage;
        painter->drawPixmap(boundingRect().toRect(), pixmap);
    }
    //text
    if (_text == "")
        return;

    painter->setFont(_font);
    painter->setPen(QPen(textColor,1));

    QRect textR;
    if (_textPos == right) {
     //   if (_hovered && _underLine)
        if (_underLine)
            painter->drawLine(_pixmap.rect().right(), _height, _width,_height );
        if(_hovered && _hoverUnderLine)
            painter->drawLine(_pixmap.rect().right() + 3, _height, _width,_height );
        textR = QRect(_imgWidth  + 3, (boundingRect().height() - _metrics->height()) / 2, _metrics->width(_text), _metrics->height());
    }
    else if (_textPos == bottom) {
        int left = (_width - _metrics->width(_text)) / 2;
        left = left > 0 ? left : 0;
        textR = QRect(left, _height - _metrics->height(), _width, _metrics->height());
    }
    else if (_textPos == center) {
        int left = (_width - _metrics->width(_text)) / 2;
        left = left > 0 ? left : 0;
        if (_underLine)
            painter->drawLine(left, _height/2 + _metrics->height()/2 + 1, left + _metrics->width(_text), _height/2 + _metrics->height()/2 + 1);
        textR = QRect(left, _height/2 - _metrics->height()/2, _metrics->width(_text), _metrics->height());
    }
    else if (_textPos == left)
    {
        textR = QRect(5 + 8, (boundingRect().height() - _metrics->height()) / 2, _metrics->width(_text), _metrics->height());
    }
    painter->drawText(textR, Qt::TextSingleLine, _text);
}

void GraphicsItemButton::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
    if (_enable)
    {
        setCursor(_hoverCursor);
         if(!_hoverToolTipText.isEmpty())
            if (_text != _oriText)
                QToolTip::showText( QCursor::pos(),_oriText);
         else 
                QToolTip::showText( QCursor::pos(),_hoverToolTipText);
         _hovered = true;
         this->update();
    }
}

void GraphicsItemButton::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void GraphicsItemButton::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    if (!_enable)
        return;

    if (_menus.size() > 0 && _menuRect.contains(event->pos().x(), event->pos().y())) {
        return;
    }
    if (_style == current_stay && _current)
        return;

    if (_style == current_stay) {
        _current = true;
        update();
    }

    emit clicked();
    emit clicked(this);
}

void GraphicsItemButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _hovered = false;
    this->update();
}

void GraphicsItemButton::setCurrent(const bool &cur)
{
    _current = cur;
//    emit clicked();
//    emit clicked(this);

    update();
}
void GraphicsItemButton::setHover(const bool &hover)
{
    _hovered = hover;
    update();
}
void GraphicsItemButton::setEnable(const bool &en)
{
    _enable = en;
    if (!_enable)
        setCursor(QCursor(Qt::ArrowCursor));
    else
        setCursor(QCursor(Qt::PointingHandCursor));

    update();
}

void GraphicsItemButton::setDefaultTextColor(const QColor &tColor)
{
    _textColor = tColor;

    _textColor_hover = _textColor;
    _textColor_selected = _textColor;
    update();
}

void GraphicsItemButton::setFont(const QFont &font)
{
    delete _metrics;
    _metrics = new QFontMetrics(font);

    _font = font;
    update();
}

void GraphicsItemButton::setText(const QString &text)
{
    _oriText = text;
    if (text.length() > _textShowLen){
   //     setToolTip(text);
        _text = text.mid(0,_textShowLen - 1 - 2);
        _text += "...";
    }
    else {
        _text = text;
      //  setToolTip("");
    }
    update();
}

void GraphicsItemButton::setSize(const int width, const int height)
{
    _width = width;
    _height = height;

    _menuRect = QRect(_width - 16, 0, qMin(16, width) ,qMax(36, height));
}

void GraphicsItemButton::setTextPos(const text_pos &pos)
{
    _textPos = pos;
}

void GraphicsItemButton::setDataP(void* data)
{
    _data = data;
}

void* GraphicsItemButton::getData()
{
    return _data;
}

void GraphicsItemButton::addMenu(const QString &menu)
{
    _menus.append(menu);
}

void GraphicsItemButton::hoverMoveEvent ( QGraphicsSceneHoverEvent * event )
{
    if (_menus.size() > 0 && _menuRect.contains(event->pos().x(), event->pos().y()))
        _menuHover = true;
    else
        _menuHover = false;
    //cej 2013-10-29
//    update();
}

void GraphicsItemButton::setImage(const QString &image, const QString &hoverImage,
              const QString &currentImage, const QString &disableImage,
              const int &imgWidth , const int &imgHeight)
{
    if (!image.isEmpty()){
        //qDebug()<<image<<" load "<<_pixmap.load(image);

        QPixmap p;
        p.load(image);
        _pixmap = p;
    }

    if (!hoverImage.isEmpty()){
        QPixmap p;
        p.load(hoverImage);
        _hoverPixmap = p;
      //  _hoverPixmap.load(hoverImage);
    }
    if (!currentImage.isEmpty()){
        //_currentPixmap.load(currentImage);

        QPixmap p;
        p.load(currentImage);
        _currentPixmap= p;
    }
    if (!disableImage.isEmpty()){
        //_disablePixmap.load(disableImage);

        QPixmap p;
        p.load(disableImage);
        _disablePixmap= p;

    }
    _imgWidth = _pixmap.rect().width();

    if (imgWidth != -1 && imgHeight != -1){
        _imgWidth = imgWidth;
        if (!_pixmap.isNull())
            _pixmap = _pixmap.scaled(imgWidth, imgHeight);
        if (!_hoverPixmap.isNull())
            _hoverPixmap = _hoverPixmap.scaled(imgWidth, imgHeight);
        if (!_currentPixmap.isNull())
            _currentPixmap = _currentPixmap.scaled(imgWidth, imgHeight);
        if (!_disablePixmap.isNull())
            _disablePixmap = _disablePixmap.scaled(imgWidth, imgHeight);
    }
    update();
}

void GraphicsItemButton::setTextColorHover(const QColor &tColor)
{
    _textColor_hover = tColor;
}

void GraphicsItemButton::setTextColorSelected(const QColor &tColor)
{
    _textColor_selected = tColor;
}

void GraphicsItemButton::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if (event->mimeData()->hasText()) {
        event->setAccepted(true);
        _dragOver = true;
        update();
    }
    else {
        event->setAccepted(false);
    }
    QGraphicsItem::dragEnterEvent(event);
}

void GraphicsItemButton::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    Q_UNUSED(event);
    _dragOver = false;
    update();
    QGraphicsItem::dragLeaveEvent(event);
}

void GraphicsItemButton::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    _dragOver = false;
    if (_enable)
        emit drop(event->mimeData(), this);
    update();

    QGraphicsItem::dropEvent(event);
}

void GraphicsItemButton::setDragEnterImg(const QString &image)
{
    _dragEnterImage = image;
    _dragEnterImageImage.load(_dragEnterImage);
}

void GraphicsItemButton::setTextShowLen(const int &len)
{
    _textShowLen = len;
    if (_oriText.length() > _textShowLen){
        //setToolTip(_text);
        _text = _oriText.mid(0,_textShowLen - 1 - 2);
        _text += "...";
        update();
    }
//    else {
        //setToolTip("");
//    }
}
///////////////////////////////////////////////////////////////////////////////////
GraphicsItemRadioButton::GraphicsItemRadioButton(QGraphicsItem * parent)
    : QGraphicsItem(parent)
    , _hovered(false)
    , _checked(false)
{
    _icon.load(":/resources/images/radioBtn_bg.png");
    _chkIcon.load(":/resources/images/radioBtn_bg_select.png");
    _hoverIcon.load(":/resources/images/radioBtn_bg_hover.png");
}

QRectF GraphicsItemRadioButton::boundingRect() const
{
    return QRectF(0,0,18,18);
}

void GraphicsItemRadioButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
           QWidget *widget)
{
    if (!_checked)
    {
        if(!_hovered)
            painter->drawPixmap(QRect(0, 0, 18, 18), _icon);
        else
            painter->drawPixmap(QRect(0, 0, 18, 18), _hoverIcon);
    }
    else
            painter->drawPixmap(QRect(0, 0, 18, 18), _chkIcon);
}

void GraphicsItemRadioButton::setCheck(const bool &chk)
{
    _checked = chk;
    update();
}
void GraphicsItemRadioButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    _hovered = true;
    update();
    QGraphicsItem::hoverEnterEvent(event);
}
void  GraphicsItemRadioButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    _hovered = false;
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}

///////////////////////////////////////////
GraphicsTextItemButton::GraphicsTextItemButton(QGraphicsItem* parent):QGraphicsTextItem(parent),
_hoverCursor(Qt::PointingHandCursor)
, _type(NOTSET)
, _hoverType(NOTSET)
{    
    _width = 80; 
    _height = 25;
}
QRectF GraphicsTextItemButton::boundingRect() const
{
    return QRectF(0, 0, _width, _height);
}
void GraphicsTextItemButton::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    if(_hoverType == HTML)
        setHtml(_hoverText);
    else if(_hoverType == TEXT)
        setPlainText(_hoverText);
    else if(_hoverType == NOTSET)
    {
        if(_type == HTML)
            setHtml(_text);
        else if(_type == TEXT)
            setPlainText(_text);
    }

    setCursor(_hoverCursor);
    QGraphicsTextItem::hoverEnterEvent(event);
}
void GraphicsTextItemButton::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if(_type == HTML)
        setHtml(_text);
    else if(_type == TEXT)
        setPlainText(_text);
    QGraphicsTextItem::hoverLeaveEvent(event);
}
void GraphicsTextItemButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    emit clicked();
}

void GraphicsTextItemButton::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void GraphicsTextItemButton::setHover(const bool& isHover)
{
    if(isHover)
    {
         if(_hoverType == HTML)
             setHtml(_hoverText);
         else if(_hoverType == TEXT)
             setPlainText(_hoverText);
         else if(_hoverType == NOTSET)
         {
             if(_type == HTML)
                 setHtml(_text);
             else if(_type == TEXT)
                 setPlainText(_text);
         }
    }
    else
    {
        if(_type == HTML)
            setHtml(_text);
        else if(_type == TEXT)
            setPlainText(_text);
    }
}
void GraphicsTextItemButton::setButtonText(const QString& text)
{
    _text = text;
    _hoverText = text;
    _type = TEXT;
    GraphicsTextItemButton::setPlainText(text);
}
void GraphicsTextItemButton::setButtonHtml(const QString& text)
{
    _text = text;
    _hoverText = text;
    _type = HTML;
    GraphicsTextItemButton::setHtml(text);
}
void GraphicsTextItemButton::setHoverText(const QString& text)
{
    _hoverText = text;
    _hoverType = TEXT;
}
void GraphicsTextItemButton::setHoverHtml(const QString& text)
{
    _hoverText = text;
    _hoverType = HTML;
}

