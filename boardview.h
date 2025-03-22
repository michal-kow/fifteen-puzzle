#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLabel>

#include <boardmodel.h>
#include <statshandler.h>


class BoardView : public QWidget {
    Q_OBJECT

private:
    BoardModel *boardModel;
    QGridLayout *gridLayout;
    StatsHandler *statsHandler;
    QLabel *statsLabel;
    QLabel *timerLabel;
    QVector<QVector<QPushButton*>> buttons;

public:
    explicit BoardView(BoardModel *model, QWidget *parent = nullptr);
    void updateView();

signals:
    void backToLandingPage();

private slots:
    void handleButtonClick();
    void checkIfSolved();
    void updateMovesDisplay(int moves);
    void updateTimeDisplay(int timeElapsed);
};

#endif // BOARDVIEW_H
