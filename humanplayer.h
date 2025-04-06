#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "player.h"
#include <QMap>

class HumanPlayer : public Player
{
    Q_OBJECT

private:
    QMap<int, int> bestTimes;
    QMap<int, int> bestMoves;

public:
    HumanPlayer(const QString& name, QObject *parent = nullptr);

    QMap<int, int> getBestTimes();
    QMap<int, int> getBestMoves();
    void updateBestTimes(int time, int boardSize) override;
    void updateBestMoves(int moves, int boardSize) override;
    bool isAI() const override { return false; }

signals:
    void updatedBestStats();
};

#endif // HUMANPLAYER_H
