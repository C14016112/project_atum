#include <fstream>
#include <sstream>
#include "dnn_agent.h"
#include "abstract_env.h"

DnnAgent::DnnAgent(const vector<int> &model_wid) {
    m_model_weights = Weights(model_wid, Weights::GAUSSIAN);
}

DnnAgent::DnnAgent(const DnnAgent& agent) {
    m_model_weights = Weights(agent.m_model_weights);
}

DnnAgent::~DnnAgent() {}

Matrix DnnAgent::evaluate_action(const Matrix &observation)
{
    Matrix result = observation;
    for(int i = 0; i < m_model_weights.get_count()-1; i+=2) {
        result = result*m_model_weights[i] + m_model_weights[i+1];
        if(i != m_model_weights.get_count()-2)
            result = relu(result);
    }
    return result;
}

DnnAgent& DnnAgent::operator=(const DnnAgent &agent) {
    m_model_weights = Weights(agent.m_model_weights);
    return *this;
}

void DnnAgent::copy_agent(DnnAgent *new_agent) {
    *new_agent = DnnAgent(*this);
}

void DnnAgent::add_weights(const Weights &offsets) {
    m_model_weights += offsets;
}

void DnnAgent::dump_config(const std::string &filename) const {
    dump_config_layer_(filename);
}

void DnnAgent::dump_config_layer_(const std::string &filename) const
{
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

void DnnAgent::load_config_layer_(const std::string &filename,
                                  std::vector<int> &layers)
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

Matrix DnnAgent::relu(Matrix matrix) {
    Matrix relu_mat = matrix;
    for(int i = 0; i < relu_mat.size(); i++) {
        if(matrix(i) < 0) relu_mat(i) = 0;
    }
    return relu_mat;
}
