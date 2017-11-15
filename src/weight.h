#ifndef __WEIGHT_H__
#define __WEIGHT_H__

#include <iostream>
#include <vector>

#include "matrix.h"

using std::vector;

enum InitType{
        COPY, ZEROS, ONES, GAUSSIAN, UNIFORM
    };

class Weights{
    // a wrapper class for vector<Matrix>
public:
    Weights(const Weights& weights, InitType type=COPY);
    Weights(const vector<int>& model_architecture, InitType type=ZEROS);
    Weights();
    ~Weights();
    void push_back(const Matrix &matrix);
    void add_weights(const Weights& weights);
    void multiply_scalar(const double scalar);
    
    inline uint get_count() const { return m_weights_vector.size(); }
    inline void set_weights_vector(const Weights& weights) { m_weights_vector = weights.m_weights_vector;}
    inline Matrix &operator[] (const int x) { return m_weights_vector[x];}
    // overload [], +, -, *, / operators
private:
	vector<Matrix> m_weights_vector;
};

#endif