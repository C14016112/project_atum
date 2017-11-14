#ifndef __OPT_ENV_H__
#define __OPT_ENV_H__

#include <armadillo>
#include <iostream>
#include "abstract_env.h"
#include "agent.h"

using namespace arma;

class OptEnv : public AbstractEnv{
	private:
		// mat problem_weight;
		uint m_problem_size;

	public:
		double evaluate(mat input_matrix);
		OptEnv(uint problme_size);
		~OptEnv();
		double evaluate_agent(Agent *ai);

};

#endif