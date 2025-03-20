#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QVector>
#include <QPoint>

class BoardModel
{
private:
    QVector<QVector<int>> board;
    QPoint emptyTile;
    int boardSize;

public:
    BoardModel();

    BoardModel(QVector<QVector<int>> _board, QPoint _emptyTile, int _boardSize);

    void shuffle();
    bool isEmptyTileNeighbor(int tile);
    void moveTile(int tile);
    QPoint getTilesPosition(int tile);
    bool isSolved();
    int getBoardSize();
    QVector<QVector<int>> getBoard();
};

#endif // BOARDMODEL_H
