#ifndef __OPT_ENV_H__
#define __OPT_ENV_H__

#include <iostream>
#include "matrix.h"
#include "abstract_env.h"
#include "abstract_agent.h"
#include "math_functions.h"

// OptEnv has a black box function f(x) and the agent has to find the correct x that leads to the minimal f(x).
// For each x output from the agant, optEnv will provide the f(x) as a hint.
// OptEnv doesn't need an "observation", but we still provide a ones matrix as dummy observation for interface alignment.
class OptEnv : public AbstractEnv{
    public:
        explicit OptEnv(uint32_t problem_size);
        double evaluate_agent(const AbstractAgent &agent, bool verbose=false) const override;
        static inline Matrix get_function_output(const Matrix &input) { return function::rastrigin(input); }
        inline Matrix get_critical_point() const { return function::rastrigin_critical_point(m_input_size); }
        inline double get_function_minimum() const { return function::rastrigin_minimum(m_input_size); }

    protected:
        const Matrix m_dummy_state;
};

#endif
