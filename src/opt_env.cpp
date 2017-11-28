#include "opt_env.h"

OptEnv::OptEnv(uint32_t output_size)
{
    m_input_size = output_size;
    m_output_size = output_size;
    m_dummy_state = arma::zeros<Matrix>(1, m_output_size);
    m_target_matrix = arma::randu<Matrix>(1, m_output_size);
}

double OptEnv::evaluate_agent(const AbstractAgent &agent, bool verbose/*=false*/) const
{
    Matrix diff = agent.evaluate_action(m_dummy_state) - m_target_matrix;
    Matrix loss = diff * diff.t();
    if (verbose) { std::cout << "L2 Norm : " << -loss(0,0) << std::endl; }
    return -loss(0,0);
}
