#include "randomaialgorithm.h"

#include <QRandomGenerator>


RandomAIAlgorithm::RandomAIAlgorithm(QObject *parent)
    : AIAlgorithm(parent)
{
}

int RandomAIAlgorithm::chooseMove(PuzzleModel& model) {
    QVector<QVector<int>> board = model.getBoard();
    auto [x, y] = model.getTilePosition(0);

    QVector<int> candidates;
    if (x > 0) candidates.append(board[x-1][y]);
    if (y > 0) candidates.append(board[x][y-1]);
    if (x < model.getBoardSize()-1) candidates.append(board[x+1][y]);
    if (y < model.getBoardSize()-1) candidates.append(board[x][y+1]);

    if (!candidates.isEmpty())
        return candidates[QRandomGenerator::global()->bounded(candidates.size())];

    return -1;
}
