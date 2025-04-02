#include "screenmanager.h"

ScreenManager::ScreenManager(QStackedWidget* _stackedWidget, PlayerManager* playerManager, QObject* parent)
    : QObject(parent), stackedWidget(_stackedWidget) {

    homeScreen = new HomeScreen(playerManager);
    playerManagerScreen = new PlayerManagerScreen(playerManager);
    puzzleModel = new PuzzleModel();
    puzzleScreen = new PuzzleScreen(puzzleModel);
    leaderboardScreen = new LeaderboardScreen(playerManager);

    stackedWidget->addWidget(homeScreen);
    stackedWidget->addWidget(playerManagerScreen);
    stackedWidget->addWidget(puzzleScreen);
    stackedWidget->addWidget(leaderboardScreen);

    connect(puzzleScreen, &PuzzleScreen::goBackToHomeScreen, this, &ScreenManager::showHomeScreen);
    connect(playerManagerScreen, &PlayerManagerScreen::goBackToHomeScreen, this, &ScreenManager::showHomeScreen);
    connect(homeScreen, &HomeScreen::boardSizeSelected, this, &ScreenManager::showPuzzleScreen);
    connect(homeScreen, &HomeScreen::openPlayerManagement, this, &ScreenManager::showPlayerManagementScreen);
    connect(puzzleScreen, &PuzzleScreen::puzzleCompleted, playerManager, &PlayerManager::updatePlayerStats);
    connect(homeScreen, &HomeScreen::openLeaderboard, this, &ScreenManager::showLeaderboardScreen);
    connect(leaderboardScreen, &LeaderboardScreen::goBackToHomeScreen, this, &ScreenManager::showHomeScreen);
}

void ScreenManager::showHomeScreen() {
    stackedWidget->setCurrentWidget(homeScreen);
}

void ScreenManager::showPlayerManagementScreen() {
    stackedWidget->setCurrentWidget(playerManagerScreen);
}

void ScreenManager::showPuzzleScreen(int boardSize) {
    puzzleModel->createNewPuzzle(boardSize);
    puzzleScreen->displayPuzzle();
    stackedWidget->setCurrentWidget(puzzleScreen);
}

void ScreenManager::showLeaderboardScreen() {
    stackedWidget->setCurrentWidget(leaderboardScreen);
}
