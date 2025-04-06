#ifndef GREEDYAIALGORITHM_H
#define GREEDYAIALGORITHM_H

#include "aialgorithm.h"

class GreedyAIAlgorithm : public AIAlgorithm
{
public:
    explicit GreedyAIAlgorithm(QObject *parent = nullptr);
    int chooseMove(PuzzleModel& model) override;
};

#endif // GREEDYAIALGORITHM_H
