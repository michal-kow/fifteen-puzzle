#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <playermanager.h>

class HomeScreen : public QWidget {
    Q_OBJECT

private:
    PlayerManager* playerManager;
    QVBoxLayout *layout;
    QLabel *playerLabel;
    QComboBox *boardSizeDropdown;
    QComboBox *algorithmDropdown;
    QPushButton *startButton;
    QPushButton *managePlayersButton;
    QPushButton *leaderboardButton;

public:
    explicit HomeScreen(PlayerManager* playerManager, QWidget *parent = nullptr);

signals:
    void boardSizeSelected(int boardSize);
    void openPlayerManagement();
    void openLeaderboard();

private slots:
    void onStartClicked();
    void updateCurrentPlayer(QString playerName, bool isAI);
};

#endif // HOMESCREEN_H
