//
// Created by Dr. Bob Kramer on 2/12/25.
//

#include <stdexcept>
#include "sampler.h"

Sampler::Sampler(int32_t n) {
    std::random_device
        rd;

    nElements = n;

    elements = new int32_t[n];

    for (int32_t i=0;i<n;i++)
        elements[i] = i;

    mt = new std::mt19937(rd());
}

Sampler::~Sampler() {

    delete mt;

    delete[] elements;
}

int32_t Sampler::getSample() {
    int32_t
        e,
        i;

    if (nElements == 0)
        throw std::underflow_error("getSample: Sampler is empty");

    std::uniform_int_distribution<int32_t>
            dis(0,nElements-1);

    i = dis(*mt);

    e = elements[i];

    nElements--;

    elements[i] = elements[nElements];

    return e;
}