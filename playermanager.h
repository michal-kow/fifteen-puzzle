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
    QSharedPointer<Player> currentPlayer;

public:
    explicit PlayerManager(QObject *parent = nullptr);
    bool addPlayer(const QString& name);
    void removePlayer(const QString& name);
    QString getCurrentPlayerName();
    void setCurrentPlayer(QString name);
    QVector<QSharedPointer<Player>> getPlayers();
    bool savePlayersToFile();
    bool loadPlayersFromFile();

signals:
    void currentPlayerChanged(QString newPlayerName);
};

#endif // PLAYERMANAGER_H
