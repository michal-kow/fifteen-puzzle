#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include "playermanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);
    // playerManager = new PlayerManager(this);
    screenManager = new ScreenManager(stackedWidget, this);

    setCentralWidget(stackedWidget);

    screenManager->showHomeScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidget;
    delete screenManager;
    // delete playerManager;
}

// void MainWindow::startGame(int boardSize) {
//     boardModel = new BoardModel(boardSize);
//     boardView = new BoardView(boardModel, this);

//     connect(boardView, &BoardView::backToHomeScreen, this, &MainWindow::returnToHomeScreen);

//     stackedWidget->addWidget(boardView);
//     stackedWidget->setCurrentWidget(boardView);
// }

// void MainWindow::returnToHomeScreen() {
//     if (boardModel && boardView) {
//         delete boardModel;
//         delete boardView;
//     }
//     stackedWidget->setCurrentWidget(homeScreen);
// }
