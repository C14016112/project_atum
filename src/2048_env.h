#ifndef __2048_ENV_H__
#define __2048_ENV_H__

#include "matrix.h"
#include "abstract_agent.h"
#include "abstract_env.h"
#include "2048_board.h"

class Game2048Env : public AbstractEnv{
public:
    Game2048Env();
    double evaluate_agent(const AbstractAgent &agent, bool verbose=false) const override;

};

#endif
