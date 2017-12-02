#include "fit_env.h"

FitEnv::FitEnv(uint32_t batch_size, uint32_t input_size/*=2*/)
:m_batch_size(batch_size)
{
    m_input_size = input_size;
    m_output_size = 1;
}

double FitEnv::evaluate_agent(const AbstractAgent &agent, bool verbose/*=false*/) const
{
    Matrix inputs = -5+10*arma::randu<Matrix>(m_batch_size, m_input_size);
    Matrix answers = FitEnv::get_function_output(inputs);
    Matrix predictions = agent.evaluate_action(inputs);
    Matrix diff = arma::abs(answers - predictions);
    return -arma::accu(diff)/m_batch_size;
}