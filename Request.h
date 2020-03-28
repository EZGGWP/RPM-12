#ifndef REQUEST_H
#define REQUEST_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QtNetwork/QtNetwork>

void getInfo(QString link) {
    QNetworkAccessManager manager;
    QNetworkRequest someRequest;
    someRequest.setUrl(link);
    //qDebug() << link;
    QNetworkReply *rep = manager.get(someRequest);
    QEventLoop event;
    QObject::connect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QObject::disconnect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    //qDebug() << rep->error();
    //qDebug() << rep->errorString();
    QJsonDocument data = QJsonDocument::fromJson(rep->readAll());
    //qDebug() << data;
    QJsonObject obj = data.object();
    qDebug() << obj.value("response");
}

#endif // REQUEST_H

