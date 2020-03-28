#ifndef GETT_H
#define GETT_H
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonDocument>
#include <QtNetwork/QtNetwork>
#include <QSslSocket>

class Gett : public QObject {
    Q_OBJECT
public:
    ///
    /// @brief Это конструктор класса Gett
    /// @param parent Получает ссылку на объект-родитель
    ///
    explicit Gett(QObject *parent = nullptr);
    QUrl pageId;
    QString fName;
public slots:
    ///
    /// \brief Это слот для получения полной ссылки для запросов по короткому id VK
    /// \param url Получает короткий id пользователя
    ///
    void getUrl(QString url);
    ///
    /// @brief Это слот, отправляющий запрос на получение базовой информации о пользователе
    ///
    void getInfo();
    ///
    /// @brief Это слот для получения данных о друзьях
    /// @param id получает не сокращённый, а цифровой id
    ///
    void friendList(QString id);
signals:
    ///
    /// @brief Этот сигал эмитится, когда базовая информация получена
    /// @param arr Аргументом является массив, содержащий базовую информацию
    ///
    void setData(QJsonArray arr);
    ///
    /// @brief Этот сигнал эмитится, когда получается взять цифровой id для получения друзей
    /// @param link Аргументом является ссылка для получения друзей
    ///
    void gotData(QString link);
    ///
    /// @brief Этот сигнал эмитится, когда получен список друзей
    /// @param id Аргументом является строка, содержащая id друзей
    ///
    void setFriends(QString friends);
};

#endif // GETT_H
