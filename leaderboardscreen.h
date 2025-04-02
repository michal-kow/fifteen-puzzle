#ifndef LEADERBOARDSCREEN_H
#define LEADERBOARDSCREEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>

#include <playermanager.h>

class LeaderboardScreen : public QWidget
{
    Q_OBJECT

private:
    PlayerManager* playerManager;
    QVBoxLayout *layout;
    QTableWidget *bestTimeTable;
    QTableWidget *bestMovesTable;
    QPushButton* backButton;

public:
    explicit LeaderboardScreen(PlayerManager* playerManager, QWidget *parent = nullptr);
    void fillWithData(int i, QTableWidget* table, int boardSize, QString type);
    void fillCells(QTableWidget* table, int i, QString value, QString name);

signals:
    void goBackToHomeScreen();

private slots:
    void connectPlayersForUpdates();
    void updateLeaderboard();
};

#endif // LEADERBOARDSCREEN_H
