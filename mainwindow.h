#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include "gett.h"
#include "download.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    ///
    /// @brief Это конструктор главного окна, тут мы подключаем сигналы и настраиваем UI
    /// @param parent принимает в качестве аргумента ссылку на родителя
    ///
    MainWindow(QWidget *parent = nullptr);
    ///
    /// @brief Это деструктор главного окна
    ///
    ~MainWindow();
    Gett *actionObject1 = new Gett;
    Download *actionObject2 = new Download;
private:
    Ui::MainWindow *ui;
public slots:
    ///
    /// @brief Это слот установки картинки
    /// \param rep Получает ответ, содеращий картинку
    ///
    void setPic(QNetworkReply *rep);
    ///
    /// @brief Это слот для установки текстовых данных
    /// @param arr Получает массив с данными для установки
    ///
    void setTexts(QJsonArray arr);
    ///
    /// @brief Это слот для установки списка друзей
    /// @param friends Получает строку с ID друзей
    ///
    void setFriendsText(QString friends);
};
#endif // MAINWINDOW_H
