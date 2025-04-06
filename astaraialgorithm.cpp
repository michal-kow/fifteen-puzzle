#include "astaraialgorithm.h"
#include <QSet>
#include <QQueue>
#include <QDebug>
#include <queue>

using namespace std;

AStarAIAlgorithm::AStarAIAlgorithm(QObject* parent) : AIAlgorithm(parent) {}

int AStarAIAlgorithm::chooseMove(PuzzleModel& model) {
    QVector<QVector<int>> board = model.getBoard();
    QPoint emptyTile = model.getTilePosition(0);

    using State = PuzzleState;
    auto cmp = [](const State& a, const State& b) { return a > b; };
    priority_queue<State, vector<State>, decltype(cmp)> openSet(cmp);

    QSet<QString> visited;
    State start{ board, 0, manhattanDistance(board), emptyTile, {} };
    openSet.push(start);

    while (!openSet.empty()) {
        State current = openSet.top();
        openSet.pop();

        QString stateKey = boardToString(current.board);
        if (visited.contains(stateKey)) continue;
        visited.insert(stateKey);

        if (manhattanDistance(current.board) == 0) {
            return current.moveHistory.isEmpty() ? -1 : current.moveHistory.first();
        }

        for (const State& neighbor : getNeighbors(current)) {
            QString neighborKey = boardToString(neighbor.board);
            if (!visited.contains(neighborKey)) {
                openSet.push(neighbor);
            }
        }
    }

    return -1;
}

int AStarAIAlgorithm::manhattanDistance(const QVector<QVector<int>>& board) {
    int dist = 0;
    int n = board.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int val = board[i][j];
            if (val != 0) {
                int targetRow = (val - 1) / n;
                int targetCol = (val - 1) % n;
                dist += abs(i - targetRow) + abs(j - targetCol);
            }
        }
    }
    return dist;
}

QVector<AStarAIAlgorithm::PuzzleState> AStarAIAlgorithm::getNeighbors(const PuzzleState& state) {
    QVector<PuzzleState> neighbors;
    int n = state.board.size();
    int x = state.emptyTile.x();
    int y = state.emptyTile.y();

    QVector<QPoint> directions = {
        { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }
    };

    for (const QPoint& d : directions) {
        int nx = x + d.x();
        int ny = y + d.y();
        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            QVector<QVector<int>> newBoard = state.board;
            std::swap(newBoard[x][y], newBoard[nx][ny]);

            PuzzleState neighbor;
            neighbor.board = newBoard;
            neighbor.emptyTile = { nx, ny };
            neighbor.gCost = state.gCost + 1;
            neighbor.hCost = manhattanDistance(newBoard);
            neighbor.moveHistory = state.moveHistory;
            neighbor.moveHistory.append(newBoard[x][y]);  // The tile that was moved

            neighbors.append(neighbor);
        }
    }

    return neighbors;
}

QString AStarAIAlgorithm::boardToString(const QVector<QVector<int>>& board) {
    QStringList parts;
    for (const auto& row : board) {
        for (int val : row) {
            parts << QString::number(val);
        }
    }
    return parts.join(",");
}
