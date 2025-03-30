#include "homescreen.h"

// HomeScreen::HomeScreen(PlayerManager* _playerManager, QWidget* parent)
//     : QWidget(parent), playerManager(_playerManager) {
HomeScreen::HomeScreen(QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // playerLabel = new QLabel(playerManager->getCurrentPlayer()->getName(), this);
    playerLabel = new QLabel("PlayerName", this);
    layout->addWidget(playerLabel);

    boardSizeDropdown = new QComboBox(this);
    boardSizeDropdown->addItem("2x2", 2);
    boardSizeDropdown->addItem("3x3", 3);
    boardSizeDropdown->addItem("4x4", 4);
    boardSizeDropdown->addItem("5x5", 5);
    boardSizeDropdown->addItem("6x6", 6);
    boardSizeDropdown->addItem("7x7", 7);
    layout->addWidget(boardSizeDropdown);

    startButton = new QPushButton("Start Game", this);
    connect(startButton, &QPushButton::clicked, this, &HomeScreen::onStartClicked);
    layout->addWidget(startButton);

    managePlayersButton = new QPushButton("Manage Players", this);
    connect(managePlayersButton, &QPushButton::clicked, this, &HomeScreen::openPlayerManagement);
    layout->addWidget(managePlayersButton);

    setLayout(layout);
}

void HomeScreen::onStartClicked() {
    int boardSize = boardSizeDropdown->currentData().toInt();
    emit boardSizeSelected(boardSize);
}
