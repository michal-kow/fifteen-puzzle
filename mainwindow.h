#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <QStackedWidget>
#include <homescreen.h>
#include <puzzlemodel.h>
#include <puzzlescreen.h>
#include <screenmanager.h>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    ScreenManager *screenManager;
    PlayerManager *playerManager;
};
#endif // MAINWINDOW_H
