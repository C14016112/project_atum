#ifndef __2048_ENV_H__
#define __2048_ENV_H__

#include <armadillo>
#include "agent.h"
#include "abstract_env.h"
#include "2048_board.h"

class Game2048Env : public AbstractEnv{
public:
	Game2048Env();
	~Game2048Env();
	double evaluate_agent(Agent *ai);
	double evaluate(mat input){return 0;};
	inline Board get_board(){return m_b;};
private:
	unsigned int m_seed;
	Board m_b;
	uint m_problem_size;
	
};

#endif