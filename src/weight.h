#ifndef __WEIGHT_H__
#define __WEIGHT_H__

#include <iostream>
#include <vector>

#include "matrix.h"

using std::vector;


class Weights{
    // a wrapper class for vector<Matrix>
public:
    enum InitType{ COPY, ZEROS, ONES, GAUSSIAN, UNIFORM };

    Weights();
    Weights(const Weights& weights, InitType type=COPY);
    Weights(const vector<int>& model_architecture, InitType type=ZEROS, bool with_bias=true);
    ~Weights();
    void push_back(const Matrix &matrix);

    inline const uint get_count() const { return m_weights_vector.size(); }
    //inline void set_weights_vector(const Weights& weights) { m_weights_vector = weights.m_weights_vector;}
    inline Matrix &operator[] (const int x) { return m_weights_vector[x]; }
    inline const Matrix operator[] (const int x) const { return m_weights_vector[x]; }
    Weights& operator=(const Weights weight);
    Weights& operator*=(const double scalar);
    Weights& operator+=(const Weights weight);
    // overload [], +, -, *, / operators

    // Save, Load
    void save(const std::string &filename) const;
    void load(const std::string &filename);
private:
    vector<Matrix> m_weights_vector;
};

#endif
