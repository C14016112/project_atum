#ifndef __ABSTRACT_ENV_H__
#define __ABSTRACT_ENV_H__

#include "abstract_agent.h"

class AbstractEnv{
    protected:
        uint problem_size;

    public:
        AbstractEnv(){};
        virtual ~AbstractEnv(){};
        virtual double evaluate_agent(AbstractAgent &ai) = 0;
        uint32_t get_input_size() const;
        uint32_t get_output_size() const;
};

#endif
