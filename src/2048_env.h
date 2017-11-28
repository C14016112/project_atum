#ifndef __2048_ENV_H__
#define __2048_ENV_H__

#include "matrix.h"
#include "abstract_agent.h"
#include "abstract_env.h"
#include "2048_board.h"

class Game2048Env : public AbstractEnv{
public:
    Game2048Env();
    ~Game2048Env();
    double evaluate_agent(AbstractAgent& agent);
    double evaluate(Matrix input){return 0;}
    inline Board get_board(){return m_board;}


    // copy_env() // constructor
    inline void reset_env(){m_board.init();}
    inline uint get_input_size(){return m_input_size;}
    inline uint get_output_size(){return m_output_size;}
    Matrix get_observation();
    void do_action(Matrix action);


private:
    unsigned int m_seed;
    Board m_board;
    uint m_input_size;
    uint m_output_size;

};

#endif
