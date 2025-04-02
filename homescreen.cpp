#include "homescreen.h"

HomeScreen::HomeScreen(PlayerManager* _playerManager, QWidget* parent)
    : QWidget(parent), playerManager(_playerManager) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    playerLabel = new QLabel("Current Player: " + playerManager->getCurrentPlayerName(), this);
    layout->addWidget(playerLabel);

    boardSizeDropdown = new QComboBox(this);
    boardSizeDropdown->addItem("2x2", 2); //TODO: remove after development
    boardSizeDropdown->addItem("3x3", 3);
    boardSizeDropdown->addItem("4x4", 4);
    boardSizeDropdown->addItem("5x5", 5);
    layout->addWidget(boardSizeDropdown);

    startButton = new QPushButton("Start Game", this);
    connect(startButton, &QPushButton::clicked, this, &HomeScreen::onStartClicked);
    layout->addWidget(startButton);

    managePlayersButton = new QPushButton("Manage Players", this);
    connect(managePlayersButton, &QPushButton::clicked, this, &HomeScreen::openPlayerManagement);
    layout->addWidget(managePlayersButton);

    leaderboardButton = new QPushButton("Leaderboard", this);
    connect(leaderboardButton, &QPushButton::clicked, this, &HomeScreen::openLeaderboard);
    layout->addWidget(leaderboardButton);

    setLayout(layout);

    connect(playerManager, &PlayerManager::currentPlayerChanged, this, &HomeScreen::updateCurrentPlayer);
}

void HomeScreen::onStartClicked() {
    int boardSize = boardSizeDropdown->currentData().toInt();
    emit boardSizeSelected(boardSize);
}

void HomeScreen::updateCurrentPlayer(QString playerName) {
    playerLabel->setText("Current Player: " + playerName);
}
