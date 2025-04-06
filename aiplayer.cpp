#include "aiplayer.h"

AIPlayer::AIPlayer(const QString& name, QObject *parent)
    : Player(name, parent)
{
}

void AIPlayer::updateBestTimes(int, int) {
    // Do nothing
}

void AIPlayer::updateBestMoves(int, int) {
    // Do nothing
}
