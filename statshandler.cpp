#include "statshandler.h"

StatsHandler::StatsHandler(QObject *parent) : QObject(parent), moveCount(0), elapsedSeconds(0) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &StatsHandler::updateElapsedTime);
}

void StatsHandler::startTimer() {
    elapsedSeconds = 0;
    timer->start(1000);
}

void StatsHandler::stopTimer() {
    timer->stop();
}

void StatsHandler::resetStats() {
    moveCount = 0;
    elapsedSeconds = 0;
    timer->stop();
    emit movesUpdated(moveCount, elapsedSeconds);
    emit timeUpdated(elapsedSeconds);
}

void StatsHandler::increaseMoveCount() {
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
    elapsedSeconds++;
    emit timeUpdated(elapsedSeconds);
}
