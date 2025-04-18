#include <stdexcept>
#include "sampler.h"

Sampler::Sampler(int32_t _nItems) {

    rd = new std::random_device;

    mt = new std::mt19937((*rd)());

    items = new int32_t[_nItems];

    for (int32_t i=0;i<_nItems;i++)
        items[i] = i;

    nItems = _nItems;
}

Sampler::~Sampler() {

    delete[] items;
}

uint32_t Sampler::getSample() {
    uint32_t
        r,e;

    if (nItems == 0)
        throw std::domain_error("Sampler is empty");

    std::uniform_int_distribution<>
        dis(0,nItems-1);

    r = dis(*mt);
    e = items[r];

    nItems--;

    items[r] = items[nItems];

    return e;
}
