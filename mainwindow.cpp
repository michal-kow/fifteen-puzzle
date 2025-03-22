#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardmodel.h"
#include "boardview.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(this);

    landingPage = new LandingPage();
    connect(landingPage, &LandingPage::boardSizeSelected, this, &MainWindow::startGame);

    stackedWidget->addWidget(landingPage);

    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete landingPage;
    delete boardModel;
    delete boardView;
    delete stackedWidget;
}

void MainWindow::startGame(int boardSize) {
    boardModel = new BoardModel(boardSize);
    boardView = new BoardView(boardModel, this);

    connect(boardView, &BoardView::backToLandingPage, this, &MainWindow::returnToLandingPage);

    stackedWidget->addWidget(boardView);
    stackedWidget->setCurrentWidget(boardView);
}

void MainWindow::returnToLandingPage() {
    if (boardModel) {
        delete boardModel;
        delete boardView;
    }
    stackedWidget->setCurrentWidget(landingPage);
}
