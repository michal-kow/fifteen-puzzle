#ifndef PUZZLESCREEN_H
#define PUZZLESCREEN_H
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLabel>

#include <puzzlemodel.h>
#include <statshandler.h>


class PuzzleScreen : public QWidget {
    Q_OBJECT

private:
    PuzzleModel *PuzzleModel;
    QGridLayout *gridLayout;
    StatsHandler *statsHandler;
    QLabel *statsLabel;
    QLabel *timerLabel;
    QVector<QVector<QPushButton*>> buttons;

public:
    explicit PuzzleScreen(class PuzzleModel *model, QWidget *parent = nullptr);
    void displayPuzzle();
    void updateView();

signals:
    void goBackToHomeScreen();
    void puzzleCompleted(int moves, int time, int boardSize);

private slots:
    void handleButtonClick();
    void checkIfSolved();
    void updateMovesDisplay(int moves);
    void updateTimeDisplay(int timeElapsed);
};

#endif // PUZZLESCREEN_H
