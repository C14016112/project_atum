#ifndef __ABSTRACT_ENV_H__
#define __ABSTRACT_ENV_H__

// #include <armadillo>
// #include <iostream>
#include "agent.h"

// using namespace arma;

class Abstract_env{
	protected:
		uint problem_size;

	public:
		Abstract_env(){};
		virtual ~Abstract_env(){};
		// virtual double evaluate(mat input_matrix) = 0;
		virtual double evaluate_agent(agent *ai) = 0;
		
};

#endif