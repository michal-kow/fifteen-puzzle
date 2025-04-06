#include "humanplayer.h"

HumanPlayer::HumanPlayer(const QString& name, QObject *parent)
    : Player(name, parent)
{
}

QMap<int, int> HumanPlayer::getBestTimes() {
    return bestTimes;
}

QMap<int, int> HumanPlayer::getBestMoves() {
    return bestMoves;
}

void HumanPlayer::updateBestTimes(int time, int boardSize) {
    if (!bestTimes.contains(boardSize) || time < bestTimes[boardSize]) {
        bestTimes[boardSize] = time;
        emit updatedBestStats();
    }
}

void HumanPlayer::updateBestMoves(int moves, int boardSize) {
    if (!bestMoves.contains(boardSize) || moves < bestMoves[boardSize]) {
        bestMoves[boardSize] = moves;
        emit updatedBestStats();
    }
}
