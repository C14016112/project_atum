#include "opt_env.h"

OptEnv::OptEnv(uint32_t output_size)
:m_dummy_state(arma::zeros<Matrix>(1, output_size))
{
    m_input_size = output_size;
    m_output_size = output_size;
}

double OptEnv::evaluate_agent(const AbstractAgent &agent, bool verbose/*=false*/) const
{
    Matrix x = agent.evaluate_action(m_dummy_state);
    Matrix prediction = get_function_output(x);
    if (verbose) {
        std::cout << "Agent output x : " << x;
        std::cout << "Optimal x : " << get_critical_point();
        std::cout << "f(x) : " << prediction(0,0) << std::endl;
        std::cout << "Minimun f(x): " << get_function_minimum() << std::endl;
    }
    return -prediction(0,0);
}
