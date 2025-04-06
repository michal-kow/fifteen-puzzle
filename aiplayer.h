#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player
{
    Q_OBJECT

public:
    explicit AIPlayer(const QString& name, QObject *parent = nullptr);

    void updateBestTimes(int time, int boardSize) override;
    void updateBestMoves(int moves, int boardSize) override;
    bool isAI() const override { return true; }
};

#endif // AIPLAYER_H
