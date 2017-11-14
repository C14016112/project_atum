#ifndef __ES_H__
#define __ES_H__

#include <armadillo>
#include "agent.h"
// #include "opt_env.h"
#include "abstract_env.h"
#include "2048_env.h"
// #include "2048.h"

using namespace arma;

class es{
public:
	es(uint thread_num, uint pop_num, double param_sigma, double param_alpha);
	~es();
	void train(Abstract_env & problem, agent * AI, uint iteration);
	void write_log(int iteration, double average_reward);


private:
	uint thread_number;
	uint population_number;
	double sigma;
	double alpha;
	double start_time;
	FILE * csv_log_file;
};
#endif