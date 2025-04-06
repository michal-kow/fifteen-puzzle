#include "homescreen.h"

HomeScreen::HomeScreen(PlayerManager* _playerManager, QWidget* parent)
    : QWidget(parent), playerManager(_playerManager) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    playerLabel = new QLabel("Current Player: " + playerManager->getCurrentPlayerName() + QString(playerManager->getCurrentPlayerIsAI() ? " 🤖" : " 🧑"), this);
    layout->addWidget(playerLabel);

    boardSizeDropdown = new QComboBox(this);
    const int SMALLEST_BOARD_PICKABLE = 2; //TODO: edit after development
    const int BIGGEST_BOARD_PICKABLE = 5;
    for (int i = SMALLEST_BOARD_PICKABLE; i < BIGGEST_BOARD_PICKABLE + 1; i++) {
        boardSizeDropdown->addItem(QString(QString::number(i)+"x"+QString::number(i)), i);
    }
    layout->addWidget(boardSizeDropdown);

    layout->addWidget(new QLabel("AI algorithm"));

    algorithmDropdown = new QComboBox(this);
    algorithmDropdown->addItem("Random");
    algorithmDropdown->setEnabled(false);
    layout->addWidget(algorithmDropdown);

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

void HomeScreen::updateCurrentPlayer(QString playerName, bool isAI) {
    playerLabel->setText("Current Player: " + playerName + QString(isAI ? " 🤖" : " 🧑"));
    if (isAI) {
        algorithmDropdown->setEnabled(true);
    } else {
        algorithmDropdown->setEnabled(false);
    }
}
