#ifndef __EVOLUTION_STRATEGY_H__
#define __EVOLUTION_STRATEGY_H__

#include "matrix.h"
#include "dnn_agent.h"
#include "abstract_env.h"
#include "2048_env.h"
#include "weight.h"

class EvolutionStrategy{
public:
    EvolutionStrategy(uint thread_num, uint pop_num, double param_sigma, double param_alpha);
    ~EvolutionStrategy();
    void train(AbstractEnv & problem, DnnAgent* ai, uint iteration);
    void write_log(int iteration, double average_reward);


private:
    uint m_thread_number;
    uint m_population_number;
    double m_sigma;
    double m_alpha;
    double m_start_time;
    FILE * m_csv_log_file;
    vector<double> utility_table;

    void create_utility_table();
    vector<std::pair<int, double>> sort_id_reward_vector( vector<std::pair<int,double>> );
};
#endif
