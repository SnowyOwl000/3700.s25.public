//
// Created by Dr. Bob Kramer on 2/12/25.
//

#ifndef HYBRIDSORT_SAMPLER_H
#define HYBRIDSORT_SAMPLER_H

#include <random>

class Sampler {
public:
    explicit Sampler(int32_t n);
    ~Sampler();

    int32_t getSample();

private:
    int32_t
        nElements,
        *elements;
    std::mt19937
        *mt;
};


#endif //HYBRIDSORT_SAMPLER_H
