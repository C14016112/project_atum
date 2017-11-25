#ifndef __AGENT_H__
#define __AGENT_H__

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "matrix.h"
#include "weight.h"
#include "abstract_agent.h"

class Agent : public AbstractAgent{
public:
    //Agent(const AbstractEnv &env, const std::string &filename);
    Agent(const std::vector<int> &model_wid);
    Agent(const Agent& agent);
    Agent();
    ~Agent();

    Agent& operator=(const Agent &);
    void copy_agent(Agent *new_agent);
    void build_model();
    Matrix predict(const Matrix input_matrix);    // same as evaluate_action?
    virtual Matrix evaluate_action(const Matrix &observation);

    virtual void add_weights(const Weights &offsets);

    virtual void dump_config(const std::string &filename) const;
    Matrix relu(Matrix);    // TODO: might need to pull into other module

    // void save_agent(const std::string &filename);
    // void load_agent(const std::string &filename);

    inline const Weights& get_model_weights() const {return m_model_weights;}
private:
    void load_config_layer_(const std::string &filename, std::vector<int> &layers);
    void dump_config_layer_(const std::string &filename) const;
};

#endif
