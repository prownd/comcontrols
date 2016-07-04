#ifndef GRAPHICSTEXTITEM_H
#define GRAPHICSTEXTITEM_H

#include <QLineEdit>

#include "comcontrols_global.h"

class QGraphicsItem;
class QGraphicsProxyWidget;
class LCONTROLSSHARED_EXPORT GraphicsTextItem : public QLineEdit
{
    Q_OBJECT
public:
    explicit GraphicsTextItem(QGraphicsItem *parent = 0);

    void setBackGroundColor(const QColor &col) { _backGroundColor = col; }

    void setError(const bool &bError) { _error = bError; }

    QGraphicsProxyWidget* proxy() { return _proxy; }
signals:
    
    void focusOut(GraphicsTextItem* item);
    void focusIn(GraphicsTextItem* item);

public slots:
    
protected:

    void focusInEvent ( QFocusEvent * event );
    void focusOutEvent ( QFocusEvent * event );
    void paintEvent ( QPaintEvent * );

private:

    QGraphicsProxyWidget* _proxy;
    bool _error;
    QColor _backGroundColor;
};

#endif // GRAPHICSTEXTITEM_H
