#ifndef __ABSTRACT_AGENT_H__
#define __ABSTRACT_AGENT_H__

#include <string>
#include "matrix.h"
#include "weight.h"
#include "abstract_env.h"

class AbstractAgent {
public:
    AbstractAgent(const AbstractEnv &env, const std::string &filename);
    const AbstractAgent &operator=(const AbstractAgent &);
    Matrix evaluate_action(const Matrix &observation) const; // return an action

    void add_weights(const Weight &offsets);
    const Weights& get_weights() const;

    virtual void dump_config(const std::string &filename) const;
    virtual void save_agent(const std::string &filename);
    virtual void load_agent(const std::string &filename);
}

#endif
