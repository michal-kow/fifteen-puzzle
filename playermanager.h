#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include <humanplayer.h>

class PlayerManager : public QObject
{
    Q_OBJECT

private:
    QVector<QSharedPointer<Player>> players;
    QSharedPointer<Player> currentPlayer;

public:
    explicit PlayerManager(QObject *parent = nullptr);
    bool addPlayer(const QString& name, const bool isAI);
    void removePlayer(const QString& name);
    QString getCurrentPlayerName();
    bool getCurrentPlayerIsAI();
    void setCurrentPlayer(QString name);
    QVector<QSharedPointer<Player>> getPlayers();
    bool savePlayersToFile();
    bool loadPlayersFromFile();

signals:
    void currentPlayerChanged(QString newPlayerName, bool isAI);
    void addedPlayer();
    void removedPlayer();

public slots:
    void updatePlayerStats(int moves, int time, int boardSize);
};

#endif // PLAYERMANAGER_H
