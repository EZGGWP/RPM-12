#include "mainwindow.h"

#include <QApplication>

///
/// @brief Это функция мэйн, в которой запускается приложение
/// \param argc
/// \param argv
/// \return Возвращает результат выполнения приложения
///
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
