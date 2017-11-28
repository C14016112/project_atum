#ifndef __MATH_FUNCTIONS_H__
#define __MATH_FUNCTIONS_H__

#include "matrix.h"

// Testinf function reference: https://en.wikipedia.org/wiki/Test_functions_for_optimization
namespace function{

// Styblinski–Tang function
inline Matrix styblinski_tang(const Matrix &input) {return 0.5 * arma::sum(arma::pow(input,4) - 16* arma::pow(input,2) + 5*input, 1); }
inline Matrix styblinski_tang_critical_point(int dimension) { return -2.903534*arma::ones<Matrix>(1, dimension); }
inline double styblinski_tang_minimum(int dimension) { return -39.166165 * dimension; }

// Sphere function
inline Matrix sphere(const Matrix &input) { return arma::sum(arma::square(input),1); }
inline Matrix sphere_critical_point(int dimension) { return arma::zeros<Matrix>(1, dimension); }
inline double sphere_minimum(int dimension) { return 0; }


// Rastrigin function
inline Matrix rastrigin(const Matrix &input) {
    static const double SCALE = 10;
    static const double PI = 3.1415926535897;

    Matrix tmp = arma::square(input) - SCALE*arma::cos(2*PI*input);
    return SCALE*input.n_cols + arma::sum(tmp,1);
}
inline Matrix rastrigin_critical_point(int dimension) { return arma::zeros<Matrix>(1, dimension); }
inline double rastrigin_minimum(int dimension){ return 0; }

}

#endif