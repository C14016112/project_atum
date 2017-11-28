#ifndef __OPT_ENV_H__
#define __OPT_ENV_H__

#include <iostream>
#include "matrix.h"
#include "abstract_env.h"
#include "abstract_agent.h"

// The optEnv has a hidden target matrix with shape (1, `problem_size`)
// The agent guess a matrix and the OptEnv will provide the mean squared error between the guessing and the answer.
// The agent has to figure out what is the target matrix.
// OptEnv doesn't nedd an "observation", but we still provide a zero matrix as dummy observation for interface alignment.
class OptEnv : public AbstractEnv{
    public:
        explicit OptEnv(uint32_t problem_size);
        double evaluate_agent(const AbstractAgent &agent, bool verbose=false) const override;
        const Matrix& get_target_matrix() const { return m_target_matrix; }
    protected:
        Matrix m_dummy_state;
        Matrix m_target_matrix;
};

#endif
