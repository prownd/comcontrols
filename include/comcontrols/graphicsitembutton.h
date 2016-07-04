#ifndef GRAPHICSITEMBUTTON_H
#define GRAPHICSITEMBUTTON_H

#include <QGraphicsItem>
#include <QObject>
#include <QFont>
#include <QCursor>
#include "comcontrols_global.h"

class QImage;
class QMimeData;
class QGraphicsTextItem;
class LCONTROLSSHARED_EXPORT GraphicsItemButton : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    enum style {
        current_stay, normal
    };

    enum text_pos {
        left, right, top, bottom, center
    };

    enum icon_pos {
        icon_center, icon_top
    };

    GraphicsItemButton(const QString &image, const QString &hoverImage,
                       const QString &currentImage, const QString &disableImage,
                       const style &stl = normal,
                       QGraphicsItem * parent = 0,
                       const int &imgWidth = -1, const int &imgHeight = -1, const text_pos &tp = right,
                       const icon_pos &icp = icon_center);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setImage(const QString &image, const QString &hoverImage,
                  const QString &currentImage, const QString &disableImage,
                  const int &imgWidth = -1, const int &imgHeight = -1);

    void setDragEnterImg(const QString &image);

    void setCurrent(const bool &cur);

    void setHover(const bool &hover);

    void setEnable(const bool &en);

    void setText(const QString &text);
    QString getText() {return  _text;}

    void setDefaultTextColor(const QColor &tColor);
    void setTextColorHover(const QColor &tColor);
    void setTextColorSelected(const QColor &tColor);
    void setFont(const QFont &font);

    void setSize(const int width, const int height);

    void setTextPos(const text_pos &pos);
    void setHoverCursor(const QCursor& cursor){_hoverCursor = cursor;}

    void setDataP(void* getData);
    void* getData();

    void addMenu(const QString &menu);

    void setUnderLine(const bool &underLine) { _underLine = underLine; }
    void setHoverUnderLine(const bool &underLine){_hoverUnderLine = underLine;}
    bool isHovered() {return _enable&&_hovered;}
    bool isEnable() { return _enable; }

    //the min len of text showed, if more than len,show it by "xxx...",and show text by tooltip
    void setTextShowLen(const int &len);
    void setHoverToolTipText(const QString& text){_hoverToolTipText = text;}
signals:

    void clicked();
    void clicked(GraphicsItemButton* btn);

    void clickMenu(const QString &menu);
    void clickMenu(const int &menu);

    void drop(const QMimeData* mimeData, GraphicsItemButton* btn);

protected:

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
    void dropEvent(QGraphicsSceneDragDropEvent *event);

    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent ( QGraphicsSceneMouseEvent * event );
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    void hoverMoveEvent ( QGraphicsSceneHoverEvent * event );
private:

    QString _image;
    QString _hoverImage;
    QString _currentImage;
    QString _dragEnterImage;

    QPixmap _pixmap;
    QPixmap _hoverPixmap;
    QPixmap _currentPixmap;
    QPixmap _disablePixmap;

    QPixmap _viewSwitch_dropDown_hover;
    QPixmap _viewSwitch_dropDown;
    QPixmap _dragEnterImageImage;

    style _style;

    QFont _font;
    text_pos _textPos;
    QCursor  _hoverCursor;

    void* _data;

protected:

    QFontMetrics* _metrics;
    QColor _textColor;
    QColor _textColor_hover;
    QColor _textColor_selected;
    bool _current;
    bool _enable;
    QString _text;
    QString _oriText;
    QString _hoverToolTipText;
    bool _hovered;
    int _width;
    int _height;

    QList<QString> _menus;
    QRect _menuRect;
    bool _menuHover;

    bool _dragOver;

    bool _underLine;
    bool _hoverUnderLine;

    int _imgWidth;

    icon_pos _iconPos;
    int _textShowLen;
};

class LCONTROLSSHARED_EXPORT GraphicsItemRadioButton : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:

    GraphicsItemRadioButton(QGraphicsItem * parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void setCheck(const bool &chk);
    bool checked() {return _checked; }
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
private:

    QPixmap _icon;
    QPixmap _chkIcon;
    QPixmap _hoverIcon;
    bool _checked;
    bool _hovered;
};
class LCONTROLSSHARED_EXPORT GraphicsTextItemButton : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum text_type {TEXT = 0, HTML = 2, NOTSET};
    GraphicsTextItemButton(QGraphicsItem * parent = 0);

    QRectF boundingRect() const;
   // void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
   //            QWidget *widget);
    void setHoverCursor(const QCursor& cursor){_hoverCursor = cursor;}
    void setButtonText(const QString& text);
    void setButtonHtml(const QString& text);
    void setHoverText(const QString& text);
    void setHoverHtml(const QString& text);
    void setButtonFont(const QFont & font);
    void setHover(const bool& isHover);
signals:
    void clicked();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
private:
    int _height;
    int _width;
    QCursor  _hoverCursor;
    QString  _text;
    QString  _hoverText;
    text_type _type;
    text_type _hoverType;
};

#endif // GRAPHICSITEMBUTTON_H
