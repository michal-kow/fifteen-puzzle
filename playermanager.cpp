#include "playermanager.h"

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
    currentPlayer = &players[0];
}

void PlayerManager::addPlayer(QString name) {
    players.append(QSharedPointer<Player>::create(name));
    savePlayersToFile();
}

void PlayerManager::switchPlayer(QString name) {
    for (int i = 0; i < players.length(); i++) {
        if (players[i]->getName() == name) {
            currentPlayer = &players[i];
        }
    }
}

QSharedPointer<Player> PlayerManager::getCurrentPlayer() {
    return *currentPlayer;
}

void PlayerManager::savePlayersToFile() {
    QFile file("players.json");

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open player file for writing.");
        return;
    }

    QJsonArray jsonArray;
    for (const auto& player : players) {
        QJsonObject jsonObj;
        jsonObj["name"] = player->getName();
        jsonObj["bestMoves"] = player->getBestMoves();
        jsonObj["bestTime"] = player->getBestTime();
        jsonArray.append(jsonObj);
    }

    QJsonDocument doc(jsonArray);
    file.write(doc.toJson());
    file.close();
}

void PlayerManager::loadPlayersFromFile() {
    QFile file("players.json");

    if (!file.open(QIODevice::ReadOnly)) {
        cout << "Couldn't open the file" << endl;
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isArray()) {
        cout << "Incorrect file format" << endl;
        return;
    }

    QJsonArray jsonArray = doc.array();
    players.clear();

    for (const QJsonValue& value : jsonArray) {
        if (value.isObject()) {
            QJsonObject jsonObj = value.toObject();
            players.append(QSharedPointer<Player>::create("testName"));
        }
    }
}
