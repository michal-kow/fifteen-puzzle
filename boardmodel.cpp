#include "boardmodel.h"
#include <QVector>
#include <QPoint>
#include <QRandomGenerator>

using namespace std;

BoardModel::BoardModel() {
    board = {{0, 1}, {2, 3}};
    QPoint emptyTile = {0, 0};
    boardSize = 2;
}

BoardModel::BoardModel(QVector<QVector<int>> _board, QPoint _emptyTile, int _boardSize) {
    board = _board;
    emptyTile = _emptyTile;
    boardSize = _boardSize;
}

void BoardModel::shuffle() {
    for (int i = 0; i < 1000; i++) {
        int rand = QRandomGenerator::global()->bounded(4);
        int x = emptyTile.x();
        int y = emptyTile.y();

        switch (rand) {
        case 0:
            if (x > 0) {
             moveTile(board[x-1][y]);
            }
            break;
        case 1:
            if (y > 0) {
             moveTile(board[x][y-1]);
            }
            break;
        case 2:
            if (x < boardSize - 1) {
             moveTile(board[x+1][y]);
            }
            break;
        case 3:
            if (y < boardSize - 1) {
             moveTile(board[x][y+1]);
            }
            break;
        default:
            break;
        }
    }
}

bool BoardModel::isEmptyTileNeighbor(int tile) {
    QPoint tilesPosition = getTilesPosition(tile);

    if (
        (emptyTile.x() - 1 == tilesPosition.x() && emptyTile.y() == tilesPosition.y()) ||
        (emptyTile.x() == tilesPosition.x() && emptyTile.y() - 1 == tilesPosition.y()) ||
        (emptyTile.x() + 1 == tilesPosition.x() && emptyTile.y() == tilesPosition.y()) ||
        (emptyTile.x() == tilesPosition.x() && emptyTile.y() + 1 == tilesPosition.y())
        ) {
        return true;
    }

    return false;
}

QPoint BoardModel::getTilesPosition(int tile) {
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            if (board[row][col] == tile) {
                return {row, col};
            }
        }
    }

    return {-1, -1};
}

void BoardModel::moveTile(int tile) {
    if (isEmptyTileNeighbor(tile)) {
        QPoint tilesPosition = getTilesPosition(tile);
        swap(board[tilesPosition.x()][tilesPosition.y()], board[emptyTile.x()][emptyTile.y()]);
        emptyTile = {tilesPosition.x(), tilesPosition.y()};
    }
};

bool BoardModel::isSolved() {
    int expectedValue = 1;

    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            if (row == boardSize - 1 && col == boardSize - 1) {
                return board[row][col] == 0;
            }

            if (board[row][col] != expectedValue) {
                return false;
            }
            expectedValue++;
        }
    }
    return true;
}

int BoardModel::getBoardSize() {
    return boardSize;
}

QVector<QVector<int>> BoardModel::getBoard() {
    return board;
}
