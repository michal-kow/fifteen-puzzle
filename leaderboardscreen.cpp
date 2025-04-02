#include "leaderboardscreen.h"

#include <QLabel>
#include <QHeaderView>
#include <iostream>

using namespace std;

LeaderboardScreen::LeaderboardScreen(PlayerManager* _playerManager, QWidget *parent)
    : QWidget(parent), playerManager(_playerManager)
{
    layout = new QVBoxLayout(this);
    QLabel* title = new QLabel("Leaderboard", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);

    bestTimeTable = new QTableWidget(3, 3, this);
    bestMovesTable = new QTableWidget(3, 3, this);

    bestTimeTable->setHorizontalHeaderLabels({"Board size", "Time", "Player"});
    bestMovesTable->setHorizontalHeaderLabels({"Board size", "Moves", "Player"});
    bestTimeTable->verticalHeader()->setVisible(false);
    bestMovesTable->verticalHeader()->setVisible(false);
    bestTimeTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    bestMovesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    updateLeaderboard();

    layout->addWidget(new QLabel("Best Times"));
    layout->addWidget(bestTimeTable);
    layout->addWidget(new QLabel("Best Moves"));
    layout->addWidget(bestMovesTable);

    backButton = new QPushButton("Back", this);
    layout->addWidget(backButton);
    connect(backButton, &QPushButton::clicked, this, &LeaderboardScreen::goBackToHomeScreen);

    connectPlayersForUpdates();
    connect(playerManager, &PlayerManager::addedPlayer, this, &LeaderboardScreen::connectPlayersForUpdates);
}

void LeaderboardScreen::connectPlayersForUpdates() {
    for (const auto& player : playerManager->getPlayers()) {
        bool connected = connect(player.get(), &Player::updatedBestStats, this, &LeaderboardScreen::updateLeaderboard);
        if (!connected) {
            qDebug() << "Failed to connect statsUpdated signal for player:" << player->getName();
        } else {
            qDebug() << "Connected statsUpdated signal for player:" << player->getName();
        }
    }
}

//TODO: call updateLeaderboard when a player is removed
void LeaderboardScreen::updateLeaderboard() {
    cout << "updating leaderboard..." << endl;
    auto players = playerManager->getPlayers();

    QMap<int, QPair<int, QString>> bestMoves;
    QMap<int, QPair<int, QString>> bestTimes;

    int boardSize = 2;//TODO: change 2 to 3 after tests

    for (int i = 0; i < 3; i++) {
        bestTimeTable->setItem(i, 0, new QTableWidgetItem(QString::number(boardSize)+"x"+QString::number(boardSize)));
        bestMovesTable->setItem(i, 0, new QTableWidgetItem(QString::number(boardSize)+"x"+QString::number(boardSize)));

        fillWithData(i, bestTimeTable, boardSize, "time");
        fillWithData(i, bestMovesTable, boardSize, "moves");

        boardSize++;
    }
}

void LeaderboardScreen::fillWithData(int i, QTableWidget* table, int boardSize, QString type) {
    auto players = playerManager->getPlayers();

    for (QSharedPointer<Player> player : players) {
        QTableWidgetItem *bestCellValue = table->item(i, 1);

        QMap<int, int> playerBestValues = type == "time" ? player->getBestTimes() : player->getBestMoves();

        int playerBestValueForBoardSize = playerBestValues.contains(boardSize) ? playerBestValues[boardSize] : -1;

        if (!bestCellValue) {
            if (playerBestValueForBoardSize < 0) {
                fillCells(table, i, QString('-'), QString('-'));
            } else {
                fillCells(table, i, QString::number(playerBestValueForBoardSize), player->getName());
            }
        } else if (playerBestValueForBoardSize >= 0) {
            if (bestCellValue->text() == '-') {
                fillCells(table, i, QString::number(playerBestValueForBoardSize), player->getName());
            } else if (bestCellValue ->text().toInt() > playerBestValueForBoardSize) {
                fillCells(table, i, QString::number(playerBestValueForBoardSize), player->getName());
            }
        }
    }
}

void LeaderboardScreen::fillCells(QTableWidget* table, int i, QString value, QString name) {
    table->setItem(i, 1, new QTableWidgetItem(value));
    table->setItem(i, 2, new QTableWidgetItem(name));
}
