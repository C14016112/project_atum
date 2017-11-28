#ifndef __FIT_ENV_H__
#define __FIT_ENV_H__

#include "matrix.h"
#include "abstract_env.h"

class FitEnv : public AbstractEnv{
    public:
        explicit FitEnv(uint32_t batch_size, uint32_t input_size=2);
        double evaluate_agent(const AbstractAgent &agent, bool verbose=false) const override;
        static inline Matrix get_function_output(const Matrix &input) { return 0.5 * arma::sum(arma::pow(input,4) - 16* arma::pow(input,2) + 5*input, 1); }
    protected:
        uint32_t m_batch_size;
};
#endif
