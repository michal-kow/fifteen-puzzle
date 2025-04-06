#ifndef ASTARAIALGORITHM_H
#define ASTARAIALGORITHM_H

#include "aialgorithm.h"

class AStarAIAlgorithm : public AIAlgorithm
{
    Q_OBJECT

public:
    explicit AStarAIAlgorithm(QObject *parent = nullptr);
    int chooseMove(PuzzleModel& model) override;

private:
    struct PuzzleState {
        QVector<QVector<int>> board;
        int gCost;
        int hCost;
        QPoint emptyTile;
        QVector<int> moveHistory;

        int fCost() const { return gCost + hCost; }
        bool operator>(const PuzzleState& other) const {
            return fCost() > other.fCost();
        }
    };

    int manhattanDistance(const QVector<QVector<int>>& board);
    QVector<PuzzleState> getNeighbors(const PuzzleState& state);
    QString boardToString(const QVector<QVector<int>>& board);
};

#endif // ASTARAIALGORITHM_H
