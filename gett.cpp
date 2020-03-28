#include "gett.h"
#include <QMessageBox>
#include <QValidator>

///
/// @brief Это конструктор класса Gett
/// @param parent Получает ссылку на объект-родитель
///
Gett::Gett(QObject *parent) : QObject(parent) {

}

///
/// @brief Это слот, отправляющий запрос на получение базовой информации о пользователе
///
void Gett::getInfo() {
    QNetworkAccessManager manager;
    QNetworkRequest someRequest;
    someRequest.setUrl(pageId);
    QNetworkReply *rep = manager.get(someRequest);
    QEventLoop event;
    QObject::connect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QObject::disconnect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    QJsonDocument data = QJsonDocument::fromJson(rep->readAll());
    qDebug() << data.object().value("response");
    if (data.object().value("response") == QJsonValue::Undefined) {
        QMessageBox msg;
        msg.setText("Профиль не найден.");
        msg.exec();
    } else {
        QJsonArray arr = data.object()["response"].toArray();
        QString link = arr[0].toObject().value("photo_max_orig").toString();
        QString id = QString::number(arr[0].toObject().value("id").toInt());
        Gett::friendList(id);
        emit gotData(link);
        emit setData(arr);
    }
}

///
/// @brief Это слот для получения данных о друзьях
/// @param id получает не сокращённый, а цифровой id
///
void Gett::friendList(QString id) {
    QNetworkAccessManager manager;
    QNetworkRequest someRequest;
    QString address = "https://api.vk.com/method/friends.get?user_id=" + id + "&count=10&access_token=9ad7ae8e9ad7ae8e9ad7ae8e579ab8500d99ad79ad7ae8ec48d995ab3251bc13926e3f0&v=5.103";
    someRequest.setUrl(address);
    QNetworkReply *rep = manager.get(someRequest);
    QEventLoop event;
    QObject::connect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    event.exec();
    QObject::disconnect(rep, SIGNAL(finished()), &event, SLOT(quit()));
    QJsonDocument data = QJsonDocument::fromJson(rep->readAll());
    QString friends = "";
    if (data.object().value("response") == QJsonValue::Undefined) {
        friends = "Профиль закрыт.";
    } else {
        QJsonArray arr = data.object()["response"].toObject()["items"].toArray();
        for (int i = 0; i < arr.size() - 1; i++) {
            friends = friends + QString::number(arr[i].toInt()) + ", ";
        }
        friends = friends + QString::number(arr[arr.size()-1].toInt()) + ".";
    }
    emit setFriends(friends);
}

///
/// \brief Это слот для получения полной ссылки для запросов по короткому id VK
/// \param url Получает короткий id пользователя
///
void Gett::getUrl(QString url) {
    url = "https://api.vk.com/method/users.get?user_ids=" + url + "&fields=photo_max_orig,bdate&access_token=9ad7ae8e9ad7ae8e9ad7ae8e579ab8500d99ad79ad7ae8ec48d995ab3251bc13926e3f0&v=5.103";
    this->pageId = QUrl(url);
};
