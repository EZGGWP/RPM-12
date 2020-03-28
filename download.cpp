#include "download.h"

///
/// @brief Это конструктор класса Download
/// @param parent Получает ссылку на объект-родитель
///
Download::Download(QObject *parent) : QObject(parent) {

}

///
/// @brief Это слот, загружающий картинку профиля
/// @param link Получает ссылку на картинку профиля в photo_max_orig
///
void Download::downloadStart(QString link) {
    QNetworkAccessManager mngr;
    QNetworkRequest req;
    req.setUrl(QUrl(link));
    QNetworkReply *rep = mngr.get(req);
    QEventLoop event;
    QObject::connect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QObject::disconnect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    emit downloadEnd(rep);
}
