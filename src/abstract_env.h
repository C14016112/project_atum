#ifndef __ABSTRACT_ENV_H__
#define __ABSTRACT_ENV_H__

#include <cstdint>
#include "abstract_agent.h"

class AbstractEnv{
    protected:
        uint32_t m_input_size;
        uint32_t m_output_size;

    public:
        AbstractEnv():m_input_size(0), m_output_size(0) {};
        virtual ~AbstractEnv(){};
        virtual double evaluate_agent(const AbstractAgent &agent, bool verbose=false) const = 0;

        inline uint32_t get_input_size() const { return m_input_size; }
        inline uint32_t get_output_size() const { return m_output_size; }
};

#endif
