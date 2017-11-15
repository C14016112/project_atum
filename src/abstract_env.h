#ifndef __ABSTRACT_ENV_H__
#define __ABSTRACT_ENV_H__

#include "agent.h"

class AbstractEnv{
	protected:
		uint problem_size;

	public:
		AbstractEnv(){};
		virtual ~AbstractEnv(){};
		virtual double evaluate_agent(Agent &ai) = 0;
		
};

#endif