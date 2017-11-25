#include <fstream>
#include <sstream>
#include "agent.h"
#include "abstract_env.h"

// Precisely, DNN-Agent

/*
Agent::Agent(const AbstractEnv &env, const std::string &filename) {
    // load file for config
    uint32_t in_dim, out_dim;
    std::vector<int> model_wid;
    in_dim = env.get_input_size();
    in_dim = env.get_output_size();

    // read config
    load_config_layer_(filename, model_wid);
    m_model_weights = Weights(model_wid, GAUSSIAN);
}
*/

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

Matrix Agent::predict(const Matrix input_matrix){
    Matrix result = input_matrix;
    for(int i = 0; i < m_model_weights.get_count()-1; i+=2){
        result = result*m_model_weights[i] + m_model_weights[i+1];
        if(i != m_model_weights.get_count()-2)
            result = relu(result);
    }
    return result;
}
Matrix Agent::evaluate_action(const Matrix &observation){
    Matrix result = observation;
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

Agent& Agent::operator=(const Agent &agent) {
    m_model_weights = Weights(agent.m_model_weights);
    return *this;
}

void Agent::copy_agent(Agent *new_agent){
    *new_agent = Agent(*this);
}

void Agent::add_weights(const Weights &offsets){
    m_model_weights += offsets;
}

void Agent::dump_config(const std::string &filename) const{
    dump_config_layer_(filename);
}

void Agent::dump_config_layer_(const std::string &filename) const{
    std::vector<int> layers;
    // determine width of each layer
    for (int i = 0; i < m_model_weights.get_count()-3; i+=2) {
        // 3 because we don't need last weight shape info
        layers.push_back(m_model_weights[i].n_cols);
    }
    std::ofstream ofs(filename, std::ofstream::out);
    ofs << "model : ";
    for (auto &s: layers)  ofs << s << " ";
    ofs << "\n";

    // dump input/output size
    ofs << "input_size : "
        << m_model_weights[0].n_rows << "\n"
        << "output_size : "
        << m_model_weights[m_model_weights.get_count() - 2].n_cols << "\n";
}
/*
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
*/

void Agent::load_config_layer_(const std::string &filename, std::vector<int> &layers)
{
    // read config
    std::ifstream fin(filename);
    std::string line, cfg_name;
    while (std::getline(fin, line))
    {
        cfg_name = line.substr(0, line.find(" "));
        if (cfg_name.compare("model") == 0)
        {
            std::string data = line.substr(line.find_first_not_of(":"));
            // if(data[0] == ' ')   data = data.substr(1);
            std::istringstream iss(data);
            int w;
            while (iss >> w) layers.push_back(w);
            break;
        }
    }
}
