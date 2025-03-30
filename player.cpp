#include "player.h"

Player::Player(QString _name, QObject *parent)
    : QObject{parent}
{
    name = _name;
    bestTime = -1;
    bestMoves = -1;
}

QString Player::getName() {
    return name;
}

int Player::getBestTime() {
    return bestTime;
}

int Player::getBestMoves() {
    return bestMoves;
}

void Player::updateBestMoves(int moves) {
    if (bestMoves == -1) {
        bestMoves = moves;
    } else if (moves < bestMoves) {
        bestMoves = moves;
    }
}

void Player::updateBestTime(int time) {
    if (bestTime == -1) {
        bestTime = time;
    } else if (time < bestTime) {
        bestTime = time;
    }
}

