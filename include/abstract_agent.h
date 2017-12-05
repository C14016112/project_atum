#ifndef __ABSTRACT_AGENT_H__
#define __ABSTRACT_AGENT_H__

#include <string>
#include "matrix.h"
#include "weight.h"

class AbstractAgent {
public:
    AbstractAgent(){};
    virtual ~AbstractAgent(){};

    virtual Matrix evaluate_action(const Matrix &observation) const = 0; // return an action
    virtual void add_weights(const Weights &offsets) = 0;
    inline virtual const Weights& get_weights() const { return m_model_weights; }

    virtual void dump_config(const std::string &filename) const = 0;
    inline virtual void save_agent(const std::string &filename="model.bin") const{
        m_model_weights.save(filename);
    }
    inline virtual void load_agent(const std::string &filename="model.bin"){
        m_model_weights.load(filename);
    }

protected:
    Weights m_model_weights;
};

#endif
