#include "2048_env.h"

game_2048_env::game_2048_env(){
	__asm__ __volatile__("rdtsc" : "=a" (seed));
	std::srand(seed);
	game_2048_env::problem_size = 16;
}

game_2048_env::~game_2048_env(){
	
}

double game_2048_env::evaluate_agent(agent *ai){
	// play an episode
	int score = 0;
	b.init();

	while (true) {
		// try to find a best move
		state current_state(b);

		
		//current_state.PrintState();
		double best_val = -10000000;
		int best_move = 0;
		for(int i = 1; i < 4; i++){
			state tmp_state = current_state;
			int reward = tmp_state.move(i);
			if (reward == -1) continue;
			mat A = zeros(16);
			for(int j = 0; j < 16; j++) A(j) = tmp_state.get_board().at(j);
			double val = (double)ai->predict(A.t())(0) + reward;
			if (val > best_val){
				best_val = val;
				best_move = i;
			}
		}

		state best_next_state = current_state;
		best_next_state.move(best_move);

		if (best_next_state.get_reward() != -1) {
			b = best_next_state.get_board();
			score += best_next_state.get_reward();
			b.add_random_tile();
		}
		// game over
		else 
			break;
	}
	return (double)score;
}
	
