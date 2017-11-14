#ifndef __OPT_ENV_H__
#define __OPT_ENV_H__

#include <armadillo>
#include <iostream>
#include "abstract_env.h"
#include "agent.h"

using namespace arma;

class opt_env : public Abstract_env{
	private:
		// mat problem_weight;
		uint problem_size;

	public:
		double evaluate(mat input_matrix);
		opt_env(uint problme_size);
		~opt_env();
		double evaluate_agent(agent *ai);

};

#endif