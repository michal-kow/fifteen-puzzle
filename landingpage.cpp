#include "landingpage.h"

LandingPage::LandingPage(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    boardSizeDropdown = new QComboBox(this);
    boardSizeDropdown->addItem("2x2", 2);
    boardSizeDropdown->addItem("3x3", 3);
    boardSizeDropdown->addItem("4x4", 4);
    boardSizeDropdown->addItem("5x5", 5);
    boardSizeDropdown->addItem("6x6", 6);
    boardSizeDropdown->addItem("7x7", 7);

    startButton = new QPushButton("Start Game", this);
    connect(startButton, &QPushButton::clicked, this, &LandingPage::onStartClicked);

    layout->addWidget(boardSizeDropdown);
    layout->addWidget(startButton);
    setLayout(layout);
}

void LandingPage::onStartClicked() {
    int boardSize = boardSizeDropdown->currentData().toInt();
    emit boardSizeSelected(boardSize);
}
