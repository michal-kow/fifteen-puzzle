#ifndef RANDOMAIALGORITHM_H
#define RANDOMAIALGORITHM_H

#include "aialgorithm.h"

class RandomAIAlgorithm : public AIAlgorithm
{
public:
    explicit RandomAIAlgorithm(QObject *parent = nullptr);
    int chooseMove(PuzzleModel& model) override;
};

#endif // RANDOMAIALGORITHM_H
