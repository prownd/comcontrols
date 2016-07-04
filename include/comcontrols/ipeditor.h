#ifndef IPEDITOR_H
#define IPEDITOR_H

#include <QLineEdit>
#include <QGraphicsItem>
#include "comcontrols_global.h"

class QGraphicsProxyWidget;
class LCONTROLSSHARED_EXPORT EditorSubItem : public QLineEdit
{
    friend class IPEditor;
public:
    EditorSubItem(QGraphicsItem *parent = 0);

    virtual void paintEvent ( QPaintEvent * event);

    QGraphicsProxyWidget* proxy() { return _proxy; }


    void setEnableEdit(const bool &enable) { _enabled = enable;
                                             this->setEnabled(enable);}

protected:
    void	focusInEvent ( QFocusEvent * event );
    void	focusOutEvent ( QFocusEvent * event );

private:

    bool _focusIn;
    bool _enabled;

    QPixmap _normal;
    QPixmap _disable;
    QPixmap _focus;
    QGraphicsProxyWidget* _proxy;
};


class LCONTROLSSHARED_EXPORT IPEditor : public QGraphicsItem
{
public:
    IPEditor(QGraphicsItem *parent = 0);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    //xxx.xxx.xxx.xxx
    QString getVal();
    //xxx.xxx.xxx.xxx
    void setVal(const QString &val);
    void setEnableEdit(const bool &enable);
    void setSubValidator(int index, QValidator* validator);

private:

    QList<EditorSubItem*> _ip;
};

#endif // IPEDITOR_H
