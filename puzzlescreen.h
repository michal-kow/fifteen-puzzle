#ifndef PUZZLESCREEN_H
#define PUZZLESCREEN_H
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLabel>

#include <puzzlemodel.h>
#include <statshandler.h>
#include <playermanager.h>
#include <aialgorithm.h>

class PuzzleScreen : public QWidget {
    Q_OBJECT

private:
    PuzzleModel *PuzzleModel;
    PlayerManager *playerManager;
    QVBoxLayout* mainLayout;
    QGridLayout *boardLayout;
    QHBoxLayout* statsLayout;
    StatsHandler *statsHandler;
    QLabel *movesLabel;
    QLabel *timerLabel;
    QVector<QVector<QPushButton*>> buttons;
    QTimer* aiMoveTimer;
    AIAlgorithm* aiAlgorithm = nullptr;

public:
    explicit PuzzleScreen(class PuzzleModel *model, PlayerManager* playerManager, QWidget *parent = nullptr);
    void displayPuzzle(QString algorithm);
    void updateView();

signals:
    void goBackToHomeScreen();
    void puzzleCompleted(int moves, int time, int boardSize);
    void callAIMove();

private slots:
    void handleButtonClick();
    void checkIfSolved();
    void updateMovesDisplay(int moves);
    void updateTimeDisplay(int timeElapsed);
    void makeAIMove();
};

#endif // PUZZLESCREEN_H
