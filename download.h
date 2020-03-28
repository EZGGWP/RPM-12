#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QDebug>
#include <QtNetwork/QtNetwork>

class Download : public QObject {
    Q_OBJECT
public:
    ///
    /// @brief Это конструктор класса Download
    /// @param parent Получает ссылку на объект-родитель
    ///
    explicit Download(QObject *parent = nullptr);
public slots:
    ///
    /// @brief Это слот, загружающий картинку профиля
    /// @param link Получает ссылку на картинку профиля в photo_max_orig
    ///
    void downloadStart(QString link);
signals:
    ///
    /// @brief Это сигнал, который эмитится по окончанию загрузки картинки профиля
    /// @param rep Аргументом является ответ, содержащий картинку
    ///
    void downloadEnd(QNetworkReply *rep);
};

#endif // DOWNLOAD_H
