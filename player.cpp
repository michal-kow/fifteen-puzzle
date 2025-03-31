#include "player.h"

Player::Player(QString _name, QObject *parent)
    : QObject{parent}
{
    name = _name;
    bestTimes = QMap<int, int>();
    bestMoves = QMap<int, int>();
}

QString Player::getName() {
    return name;
}

QMap<int, int> Player::getBestTimes() {
    return bestTimes;
}

QMap<int, int> Player::getBestMoves() {
    return bestMoves;
}

void Player::updateBestMoves(int moves, int boardSize) {
    if (bestMoves.contains(boardSize)) {
        if (moves < bestMoves[boardSize]) {
            bestMoves[boardSize] = moves;
        }
    } else {
        bestMoves.insert(boardSize, moves);
    }
}

void Player::updateBestTimes(int time, int boardSize) {
    if (bestTimes.contains(boardSize)) {
        if (time < bestTimes[boardSize]) {
            bestTimes[boardSize] = time;
        }
    } else {
        bestTimes.insert(boardSize, time);
    }
}

