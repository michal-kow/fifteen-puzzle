#include "puzzlemodel.h"
#include <QVector>
#include <QPoint>
#include <QRandomGenerator>

using namespace std;

PuzzleModel::PuzzleModel() {
    // Create the default 15 Puzzle board (board size is 4) and shuffle it
    createNewPuzzle(4);
}

PuzzleModel::PuzzleModel(int _boardSize) {
    // Set properties based on the board size and shuffle the board
    createNewPuzzle(_boardSize);
}

QVector<QVector<int>> PuzzleModel::generateSolvedBoard(int boardSize) {
    // Generate a solved N-size board (solved being the numbers going from 1 to N^2-1 with the 0 as the empty tile in the last spot)
    QVector<QVector<int>> solvedBoard(boardSize, QVector<int>(boardSize, 0));

    int value = 1; //start assigning the values from 1
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            if (row == boardSize - 1 && col == boardSize - 1) {
                solvedBoard[row][col] = 0; //assign 0 if it's the last spot
            } else {
                solvedBoard[row][col] = value++;
            }
        }
    }

    return solvedBoard;
}

void PuzzleModel::shuffle() {
    // Shuffle the board's values
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

    if (isSolved()) {
        shuffle();
    }
}

bool PuzzleModel::isEmptyTileAdjacent(int tile) {
    // Check if a tile with the given value is adjacent to the empty tile
    QPoint tilesPosition = getTilePosition(tile);

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

QPoint PuzzleModel::getTilePosition(int tile) {
    // Get position of a tile with the given value
    for (int row = 0; row < board.size(); row++) {
        for (int col = 0; col < board[row].size(); col++) {
            if (board[row][col] == tile) {
                return {row, col};
            }
        }
    }

    return {-1, -1};
}

bool PuzzleModel::moveTile(int tile) {
    // Swap the given tile with the empty spot; return true if possile or false if not
    if (isEmptyTileAdjacent(tile)) {
        QPoint tilesPosition = getTilePosition(tile);
        swap(board[tilesPosition.x()][tilesPosition.y()], board[emptyTile.x()][emptyTile.y()]);
        emptyTile = {tilesPosition.x(), tilesPosition.y()};
        return true;
    }

    return false;
};

bool PuzzleModel::isSolved() {
    // Check if the puzzle is solved
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

void PuzzleModel::createNewPuzzle(int _boardSize) {
    boardSize = _boardSize;
    board = generateSolvedBoard(boardSize);
    emptyTile = {boardSize - 1, boardSize - 1};

    shuffle();
}

int PuzzleModel::getBoardSize() {
    return boardSize;
}

QVector<QVector<int>> PuzzleModel::getBoard() {
    return board;
}
