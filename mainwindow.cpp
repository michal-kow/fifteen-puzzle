#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);
    stackedWidget->setFixedSize(400, 400);
    playerManager = new PlayerManager(this);
    screenManager = new ScreenManager(stackedWidget, playerManager, this);

    setCentralWidget(stackedWidget);

    screenManager->showHomeScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidget;
    delete screenManager;
    delete playerManager;
}
