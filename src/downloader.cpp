#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QVariant>
#include <QUrl>
#include <QDebug>
#include <QByteArray>
#include <QString>
#include <QFile>
#include <QFileInfo>

#include "downloader.h"

Downloader::Downloader(QObject *parent)
    : QObject(parent), _reply(NULL)
{
    _nam = new QNetworkAccessManager;
    connect(_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
}

Downloader::~Downloader()
{
}

void Downloader::download(QString source, QString dest)
{
    if (_reply) {
        qDebug() << "this should not happen";
        return;
    }

    _dest = dest;
    _url.clear();
    _url.setUrl(source);
    _reply = _nam->get(QNetworkRequest(_url));
    connect(_reply, SIGNAL(downloadProgress(qint64, qint64)), SLOT(onProgress(qint64, qint64)));
}

void Downloader::onProgress(qint64 recieve, qint64 total)
{
    emit progress(recieve, total);
}

void Downloader::close()
{
    if (_reply)
        _reply->abort();
    _reply = NULL;
}

void Downloader::onFinished(QNetworkReply*)
{
    QVariant statusCodeV = _reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    QVariant redirectionTargetUrl = _reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (_reply->error() == QNetworkReply::NoError) {
        _buffer = _reply->readAll();
        QFile file(_dest);
        if (!file.open(QIODevice::WriteOnly))
            qDebug() << "open file failed when writing";
        file.write(_buffer);
        file.close();
        emit done();
    }
    else {
        emit loadError("ÏÂÔØÊ§°Ü£¬Çë¼ì²éÍøÂçµØÖ·¼°ÍøÂçÁ¬½Ó");
    }
    _reply = NULL;
}
