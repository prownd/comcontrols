#ifndef DOWNLOADER_H
#define DOWNLOADER_H
#include <QObject>
#include <QUrl>
#include <QFile>
#include "comcontrols_global.h"

class QNetworkAccessManager;
class QNetworkReply;
class QByteArray;
class QString;

class LCONTROLSSHARED_EXPORT Downloader : public QObject
{
    Q_OBJECT
public:
    Downloader(QObject * parent = NULL);
    ~Downloader();
    void download(QString url, QString dest);
    void save(QString filename);
    QByteArray& buffer()
    {
        return _buffer;
    }
    void close();
public slots:
    void onFinished(QNetworkReply *);
    void onProgress(qint64, qint64);
signals:
    void done();
    void progress(qint64, qint64);
    void loadError(QString error);
private:
    QNetworkAccessManager *_nam;
    QNetworkReply *_reply;
    QUrl _url;
    QByteArray _buffer;
    QString _dest;
};

#endif
