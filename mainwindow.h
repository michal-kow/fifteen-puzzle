#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleClick(QPushButton * tile) {
        QString tilePosition = QString(tile->objectName().at(4)) + QString(tile->objectName().at(5));
        cout << "Position: " << tilePosition.toStdString() << endl;
        cout << "Value: " << tile->text().toStdString() << endl;
    };

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
