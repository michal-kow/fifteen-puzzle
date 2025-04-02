#include "playermanager.h"
#include "player.h"

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
        addPlayer("Guest");
        savePlayersToFile();
    }
}

bool PlayerManager::addPlayer(const QString& name) {
    for (const auto& player : players) {
        if (player->getName() == name) {
            return false;
        }
    }
    players.append(QSharedPointer<Player>::create(name));
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
}

QString PlayerManager::getCurrentPlayerName() {
    return currentPlayer ? currentPlayer->getName() : "Guest";
}

void PlayerManager::setCurrentPlayer(QString name) {
    for (QSharedPointer<Player> player : players) {
        if (player->getName() == name) {
            currentPlayer = player;
            emit currentPlayerChanged(name);
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

        QJsonObject bestTimesObj;
        QMap<int, int> bestTimes = player->getBestTimes();
        for (auto i = bestTimes.cbegin(), end = bestTimes.cend(); i!= end; ++i) {
            bestTimesObj[QString::number(i.key())] = i.value();
        }

        QJsonObject bestMovesObj;
        QMap<int, int> bestMoves = player->getBestMoves();
        for (auto i = bestMoves.cbegin(), end = bestMoves.cend(); i != end; ++i) {
            bestMovesObj[QString::number(i.key())] = i.value();
        }

        jsonObj["bestTimes"] = bestTimesObj;
        jsonObj["bestMoves"] = bestMovesObj;
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
            QSharedPointer<Player> player = QSharedPointer<Player>::create(jsonObj["name"].toString());

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
