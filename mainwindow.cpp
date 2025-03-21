#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardmodel.h"
#include "boardview.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    boardModel = new BoardModel(4);

    boardView = new BoardView(boardModel, this);
    setCentralWidget(boardView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete boardModel;
    delete boardView;
}
