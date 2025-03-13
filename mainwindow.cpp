#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

bool checkIfEmptyTileIsNeighbor(int tilePositionX, int tilePositionY, int table[4][4]) {
    bool isNeighor = false;

    if (tilePositionX >= 1) {
        if (table[tilePositionX-1][tilePositionY] == 0) {
            isNeighor = true;
        }
    }

    if (tilePositionX <= 2) {
        if (table[tilePositionX+1][tilePositionY] == 0) {
            isNeighor = true;
        }
    }

    if (tilePositionY >= 1) {
        if (table[tilePositionX][tilePositionY-1] == 0) {
            isNeighor = true;
        }
    }

    if (tilePositionY <= 2) {
        if (table[tilePositionX][tilePositionY+1] == 0) {
            isNeighor = true;
        }
    }

    return isNeighor;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
        bool isEmptyTileNeighbor = checkIfEmptyTileIsNeighbor(tilePositionX, tilePositionY, table);
        cout << "IsEmptyTileNeighbor for: " << tilePositionX << ":" << tilePositionY << ": " << isEmptyTileNeighbor << endl;
        connect(tile, &QPushButton::clicked, this, [this, tile](){ handleClick(tile); });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
