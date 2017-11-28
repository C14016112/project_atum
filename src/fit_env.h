#ifndef __FIT_ENV_H__
#define __FIT_ENV_H__

#include "matrix.h"
#include "abstract_env.h"

// FitEnv has a black box function f(x) and agent represents another function g(x)
// Sample `batch_size` points and fit these points to f(x) and g(x) respectively.
// The FitEnv will provide the summation of |f(x) - g(x)| for all samples and the agent has to find out what's the black box function f(x) is.
class FitEnv : public AbstractEnv{
    public:
        explicit FitEnv(uint32_t batch_size, uint32_t input_size=2);
        double evaluate_agent(const AbstractAgent &agent, bool verbose=false) const override;
        static inline Matrix get_function_output(const Matrix &input) { return 0.5 * arma::sum(arma::pow(input,4) - 16* arma::pow(input,2) + 5*input, 1); }
    protected:
        uint32_t m_batch_size;
};
#endif
