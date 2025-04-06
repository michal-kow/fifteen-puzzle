#ifndef AIALGORITHM_H
#define AIALGORITHM_H

#include "puzzlemodel.h"

#include <QObject>

class AIAlgorithm : public QObject
{
    Q_OBJECT

public:
    explicit AIAlgorithm(QObject *parent = nullptr);
    virtual int chooseMove(PuzzleModel& model) = 0;
};

#endif // AIALGORITHM_H
