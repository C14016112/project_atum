#include "weight.h"
#include <fstream>
#include <string>

Weights::Weights(const Weights& weights, Weights::InitType type)
{
    if (type == COPY){
        for(int i = 0; i < weights.get_count(); i++){
            m_weights_vector.push_back( Matrix(weights.m_weights_vector[i]) );
        }
    }
    else if (type == ZEROS){
        for(int i = 0; i < weights.get_count(); i++){
            m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::zeros) );
        }
    }
    else if(type == ONES){
        for(int i = 0; i < weights.get_count(); i++){
            m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::ones) );
        }
    }
    else if(type == GAUSSIAN){
        for(int i = 0; i < weights.get_count(); i++){
            m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::randn) );
        }
    }
    else if(type == UNIFORM){
        for(int i = 0; i < weights.get_count(); i++){
            m_weights_vector.push_back( Matrix(size(weights.m_weights_vector[i]), arma::fill::randu) );
        }
    }
}

Weights::Weights(const vector<int>& model_architecture,
                 InitType type,
                 bool with_bias)
{
    // TODO: Try to simplify
    if (type == COPY)   // COPY mode is not allowed
    {
        std::cerr << "[ERROR] weight initialization cannot use COPY mode.\n";
        exit(1);
    }

    if (with_bias)    // Also construct the bias
    {
        if (type == ZEROS){
            for(int i = 0; i < model_architecture.size()-1; i++){
                m_weights_vector.push_back(zeros<Matrix>(model_architecture[i], model_architecture[i+1]));
                m_weights_vector.push_back(zeros<Matrix>(1, model_architecture[i+1]));
            }
        }
        else if(type == ONES){
            for(int i = 0; i < model_architecture.size()-1; i++){
                m_weights_vector.push_back(ones<Matrix>(model_architecture[i], model_architecture[i+1]));
                m_weights_vector.push_back(ones<Matrix>(1, model_architecture[i+1]));
            }
        }
        else if(type == GAUSSIAN){
            for(int i = 0; i < model_architecture.size()-1; i++){
                m_weights_vector.push_back(randn<Matrix>(model_architecture[i], model_architecture[i+1]));
                m_weights_vector.push_back(randn<Matrix>(1, model_architecture[i+1]));
            }
        }
        else if(type == UNIFORM){
            for(int i = 0; i < model_architecture.size()-1; i++){
                m_weights_vector.push_back(randu<Matrix>(model_architecture[i], model_architecture[i+1]));
                m_weights_vector.push_back(randu<Matrix>(1, model_architecture[i+1]));
            }
        }
        else
        {
            std::cerr << "[ERROR] weight initialization can only use "
                "ZEROS/ONES/GAUSSIAN/UNIFORM mode.\n";
            exit(1);
        }
    }
    else    // Only construct weights
    {
        if (type == ZEROS){
            for(int i = 0; i < model_architecture.size()-1; i++)
                m_weights_vector.push_back(zeros<Matrix>(1, model_architecture[i+1]));
        }
        else if(type == ONES){
            for(int i = 0; i < model_architecture.size()-1; i++)
                m_weights_vector.push_back(ones<Matrix>(1, model_architecture[i+1]));
        }
        else if(type == GAUSSIAN){
            for(int i = 0; i < model_architecture.size()-1; i++)
                m_weights_vector.push_back(randn<Matrix>(1, model_architecture[i+1]));
        }
        else if(type == UNIFORM){
            for(int i = 0; i < model_architecture.size()-1; i++)
                m_weights_vector.push_back(randu<Matrix>(1, model_architecture[i+1]));
        }
        else
        {
            std::cerr << "[ERROR] weight initialization can only use "
                "ZEROS/ONES/GAUSSIAN/UNIFORM mode.";
            exit(1);
        }
    }
}

Weights::Weights(){}

Weights::~Weights(){ m_weights_vector.clear(); }

void Weights::push_back(const Matrix &matrix){
    m_weights_vector.push_back(Matrix(matrix));
}

Weights& Weights::operator=(const Weights weight){
    m_weights_vector = weight.m_weights_vector;
    return *this;
}

Weights& Weights::operator*=(const double scalar){
    for(int i = 0; i < get_count(); i++){
        m_weights_vector[i] *= scalar;
    }
    return *this;
}

Weights& Weights::operator+=(const Weights weight){
    for(int i = 0; i < get_count(); i++){
        m_weights_vector[i] += weight.m_weights_vector[i];
    }
    return *this;
}

void Weights::save(const std::string &filename) const
{
    std::ofstream ofs(filename, std::ofstream::out);
    if (ofs.is_open()) {
        for (int i = 0; i < get_count(); i++)
            m_weights_vector[i].save(ofs);
    }
    else {
        std::cout << "[ERROR] Failed to open " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Weights::load(const std::string &filename)
{
    std::ifstream ifs(filename, std::ifstream::in);
    if (ifs.is_open()) {
        for (int i = 0; i < get_count(); ++i)   // originally get_count() - 1, not sure why
            m_weights_vector[i].load(ifs);
    }
    else {
        std::cout << "[ERROR] Failed to open " << filename << std::endl;
        exit(EXIT_FAILURE);
    }
}
