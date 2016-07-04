#include "curvewidget.h"

#include <QPainter>
#include <QPainterPath>

CurveWidget::CurveWidget(QWidget *parent) :
    QWidget(parent)
  , _xSum(12)
  , _xMin(0)
  , _xMax(60)
  , _ySum(2)
  , _yMin(0)
  , _yMax(100)
  , _metrics(this->font())
  , _bottomHeight(10)
  , _topHeight(15)
  , _leftWidth(10)
  , _axisColor(18,136,245)
  , _gridColor("#dee0ea")
  , _topLine(false)
  , _xValShow(true)
  , _yValShow(true)
{
    this->setStyleSheet("background-color:rgba(255,255,255,0)");
//    _yUnit = "%";

//    for (qreal i = 0;i < 240;i++)
//        _values.insert(i / 20, rand() % 20 + 20);
}

void CurveWidget::paintEvent ( QPaintEvent * event )
{
    QPainter painter(this);

    int xZero = 0;
    QString str;
    for (int i = 0;i < _ySum;i++) {
        str = QString("%1%2").arg(_yMin + (i + 1) * (_yMax - _yMin) / _ySum).arg(_yUnit);

        if ((_metrics.width(str) + _leftWidth) > xZero) {
            xZero = _metrics.width(str) + _leftWidth;
        }
    }
    int yZero = this->height() - _metrics.height() - _bottomHeight;
 //   int yTop = 65;
    int xMax = width() - 10 - _metrics.width(_xUnit) - 5;
    int xWidth = xMax - xZero;
    int yHeight = yZero - _topHeight;
    int arrowDis = 10;

    //draw grid
    int xSpacing = xWidth / _xSum;
    int ySpacing = yHeight / _ySum;

    qreal xStepVal = (_xMax - _xMin) / _xSum;
    qreal yStepVal = (_yMax - _yMin) / _ySum;

    painter.setPen(QPen(_gridColor));

//    yZero -=2;

    //draw text
//
    painter.setPen(QPen(_axisColor));
    for (int i = 0;i < _ySum;i++) {
        if (i < (_ySum - 1) && !_yValShow)
            continue;
        str = QString("%1%2").arg(_yMin + (i + 1) * (_yMax - _yMin) / _ySum).arg(_yUnit);
        painter.drawText(QRect(xZero - _metrics.width(str) - 5, _topHeight + (_ySum - i - 1) * ySpacing, _metrics.width(str),_metrics.height()) ,str);
    }
    for (int i = 0;i <= _xSum;i++) {
        if (i > 0 && i < _xSum && !_xValShow)
            continue;
   //     str = QString("%1%2").arg(_xMin + i * (_xMax - _xMin)/_xSum).arg(_xUnit);
        str = QString("%1").arg(_xMin + i * (_xMax - _xMin)/_xSum);
        painter.drawText(QRect(xZero + i * xSpacing - _metrics.width(str) / 2, yZero + 5, _metrics.width(str) , _metrics.height()), str);
    }
    //draw x unit
    painter.drawText(QRect(xMax + 5, yZero + 5,_metrics.width(_xUnit), 20), _xUnit);

    //draw line
    painter.setPen(QPen(QColor(_gridColor)));
    for (int i = 0;i < _xSum;i++)
        painter.drawLine(xZero + (i + 1) * xSpacing, yZero, xZero + (i + 1) * xSpacing, _topHeight);

    int vSum = (_ySum - 1);
    if (_topLine)
        vSum++;

    for (int i = 0;i < vSum;i++)
        painter.drawLine(xZero, yZero - (i + 1) * ySpacing, xMax, yZero - (i + 1) * ySpacing);

    //draw line
    if (_curves.size() > 0) {
        for (int i = 0;i < _curves.size();i++) {

            QMap<qreal, qreal> values = _curves.at(i)._values;
            painter.setPen(QPen(QColor(_curves.at(i)._color), _curves.at(i)._lineWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

            QPointF poPre = convertToPoint(values.begin().key(), values.begin().value(), xZero, yZero, xSpacing, ySpacing, xStepVal, yStepVal);
            painter.drawPoint(poPre);

            for (QMap<qreal, qreal>::iterator iter = values.begin() + 1;iter != values.end();iter++) {
                QPointF poCur = convertToPoint(iter.key(), iter.value(), xZero, yZero, xSpacing, ySpacing, xStepVal, yStepVal);

                painter.drawLine(poPre, poCur);
                poPre = poCur;
            }
        }
    }
    yZero +=2;
    //draw x\y
//    painter.setPen(QPen(QColor(18,136,245), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setPen(QPen(_axisColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    painter.drawLine(xZero - 10, yZero, xMax + arrowDis, yZero);
    painter.drawLine(xZero, yZero + 5, xZero, _topHeight - arrowDis);

    QPointF points[3] = {QPointF(xZero, _topHeight - arrowDis), QPointF(xZero - 2.5, _topHeight + 5 - arrowDis), QPointF(xZero + 2.5, _topHeight + 5 - arrowDis)};
    painter.drawPolygon(points, 3);


    QPainterPath path1;
    path1.moveTo(points[0]);
    path1.lineTo(points[1]);
    path1.lineTo(points[2]);
    path1.lineTo(points[0]);
    painter.fillPath(path1, QBrush(_axisColor));

    //draw y title
    painter.drawText(QRect(points[2].x() + 3, _topHeight - arrowDis - 2, _metrics.width(_yTitle) + 1, _metrics.height()), _yTitle);


    QPointF points2[3] = {QPointF(xMax + arrowDis, yZero), QPointF(xMax - 5 + arrowDis, yZero + 2.5), QPointF(xMax - 5 + arrowDis, yZero - 2.5)};
    painter.drawPolygon(points2, 3);

    QPainterPath path2;
    path2.moveTo(points2[0]);
    path2.lineTo(points2[1]);
    path2.lineTo(points2[2]);
    path2.lineTo(points2[0]);
    painter.fillPath(path2, QBrush(_axisColor));

//    painter.fillRect(this->rect(), Qt::black);
}

QPointF CurveWidget::convertToPoint(const qreal &xVal, const qreal &yVal,
                      const int &xZero, const int &yZero,
                      const int &xSpacing ,const int &ySpacing,
                      const qreal &xStepVal, const qreal &yStepVal)
{
    return QPointF(xZero + xVal / xStepVal * xSpacing, yZero - yVal / yStepVal * ySpacing);
}

void CurveWidget::setXSum(const int &val)
{
    _xSum = val;
}

void CurveWidget::setYSum(const int &val)
{
    _ySum = val;
}

void CurveWidget::setXMax(const qreal &val)
{
    _xMax = val;
}

void CurveWidget::setXMin(const qreal &val)
{
    _xMin = val;
}

void CurveWidget::setYMax(const qreal &val)
{
    _yMax = val;
}

void CurveWidget::setYMin(const qreal &val)
{
    _yMin = val;
}

void CurveWidget::setXUnit(const QString &unit)
{
    _xUnit = unit;
}

void CurveWidget::setYUnit(const QString &unit)
{
    _yUnit = unit;
}

void CurveWidget::addCurve(const curve &cur)
{
    _curves.append(cur);
}

void CurveWidget::addValue(const int &curveIndex, const qreal &x, const qreal &y)
{
    if (curveIndex < 0)
        return;

    QList<curve>::iterator iter = NULL;
    qreal yV = y > _yMax ? _yMax : y;

    if (curveIndex >= _curves.size()) {
        curve cur;
        _curves.append(cur);
        iter = _curves.end() - 1;
    }
    else {
        iter = _curves.begin() + curveIndex;
    }

    iter->_values.insert(x, yV);
}

void CurveWidget::removeAll()
{
    _curves.clear();
}
