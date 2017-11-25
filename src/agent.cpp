#include "agent.h"

// Precisely, DNN-Agent

Agent::Agent(const vector<int> &model_wid)
{
    m_model_weights = Weights(model_wid, GAUSSIAN);
}

Agent::Agent(const Agent& agent)
{
    m_model_weights = Weights(agent.m_model_weights);
}

Agent::~Agent(){
}

Matrix Agent::predict(Matrix input_matrix){
    Matrix result = input_matrix;
    for(int i = 0; i < m_model_weights.get_count()-1; i+=2){
        result = result*m_model_weights[i] + m_model_weights[i+1];
        if(i != m_model_weights.get_count()-2)
            result = relu(result);
    }
    return result;
}

Matrix Agent::relu(Matrix matrix){
    Matrix relu_mat = matrix;
    for(int i = 0; i < relu_mat.size(); i++){
        if(matrix(i) < 0) relu_mat(i) = 0;
    }
    return relu_mat;
}

void Agent::copy_agent(Agent *new_agent){
    *new_agent = Agent(*this);
}

void Agent::add_model_weights(Weights& added_model_weights){
    m_model_weights += added_model_weights;
}

void Agent::save_agent(){
    std::ofstream ofs;
    ofs.open ("model.bin", std::ofstream::out);
    if(ofs.is_open()){
        for(int i = 0; i < m_model_weights.get_count(); i++){
            m_model_weights[i].save(ofs);
        }
        ofs.close();
    }
    else{
        std::cout << "[ERROR] Failed to open model.bin.\n";
        exit(EXIT_FAILURE);
    }
}

void Agent::load_agent(){
    std::ifstream ifs;
    ifs.open("model.bin", std::ifstream::in);
    if(ifs.is_open()){
        for(int i = 0; i < m_model_weights.get_count() - 1; i++){
            m_model_weights[i].load(ifs);
        }
        ifs.close();
    }
    else{
        std::cout << "[ERROR] Failed to open model.bin.\n";
        exit(EXIT_FAILURE);
    }
}
