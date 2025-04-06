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

    aiCheckbox = new QCheckBox("AI Player", this);
    layout->addWidget(aiCheckbox);

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
    connect(backButton, &QPushButton::clicked, this, &PlayerManagerScreen::onBackButtonClicked);
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

    bool isAI = aiCheckbox->isChecked();

    if (!playerManager->addPlayer(playerName, isAI)) {
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

    QMessageBox msgBox;
    msgBox.setWindowTitle("Are you sure?");
    msgBox.setText("Are you sure? Deleting this player will also remove their stats!");
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);

    int result = msgBox.exec();

    switch(result) {
        case QMessageBox::Ok:
            playerManager->removePlayer(playerName);
            updatePlayerList();
            break;

        case QMessageBox::Cancel:
            break;
    }
}

void PlayerManagerScreen::onBackButtonClicked() {
    QString currentPlayerName = playerManager->getCurrentPlayerName();

    bool playerStillExists = false;
    for (const auto& player : playerManager->getPlayers()) {
        if (player->getName() == currentPlayerName) {
            playerStillExists = true;
            break;
        }
    }

    if (!playerStillExists) {
        QMessageBox::warning(this, "Player Missing", "The selected player was deleted. Please choose another.");
        return;
    }

    emit goBackToHomeScreen();
}
