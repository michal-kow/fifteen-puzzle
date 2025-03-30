#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
// #include <playermanager.h>

class HomeScreen : public QWidget {
    Q_OBJECT

private:
    // PlayerManager* playerManager;
    QVBoxLayout *layout;
    QLabel *playerLabel;
    QComboBox *boardSizeDropdown;
    QPushButton *startButton;
    QPushButton *managePlayersButton;

public:
    // explicit HomeScreen(PlayerManager* playerManager, QWidget *parent = nullptr);
    explicit HomeScreen(QWidget *parent = nullptr);

signals:
    void boardSizeSelected(int boardSize);
    void openPlayerManagement();

private slots:
    void onStartClicked();
};

#endif // HOMESCREEN_H
