#ifndef FADERITEM_H
#define FADERITEM_H
#include <QObject>
#include <QGraphicsItem>
#include <QTimeLine>
#include <QRect>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsOpacityEffect>
#include "comcontrols_global.h"

class QGraphicsSceneHoverEvent;
class LCONTROLSSHARED_EXPORT FaderItem : public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    FaderItem(QGraphicsItem *parentItem=0);
    void setTranslate(qreal,qreal);
    void setFixed(const bool &fix);
    bool isFixed() { return _fixed; }

public slots:
    void fade_on_fade_in(int counter);
    void receiveStatus(int,int,QString);

    void timeFinished();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );

private:
    QTimeLine *timeline;
    int changenumber;
//    QGraphicsOpacityEffect *Opacity;
    qreal view_width;
    qreal view_height;
    qreal picture_heigth;
    int status;
    int tip_change_rate;
    QString _content;

    QPixmap _tipsBox_error_left;
    QPixmap _tipsBox_error_center;
    QPixmap _tipsBox_error_right;
    QPixmap _tipsBox_note_left;
    QPixmap _tipsBox_note_center;
    QPixmap _tipsBox_note_right;
    QPixmap _tipsBox_succeed_left;
    QPixmap _tipsBox_succeed_center;
    QPixmap _tipsBox_succeed_right;

    bool _running;
    bool _fixed;
};

#include <QWidget>
class LCONTROLSSHARED_EXPORT FaderWidget : public QWidget
{
    Q_OBJECT
public:
    FaderWidget(QWidget *parent=0);
    void setTranslate(qreal,qreal);
    void setFixed(const bool &fix);
    bool isFixed() { return _fixed; }

public slots:
    void fade_on_fade_in(int counter);
    void receiveStatus(int,int,QString);

    void timeFinished();

protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    QTimeLine *timeline;
    int changenumber;
//    QGraphicsOpacityEffect *Opacity;
    qreal view_width;
    qreal view_height;
    qreal picture_heigth;
    int status;
    int tip_change_rate;
    QString _content;

    QPixmap _tipsBox_error_left;
    QPixmap _tipsBox_error_center;
    QPixmap _tipsBox_error_right;
    QPixmap _tipsBox_note_left;
    QPixmap _tipsBox_note_center;
    QPixmap _tipsBox_note_right;
    QPixmap _tipsBox_succeed_left;
    QPixmap _tipsBox_succeed_center;
    QPixmap _tipsBox_succeed_right;

    bool _running;
    bool _fixed;
};

#endif // FADERITEM_H
