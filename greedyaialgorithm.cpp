#include "greedyaialgorithm.h"

GreedyAIAlgorithm::GreedyAIAlgorithm(QObject *parent)
    : AIAlgorithm{parent}
{}

int GreedyAIAlgorithm::chooseMove(PuzzleModel& model) {
    QVector<QVector<int>> board = model.getBoard();
    auto [x, y] = model.getTilePosition(0);

    if (x > 0) return board[x - 1][y];
    if (y > 0) return board[x][y - 1];
    if (x < board.size() - 1) return board[x + 1][y];
    return board[x][y + 1];
}
