#ifndef __UTILS_H__
#define __UTILS_H__

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <armadillo>

namespace utils{

void init_random_seed(unsigned seed)
{
    arma::arma_rng::set_seed(seed);
    std::srand(seed);
}

void init_random_seed()
{
    arma::arma_rng::set_seed_random();
    std::srand(std::time(0));
}

}

#endif