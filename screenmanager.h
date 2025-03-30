#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <QStackedWidget>
#include "homescreen.h"
#include "puzzlescreen.h"

class ScreenManager : public QObject {
    Q_OBJECT

private:
    QStackedWidget* stackedWidget;
    PuzzleModel* puzzleModel;
    HomeScreen* homeScreen;
    // PlayerManagementScreen* playerManagerScreen;
    PuzzleScreen* puzzleScreen;

public:
    // explicit ScreenManager(QStackedWidget* stackedWidget, PlayerManager* playerManager, QObject* parent = nullptr);
    explicit ScreenManager(QStackedWidget* stackedWidget, QObject* parent = nullptr);

    void showHomeScreen();
    void showPlayerManagementScreen();
    void showPuzzleScreen(int boardSize);
};

#endif // SCREENMANAGER_H
