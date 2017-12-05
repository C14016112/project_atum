#ifndef __UTILS_H__
#define __UTILS_H__

#include <sys/time.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <armadillo>

namespace utils{

inline void init_random_seed(unsigned seed)
{
    arma::arma_rng::set_seed(seed);
    std::srand(seed);
}

inline void init_random_seed()
{
    arma::arma_rng::set_seed_random();
    std::srand(std::time(0));
}

inline double get_current_time_in_seconds()
{
    static const int MILLI_SECONDS = 1e6;
    struct timeval now_time;
    gettimeofday(&now_time, NULL);
    return now_time.tv_sec + (1.0/MILLI_SECONDS) * now_time.tv_usec;
}

}
#endif