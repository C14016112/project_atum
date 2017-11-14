#ifndef __2048_ENV_H__
#define __2048_ENV_H__

#include <armadillo>
#include "agent.h"
#include "abstract_env.h"
#include "2048_board.h"

class game_2048_env : public Abstract_env{
public:
	game_2048_env();
	~game_2048_env();
	double evaluate_agent(agent *AI);
	double evaluate(mat input){return 0;};
	inline board get_board(){return b;};
private:
	unsigned int seed;
	board b;
	uint problem_size;
	
};

#endif