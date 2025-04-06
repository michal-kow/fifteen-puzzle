#include "playermanager.h"
#include "humanplayer.h"
#include "aiplayer.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <iostream>

using namespace std;

PlayerManager::PlayerManager(QObject *parent)
    : QObject{parent}
{
    loadPlayersFromFile();
    if (players.length() > 0) {
        currentPlayer = players[0];
    } else {
        addPlayer("Guest", false);
        savePlayersToFile();
    }
}

bool PlayerManager::addPlayer(const QString& name, const bool isAI) {
    for (const auto& player : players) {
        if (player->getName() == name) {
            return false;
        }
    }
    if (isAI) {
        players.append(QSharedPointer<AIPlayer>::create(name));
    } else {
        players.append(QSharedPointer<HumanPlayer>::create(name));
    }
    savePlayersToFile();
    emit addedPlayer();
    return true;
}

void PlayerManager::removePlayer(const QString& name) {
    players.erase(
        remove_if(
            players.begin(),
            players.end(),
            [&name](const QSharedPointer<Player>& player) {
                return player->getName() == name;
            }
        ),
        players.end()
    );
    savePlayersToFile();
    emit removedPlayer();
}

QString PlayerManager::getCurrentPlayerName() {
    return currentPlayer ? currentPlayer->getName() : "Guest";
}

bool PlayerManager::getCurrentPlayerIsAI() {
    return currentPlayer->isAI();
}

void PlayerManager::setCurrentPlayer(QString name) {
    for (QSharedPointer<Player> player : players) {
        if (player->getName() == name) {
            currentPlayer = player;
            emit currentPlayerChanged(name, getCurrentPlayerIsAI());
            return;
        }
    }
}

QVector<QSharedPointer<Player>> PlayerManager::getPlayers() {
    return players;
}

bool PlayerManager::savePlayersToFile() {
    QFile file("players.json");

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open player file for writing.");
        return false;
    }

    QJsonArray jsonArray;

    for (QSharedPointer<Player> player : players) {
        QJsonObject jsonObj;
        jsonObj["name"] = player->getName();
        jsonObj["isAI"] = player->isAI();

        if (!player->isAI()) {
            HumanPlayer* humanPlayer = dynamic_cast<HumanPlayer*>(player.get());
            QJsonObject bestTimesObj;
            QMap<int, int> bestTimes = humanPlayer->getBestTimes();
            for (auto i = bestTimes.cbegin(), end = bestTimes.cend(); i!= end; ++i) {
                bestTimesObj[QString::number(i.key())] = i.value();
            }

            QJsonObject bestMovesObj;
            QMap<int, int> bestMoves = humanPlayer->getBestMoves();
            for (auto i = bestMoves.cbegin(), end = bestMoves.cend(); i != end; ++i) {
                bestMovesObj[QString::number(i.key())] = i.value();
            }

            jsonObj["bestTimes"] = bestTimesObj;
            jsonObj["bestMoves"] = bestMovesObj;
        }
        jsonArray.append(jsonObj);
    }

    QJsonDocument doc(jsonArray);
    file.write(doc.toJson());
    file.close();

    return true;
}

bool PlayerManager::loadPlayersFromFile() {
    QFile file("players.json");

    if (!file.open(QIODevice::ReadOnly)) {
        cout << "Couldn't open the file" << endl;
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        cout << "Incorrect file format" << endl;
        return false;
    }

    QJsonArray jsonArray = doc.array();
    players.clear();

    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject jsonObj = value.toObject();
            QSharedPointer<Player> player;
            if (jsonObj["isAI"] == true) {
                player = QSharedPointer<AIPlayer>::create(jsonObj["name"].toString());
            } else {
                player = QSharedPointer<HumanPlayer>::create(jsonObj["name"].toString());

                if (jsonObj.contains("bestTimes") && jsonObj["bestTimes"].isObject()) {
                    QJsonObject bestTimesObj = jsonObj["bestTimes"].toObject();
                    for (QString key : bestTimesObj.keys()) {
                        player->updateBestTimes(bestTimesObj[key].toInt(), key.toInt());
                    }
                }

                if (jsonObj.contains("bestMoves") && jsonObj["bestMoves"].isObject()) {
                    QJsonObject bestMovesObj = jsonObj["bestMoves"].toObject();
                    for (QString key : bestMovesObj.keys()) {
                        player->updateBestMoves(bestMovesObj[key].toInt(), key.toInt());
                    }
                }
            }

            players.append(player);
        }
    }

    return true;
}

void PlayerManager::updatePlayerStats(int moves, int time, int boardSize) {
    if (!currentPlayer) return;

    currentPlayer->updateBestMoves(moves, boardSize);
    currentPlayer->updateBestTimes(time, boardSize);

    savePlayersToFile();
}
