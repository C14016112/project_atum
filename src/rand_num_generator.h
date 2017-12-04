#ifndef __RANDOM_NUMBER_GENERATOR_H__

#include<chrono>
#include<iostream>
// reference: https://en.wikipedia.org/wiki/Xorshift#xorshift*
class RandNumGenerator
{
public:
    RandNumGenerator()
    :m_seed(std::chrono::system_clock::now().time_since_epoch().count())
    {

    }

    RandNumGenerator(uint64_t seed)
    :m_seed(seed)
    {
        if (seed == 0){
            std::cerr << __FILE__ << ":" << __LINE__<< ": Seed cannot be zero! Automatically pick another seed.\n";
            m_seed = std::chrono::system_clock::now().time_since_epoch().count();
        }
    }

    uint64_t get_number() {
        m_seed ^= m_seed >> 12;
        m_seed ^= m_seed << 25;
        m_seed ^= m_seed >> 27;
        return m_seed * 0x2545F4914F6CDD1D;
    }
protected:
    uint64_t m_seed = 19940901;
};

#endif
