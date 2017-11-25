#ifndef __WEIGHT_H__
#define __WEIGHT_H__

#include <iostream>
#include <vector>

#include "matrix.h"

using std::vector;

enum InitType{ COPY, ZEROS, ONES, GAUSSIAN, UNIFORM }; // TODO: move into the class

class Weights{
    // a wrapper class for vector<Matrix>
public:
    Weights(const Weights& weights, InitType type=COPY);
    Weights(const vector<int>& model_architecture, InitType type=ZEROS, bool with_bias=true);
    Weights();
    ~Weights();
    void push_back(const Matrix &matrix);

    inline uint get_count() const { return m_weights_vector.size(); }
    //inline void set_weights_vector(const Weights& weights) { m_weights_vector = weights.m_weights_vector;}
    inline Matrix &operator[] (const int x) { return m_weights_vector[x]; }
    inline Matrix operator[] (const int x) const { return m_weights_vector[x]; }
    Weights& operator=(const Weights weight);
    Weights& operator*=(const double scalar);
    Weights& operator+=(const Weights weight);
    // overload [], +, -, *, / operators

    // Save, Load
private:
    vector<Matrix> m_weights_vector;
};

#endif
