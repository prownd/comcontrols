#ifndef PAGENUMBERCONTROL_H
#define PAGENUMBERCONTROL_H

#include <QWidget>
#include "comcontrols_global.h"
#include "custombtn.h"

#ifndef ABSTRACT
  #define ABSTRACT =0
#endif

//usage:IPageNumberControl *app = new PageNumberControl(this);
class LCONTROLSSHARED_EXPORT IPageNumberControl : public QWidget
{
    Q_OBJECT
public:
    virtual ~IPageNumberControl(){};
protected:
    IPageNumberControl(QWidget *parent = 0):QWidget(parent){};

public:
    virtual void setCurrentPage(int currentPageNumber) ABSTRACT;
    virtual void setTotalPage(int totalPageNumber) ABSTRACT;
    virtual void setCurrentAndTotalPage(int currentPageNumber, int totalPageNumber) ABSTRACT;
    virtual void setBackgroundColor(const QColor & color) ABSTRACT;

signals:
    void currentPageChanged(int);
};
class LCONTROLSSHARED_EXPORT PageNumberControl : public IPageNumberControl
{
    Q_OBJECT
public:
    explicit PageNumberControl(QWidget *parent = 0);
    ~PageNumberControl();
public:
    void setCurrentPage(int currentPageNumber);
    void setTotalPage(int totalPageNumber);
    void setCurrentAndTotalPage(int currentPageNumber, int totalPageNumber);
    void setBackgroundColor(const QColor & color);
    void setCluster(bool);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void updatePageNumber();

private slots:
    void slotForwardPage();
    void slotBackwardPage();

private:
    bool _cluster;
    QLabel *currentPageLabel;
    QLabel *middleLabel;
    QLabel *totalPageLabel;

    CustomBtn *forwardBtn;
    CustomBtn *backwardBtn;

    QPoint dragPosition;

    int _currentPageNumber;
    int _totalPageNumber;
    QColor backgroundColor;
};

#endif // PAGENUMBERCONTROL_H
