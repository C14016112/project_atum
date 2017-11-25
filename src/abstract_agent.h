#ifndef __ABSTRACT_AGENT_H__
#define __ABSTRACT_AGENT_H__

#include <string>
#include <fstream>
#include "matrix.h"
#include "agent.h"
#include "weight.h"

class AbstractAgent {
public:
    //AbstractAgent(const AbstractEnv &env, const std::string &filename);
    AbstractAgent(){};
    virtual ~AbstractAgent(){};
    // void copy_agent(AbstractAgent *new_agent);

    virtual Matrix evaluate_action(const Matrix &observation) = 0; // return an action
    virtual void add_weights(const Weights &offsets) = 0;
    virtual const Weights& get_weights() const {
        return m_model_weights;
    }

    virtual void dump_config(const std::string &filename) const = 0;
    void save_agent(const std::string &filename="model.bin") {
        std::ofstream ofs;
        ofs.open(filename, std::ofstream::out);
        if (ofs.is_open()) {
            for(int i = 0; i < m_model_weights.get_count(); ++i)
                m_model_weights[i].save(ofs);
            ofs.close();
        }
        else {
            std::cout << "[ERROR] Failed to open " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    void load_agent(const std::string &filename="model.bin") {
        std::ifstream ifs;
        ifs.open(filename, std::ifstream::in);
        if (ifs.is_open()) {
            for (int i = 0; i < m_model_weights.get_count() - 1; ++i)
                m_model_weights[i].load(ifs);
            ifs.close();
        }
        else {
            std::cout << "[ERROR] Failed to open " << filename << std::endl;
            exit(EXIT_FAILURE);
        }
    }

protected:
    Weights m_model_weights;
};

#endif
