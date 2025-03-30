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
        jsonObj["bestMoves"] = player->getBestMoves();
        jsonObj["bestTime"] = player->getBestTime();
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
            players.append(QSharedPointer<Player>::create(jsonObj["name"].toString()));
        }
    }

    return true;
}
