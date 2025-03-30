#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include <player.h>

class PlayerManager : public QObject
{
    Q_OBJECT

private:
    QVector<QSharedPointer<Player>> players;
    QSharedPointer<Player> *currentPlayer;

public:
    explicit PlayerManager(QObject *parent = nullptr);
    void addPlayer(QString name);
    void switchPlayer(QString name);
    QSharedPointer<Player> getCurrentPlayer();
    void savePlayersToFile();
    void loadPlayersFromFile();

signals:
};

#endif // PLAYERMANAGER_H
