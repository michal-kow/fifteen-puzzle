#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QPoint>

class BoardModel {
private:
    int boardSize; //size of the NxN board
    QVector<QVector<int>> board; //all tiles values stored in a 2D array
    QPoint emptyTile; //empty tile's position stored in the {x,y} format

public:
    BoardModel();

    BoardModel(int _boardSize);

    QVector<QVector<int>> generateSolvedBoard(int boardSize);
    void shuffle();
    bool isEmptyTileAdjacent(int tile);
    void moveTile(int tile);
    QPoint getTilesPosition(int tile);
    bool isSolved();
    int getBoardSize();
    QVector<QVector<int>> getBoard();
};

#endif // BOARDMODEL_H
