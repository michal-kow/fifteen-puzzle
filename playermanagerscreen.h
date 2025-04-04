#ifndef PLAYERMANAGERSCREEN_H
#define PLAYERMANAGERSCREEN_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>

#include <playermanager.h>

class PlayerManagerScreen : public QWidget
{
    Q_OBJECT

private:
    PlayerManager* playerManager;
    QListWidget* playerList;
    QLineEdit* newPlayerInput;
    QPushButton* addPlayerButton;
    QPushButton* setAsCurrentPlayerButton;
    QPushButton* deletePlayerButton;
    QPushButton* backButton;
    void updatePlayerList();

public:
    explicit PlayerManagerScreen(PlayerManager* playerManager, QWidget *parent = nullptr);

signals:
    void playerSelected(QString playerName);
    void goBackToHomeScreen();

private slots:
    void addPlayer();
    void selectPlayer();
    void deletePlayer();
    void onBackButtonClicked();
};

#endif // PLAYERMANAGERSCREEN_H
