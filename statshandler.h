#ifndef STATSHANDLER_H
#define STATSHANDLER_H
#include <QObject>
#include <QTimer>

class StatsHandler : public QObject {
    Q_OBJECT

private:
    QTimer *timer;
    int moveCount;
    int elapsedSeconds;

public:
    explicit StatsHandler(QObject *parent = nullptr);

    void startTimer();
    void stopTimer();
    int getElapsedTime();
    int getMoveCount();
    void increaseMoveCount();
    void resetStats();

signals:
    void movesUpdated(int moves, int timeElapsed);
    void timeUpdated(int timeElapsed);

private slots:
    void updateElapsedTime();
};

#endif // STATSHANDLER_H
