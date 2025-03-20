#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "boardmodel.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    BoardModel *board = new BoardModel;

    cout << board->getBoard()[0][0] << endl;

    int table[4][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11},
        {12, 13, 14, 15}
    };

    QList<QPushButton *> tiles = ui->centralwidget->findChildren<QPushButton *>(QString());
    foreach (QPushButton * tile, tiles) {
        int tilePositionX = tile->objectName().at(4).digitValue();
        int tilePositionY = tile->objectName().at(5).digitValue();
        tile->setText(QString::number(table[tilePositionX][tilePositionY]));
        connect(tile, &QPushButton::clicked, this, [this, tile](){ handleClick(tile); });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
