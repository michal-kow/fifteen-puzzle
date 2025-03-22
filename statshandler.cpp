#include "statshandler.h"

#include <iostream>
using namespace std;

StatsHandler::StatsHandler(QObject *parent) : QObject(parent), moveCount(0), elapsedSeconds(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StatsHandler::updateElapsedTime);
}

void StatsHandler::startTimer() {
    cout << "Starting timer..." << endl;
    elapsedSeconds = 0;
    timer->start(1000);
}

void StatsHandler::stopTimer() {
    cout << "Stopped timer" << endl;
    timer->stop();
}

void StatsHandler::resetStats() {
    cout << "Resetting stats..." << endl;
    moveCount = 0;
    elapsedSeconds = 0;
    timer->stop();
    emit movesUpdated(moveCount, elapsedSeconds);
    emit timeUpdated(elapsedSeconds);
}

void StatsHandler::increaseMoveCount() {
    cout << "increaseMoveCount()" << endl;
    moveCount++;
    emit movesUpdated(moveCount, elapsedSeconds);
}

int StatsHandler::getMoveCount() {
    return moveCount;
}

int StatsHandler::getElapsedTime() {
    return elapsedSeconds;
}

void StatsHandler::updateElapsedTime() {
    cout << "updateElapsedTime()" << endl;
    elapsedSeconds++;
    emit timeUpdated(elapsedSeconds);
}
