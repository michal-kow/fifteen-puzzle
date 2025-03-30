#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT

private:
    QString name;
    int bestTime;
    int bestMoves;

public:
    explicit Player(QString _name, QObject *parent = nullptr);
    QString getName();
    int getBestTime();
    int getBestMoves();
    void updateBestTime(int time);
    void updateBestMoves(int moves);

signals:
};

#endif // PLAYER_H
