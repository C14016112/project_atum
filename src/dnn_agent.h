#ifndef __DnnA_GENT_H__
#define __DnnA_GENT_H__

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "matrix.h"
#include "weight.h"
#include "abstract_agent.h"

class DnnAgent : public AbstractAgent{
public:
    DnnAgent(const std::vector<int> &model_wid);
    DnnAgent(const DnnAgent& agent);
    DnnAgent();
    ~DnnAgent();

    DnnAgent& operator=(const DnnAgent &);
    virtual void copy_agent(DnnAgent *new_agent);
    void build_model();
    virtual Matrix evaluate_action(const Matrix &observation);

    virtual void add_weights(const Weights &offsets);

    virtual void dump_config(const std::string &filename) const;
    Matrix relu(Matrix);

private:
    void load_config_layer_(const std::string &filename, std::vector<int> &layers);
    void dump_config_layer_(const std::string &filename) const;
};

#endif
