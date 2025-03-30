#include "screenmanager.h"

// ScreenManager::ScreenManager(QStackedWidget* _stackedWidget, PlayerManager* playerManager, QObject* parent)
ScreenManager::ScreenManager(QStackedWidget* _stackedWidget, QObject* parent)
    : QObject(parent), stackedWidget(_stackedWidget) {

    // homeScreen = new HomeScreen(playerManager);
    homeScreen = new HomeScreen();
    // playerManagerScreen = new PlayerManagerScreen(playerManager);
    puzzleModel = new PuzzleModel();
    puzzleScreen = new PuzzleScreen(puzzleModel);

    stackedWidget->addWidget(homeScreen);
    // stackedWidget->addWidget(playerScreen);
    stackedWidget->addWidget(puzzleScreen);

    connect(puzzleScreen, &PuzzleScreen::goBackToHomeScreen, this, &ScreenManager::showHomeScreen);
    connect(homeScreen, &HomeScreen::boardSizeSelected, this, &ScreenManager::showPuzzleScreen);
    connect(homeScreen, &HomeScreen::openPlayerManagement, this, &ScreenManager::showPlayerManagementScreen);
}

void ScreenManager::showHomeScreen() {
    stackedWidget->setCurrentWidget(homeScreen);
}

void ScreenManager::showPlayerManagementScreen() {
    // stackedWidget->setCurrentWidget(playerManagementScreen);
}

void ScreenManager::showPuzzleScreen(int boardSize) {
    puzzleModel->createNewPuzzle(boardSize);
    puzzleScreen->displayPuzzle();
    stackedWidget->setCurrentWidget(puzzleScreen);
}
