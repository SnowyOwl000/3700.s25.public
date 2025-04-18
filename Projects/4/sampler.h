#ifndef BST_DICTIONARY_SAMPLER_H
#define BST_DICTIONARY_SAMPLER_H

#include <cstdint>
#include <random>

class Sampler {
public:
    explicit Sampler(int32_t _nItems);
    ~Sampler();

    uint32_t getSample();

private:
    int32_t
        *items,
        nItems;
    std::random_device
        *rd;
    std::mt19937
        *mt;
};


#endif //BST_DICTIONARY_SAMPLER_H
