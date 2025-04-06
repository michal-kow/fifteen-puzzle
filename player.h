#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QString>

class Player : public QObject
{
    Q_OBJECT

protected:
    QString name;

public:
    explicit Player(const QString& name, QObject *parent = nullptr);

    QString getName() const;
    virtual void updateBestTimes(int time, int boardSize) = 0;
    virtual void updateBestMoves(int moves, int boardSize) = 0;
    virtual bool isAI() const = 0;
};

#endif // PLAYER_H
