#include "2048_env.h"
#include <limits>

Game2048Env::Game2048Env()
{
    m_input_size = 16;
    m_output_size = 1;
}

double Game2048Env::evaluate_agent(const AbstractAgent &agent, bool verbose/*=false*/) const
{
    int score = 0;
    bool is_terminate = false;

    Board2048 board;
    board.init();

    while (is_terminate == false) {
        double best_q_value = std::numeric_limits<double>::lowest();
        int best_move = -1;
        for(int i = 0; i < 4; i++){
            Board2048 copied_board(board);
            int reward = copied_board.move(i);
            if (reward == -1) continue;
            Matrix agent_prediction = agent.evaluate_action(board.get_observation());
            double q_value = static_cast<double>(agent_prediction(0,0)) + reward;
            if (q_value > best_q_value){
                best_q_value = q_value;
                best_move = i;
            }
        }

        if (best_move != -1) {
            score += board.move(best_move);
            board.add_random_tile();
        }
        else{
            is_terminate = true;
        }
    }

    if (verbose){
        int max_tile = 0;
        for(int i = 0; i < 16; ++i) if(board.at(i) > max_tile) max_tile = board.at(i);
        std::cout << "max tile: " << (2<<max_tile) << " , score: " << score << std::endl;
    }

    return static_cast<double>(score);
}
