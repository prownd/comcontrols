#ifndef CURVEWIDGET_H
#define CURVEWIDGET_H

#include <QWidget>
#include <QVariant>
#include "comcontrols_global.h"

class LCONTROLSSHARED_EXPORT CurveWidget : public QWidget
{
    Q_OBJECT
public:

    struct curve {
        curve(): _lineWidth(2){}
        QString  _name;
        QColor   _color;
        int      _lineWidth;
        QMap<qreal, qreal> _values;
    };

    explicit CurveWidget(QWidget *parent = 0);

    void setXSum(const int &val);
    void setYSum(const int &val);

    void setXMax(const qreal &val);
    void setXMin(const qreal &val);

    void setYMax(const qreal &val);
    void setYMin(const qreal &val);

    void setXUnit(const QString &unit);
    void setYUnit(const QString &unit);

    void setYTitle(const QString &til) { _yTitle = til; }
    void setBottomHeight(const int &hei) { _bottomHeight = hei; }
    void setTopHeight(const int &hei) { _topHeight = hei; }
    void setLeftWidth(const int &wid) { _leftWidth = wid; }
    void setTopLine(const bool &val) { _topLine = val; }

    void setAxisColor(const QColor &col) { _axisColor = col; }
    void setGridColor(const QColor &col) { _gridColor = col; }

    void addCurve(const curve &cur);
    void addValue(const int &curveIndex, const qreal &x, const qreal &y);
    void removeAll();

    void setXValShow(const bool &sh) { _xValShow = sh; }
    void setYValShow(const bool &sh) { _yValShow = sh; }

protected:

    void paintEvent ( QPaintEvent * event );

signals:
    
public slots:

private:

    QPointF convertToPoint(const qreal &xVal, const qreal &yVal,
                          const int &xZero, const int &yZero,
                          const int &xSpacing ,const int &ySpacing,
                          const qreal &xStepVal, const qreal &yStepVal);

private:

    int _xSum;//∫·÷·øÃ∂» ˝¡ø
    qreal _xMin;
    qreal _xMax;

    int _ySum;
    qreal _yMin;
    qreal _yMax;


    QString _xUnit;
    QString _yUnit;

    QList<curve> _curves;

    QFontMetrics _metrics;

    int _bottomHeight;
    int _topHeight;
    int _leftWidth;

    QString _yTitle;

    QColor _axisColor;
    QColor _gridColor;

    bool _topLine;

    bool _xValShow;
    bool _yValShow;
};

#endif // CURVEWIDGET_H
