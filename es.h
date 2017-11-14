#ifndef __ES_H__
#define __ES_H__

#include <armadillo>
#include "agent.h"
// #include "opt_env.h"
#include "abstract_env.h"
#include "2048_env.h"
// #include "2048.h"

using namespace arma;

class Es{
public:
	Es(uint thread_num, uint pop_num, double param_sigma, double param_alpha);
	~Es();
	void train(AbstractEnv & problem, Agent * AI, uint iteration);
	void write_log(int iteration, double average_reward);


private:
	uint m_thread_number;
	uint m_population_number;
	double m_sigma;
	double m_alpha;
	double m_start_time;
	FILE * m_csv_log_file;
};
#endif