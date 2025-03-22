#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <QStackedWidget>
#include <landingpage.h>
#include <boardmodel.h>
#include <boardview.h>

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
    LandingPage *landingPage;
    BoardModel *boardModel;
    BoardView *boardView;

public slots:
    void startGame(int boardSize);
    void returnToLandingPage();
};
#endif // MAINWINDOW_H
