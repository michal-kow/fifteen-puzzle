#ifndef PUZZLEMODEL_H
#define PUZZLEMODEL_H

#include <QVector>
#include <QPoint>

class PuzzleModel {
private:
    int boardSize; //size of the NxN board
    QVector<QVector<int>> board; //all tiles values stored in a 2D array
    QPoint emptyTile; //empty tile's position stored in the {x,y} format

public:
    PuzzleModel();

    PuzzleModel(int _boardSize);

    QVector<QVector<int>> generateSolvedBoard(int boardSize);
    void shuffle();
    bool isEmptyTileAdjacent(int tile);
    bool moveTile(int tile);
    QPoint getTilePosition(int tile);
    bool isSolved();
    void createNewPuzzle(int _boardSize);
    int getBoardSize();
    QVector<QVector<int>> getBoard();
};

#endif // PUZZLEMODEL_H
