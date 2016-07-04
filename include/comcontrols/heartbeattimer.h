#include <QEvent>
#include <QObject> 
#include <QDateTime>
#include <QTimer>
#include "comcontrols_global.h"
class LCONTROLSSHARED_EXPORT HeartBeat : public QObject
{
    Q_OBJECT
public:
    HeartBeat(QObject *parent, const int& interval = 40000);

    ~HeartBeat();
    void beat();
    void setInerval(const int &sec);
signals:
    void dead();
private slots:
    void check();
private:
    QDateTime  last;
    QTimer*    checkTimer;
    int        intval;
};

class LCONTROLSSHARED_EXPORT HeartbeatTimerEvent :public QEvent
{
public:

    HeartbeatTimerEvent ()
        : QEvent(Type(QEvent::User+7)) {}

    enum Op { START, STOP};

    void    setOperation(enum Op op) { _op = op; }
    Op      operation() { return _op; }

private:

    Op _op;
};

class LCONTROLSSHARED_EXPORT HeartbeatTimer :public QTimer
{
    Q_OBJECT
public:
    HeartbeatTimer(){
//        connect(this,SIGNAL(timeout()),this, SLOT(onlive()));
    }

private slots:

    void onlive();

protected:
    void  customEvent(QEvent *event);
};


