#ifndef __ABSTRACT_ENV_H__
#define __ABSTRACT_ENV_H__

// #include <armadillo>
// #include <iostream>
#include "agent.h"

// using namespace arma;

class AbstractEnv{
	protected:
		uint problem_size;

	public:
		AbstractEnv(){};
		virtual ~AbstractEnv(){};
		// virtual double evaluate(mat input_matrix) = 0;
		virtual double evaluate_agent(Agent &ai) = 0;
		
};

#endif