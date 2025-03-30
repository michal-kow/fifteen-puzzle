#include "playermanagerscreen.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

PlayerManagerScreen::PlayerManagerScreen(PlayerManager* playerManager, QWidget *parent)
    : QWidget{parent}, playerManager(playerManager) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    playerList = new QListWidget(this);
    layout->addWidget(playerList);

    newPlayerInput = new QLineEdit(this);
    newPlayerInput->setPlaceholderText("Enter new player name");
    layout->addWidget(newPlayerInput);

    addPlayerButton = new QPushButton("Add Player", this);
    setAsCurrentPlayerButton = new QPushButton("Pick Player", this);
    deletePlayerButton = new QPushButton("Delete Player", this);
    backButton = new QPushButton("Back", this);

    layout->addWidget(addPlayerButton);
    layout->addWidget(setAsCurrentPlayerButton);
    layout->addWidget(deletePlayerButton);
    layout->addWidget(backButton);

    updatePlayerList();

    connect(addPlayerButton, &QPushButton::clicked, this, &PlayerManagerScreen::addPlayer);
    connect(playerList, &QListWidget::itemDoubleClicked, this, &PlayerManagerScreen::selectPlayer);
    connect(setAsCurrentPlayerButton, &QPushButton::clicked, this, &PlayerManagerScreen::selectPlayer);
    connect(deletePlayerButton, &QPushButton::clicked, this, &PlayerManagerScreen::deletePlayer);
    connect(backButton, &QPushButton::clicked, this, &PlayerManagerScreen::goBackToHomeScreen);
}

void PlayerManagerScreen::updatePlayerList() {
    playerList->clear();
    for (const auto& player : playerManager->getPlayers()) {
        playerList->addItem(player->getName());
    }
}

void PlayerManagerScreen::addPlayer() {
    QString playerName = newPlayerInput->text().trimmed();
    if (playerName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Name", "Player name cannot be empty.");
        return;
    }

    if (!playerManager->addPlayer(playerName)) {
        QMessageBox::warning(this, "Error", "Player already exists.");
        return;
    }

    updatePlayerList();
    newPlayerInput->clear();
}

void PlayerManagerScreen::selectPlayer() {
    QListWidgetItem* selectedItem = playerList->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No Selection", "Please select a player to delete.");
        return;
    }

    QString playerName = selectedItem->text();
    playerManager->setCurrentPlayer(playerName);
    emit goBackToHomeScreen();
}

void PlayerManagerScreen::deletePlayer() {
    QListWidgetItem* selectedItem = playerList->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No Selection", "Please select a player to delete.");
        return;
    }

    QString playerName = selectedItem->text();
    playerManager->removePlayer(playerName);
    updatePlayerList();
}
