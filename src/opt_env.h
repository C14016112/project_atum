#ifndef __OPT_ENV_H__
#define __OPT_ENV_H__

#include <iostream>
#include "matrix.h"
#include "abstract_env.h"
#include "abstract_agent.h"

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
