#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QMap>

class Player : public QObject
{
    Q_OBJECT

private:
    QString name;
    QMap<int, int> bestTimes;
    QMap<int, int> bestMoves;

public:
    explicit Player(QString _name, QObject *parent = nullptr);
    QString getName();
    QMap<int, int> getBestTimes();
    QMap<int, int> getBestMoves();
    void updateBestTimes(int time, int boardSize);
    void updateBestMoves(int moves, int boardSize);

signals:
};

#endif // PLAYER_H
