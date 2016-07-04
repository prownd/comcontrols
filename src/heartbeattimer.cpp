#include "heartbeattimer.h"
#define NODEEVENT   QEvent::User+7
HeartBeat::HeartBeat(QObject *parent, const int& interval)
        : QObject(parent),intval(interval)
{
    checkTimer = new QTimer(this);
    checkTimer->setInterval(intval);
    last = QDateTime::currentDateTime();
    connect(checkTimer, SIGNAL(timeout()), \
            this, SLOT(check()));
}

HeartBeat::~HeartBeat()
{ 
    delete checkTimer; 
}
void HeartBeat::beat()
{
    if (!checkTimer->isActive())
        checkTimer->start();
    last = QDateTime::currentDateTime();
}
void HeartBeat::setInerval(const int &sec) {
    intval = sec;
}
void HeartBeat::check()
{
    QDateTime cur = QDateTime::currentDateTime();
    if (last.secsTo(cur) >= (int)intval/1000) {
    //if (last.secsTo(QDateTime::currentDateTime()) >= (int)intval/1000) {
        checkTimer->stop(); 
        emit dead();
    }
}

/////////////////////////////////////////////////////////
void HeartbeatTimer::customEvent(QEvent *event)
{
    if (event->type() == QEvent::Type(NODEEVENT)) {

        HeartbeatTimerEvent* ne = static_cast<HeartbeatTimerEvent*>(event);
        if (ne->operation() == HeartbeatTimerEvent::START)
            this->start(); 
        else if (ne->operation() == HeartbeatTimerEvent::STOP)
            this->stop(); 
    }
}

void HeartbeatTimer::onlive()
{
    QString cmd = QString("LIVE");
}


