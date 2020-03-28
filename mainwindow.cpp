#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

///
/// @brief Это конструктор главного окна, тут мы подключаем сигналы и настраиваем UI
/// @param parent принимает в качестве аргумента ссылку на родителя
///
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QString plchldr = "Введите ссылку на профиль";
    ui->lineEdit->setPlaceholderText(plchldr);
    ui->label->setStyleSheet("border-width: 10px; border-style: ridge; border-color: blue;");
    QValidator *val = new QRegExpValidator(QRegExp("([A-z]*[0-9]*)\\w{1,32}"), 0);
    ui->lineEdit->setValidator(val);
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this->actionObject1, SLOT(getUrl(QString)));
    connect(ui->pushButton, &QPushButton::clicked, this->actionObject1, &Gett::getInfo);
    connect(actionObject1, &Gett::gotData, actionObject2, &Download::downloadStart);
    connect(actionObject2, &Download::downloadEnd, this, &MainWindow::setPic);
    connect(actionObject1, &Gett::setData, this, &MainWindow::setTexts);
    connect(actionObject1, &Gett::setFriends, this, &MainWindow::setFriendsText);
}

///
/// @brief Это деструктор главного окна
///
MainWindow::~MainWindow() {
    delete ui;
}

///
/// @brief Это слот установки картинки
/// \param rep Получает ответ, содеращий картинку
///
void MainWindow::setPic(QNetworkReply *rep) {
    QPixmap map;
    map.loadFromData(rep->readAll());
    ui->label->setScaledContents(true);
    ui->label->setPixmap(map);
};

///
/// @brief Это слот для установки текстовых данных
/// @param arr Получает массив с данными для установки
///
void MainWindow::setTexts(QJsonArray arr) {
    ui->lineEdit_2->setText(arr[0].toObject().value("first_name").toString());
    ui->lineEdit_3->setText(arr[0].toObject().value("last_name").toString());
    if (arr[0].toObject().value("bdate").toString() == "") {
        ui->lineEdit_8->setText("Профиль закрыт.");
    } else ui->lineEdit_8->setText(arr[0].toObject().value("bdate").toString());

    if (arr[0].toObject().value("nickname").toString() == "") {
        ui->lineEdit_6->setText("Нет никнейма");
    } else ui->lineEdit_6->setText(arr[0].toObject().value("nickname").toString());
};

///
/// @brief Это слот для установки списка друзей
/// @param friends Получает строку с ID друзей
///
void MainWindow::setFriendsText(QString friends) {
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setText(friends);
}

