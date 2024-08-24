#include "random_generator.h"

// Mersenne Twister implementation
void mt19937_init(mt19937_t *rng, uint32_t seed) {
    rng->state[0] = seed;
    for (int i = 1; i < 624; i++) {
        rng->state[i] = (1812433253U * (rng->state[i-1] ^ (rng->state[i-1] >> 30)) + i);
    }
    rng->index = 624;
}

void mt19937_twist(mt19937_t *rng) {
    for (int i = 0; i < 624; i++) {
        uint32_t y = (rng->state[i] & 0x80000000) + (rng->state[(i+1) % 624] & 0x7fffffff);
        rng->state[i] = rng->state[(i + 397) % 624] ^ (y >> 1);
        if (y % 2 != 0) {
            rng->state[i] ^= 2567483615U;
        }
    }
    rng->index = 0;
}

uint32_t mt19937_generate(mt19937_t *rng) {
    if (rng->index >= 624) {
        mt19937_twist(rng);
    }

    uint32_t y = rng->state[rng->index++];
    y ^= (y >> 11);
    y ^= (y << 7) & 2636928640U;
    y ^= (y << 15) & 4022730752U;
    y ^= (y >> 18);

    return y;
}

// Linear Congruential Generator (LCG)
void lcg_init(lcg_t *rng, uint32_t seed, uint32_t a, uint32_t c, uint32_t m) {
    rng->a = a;
    rng->c = c;
    rng->m = m;
    rng->state = seed;
}

uint32_t lcg_generate(lcg_t *rng) {
    rng->state = (rng->a * rng->state + rng->c) % rng->m;
    return rng->state;
}

// std::minstd_rand0
void minstd_rand0_init(lcg_t *rng, uint32_t seed) {
    lcg_init(rng, seed, 16807, 0, 2147483647U);
}

uint32_t minstd_rand0_generate(lcg_t *rng) {
    return lcg_generate(rng);
}

// std::minstd_rand
void minstd_rand_init(lcg_t *rng, uint32_t seed) {
    lcg_init(rng, seed, 48271, 0, 2147483647U);
}

uint32_t minstd_rand_generate(lcg_t *rng) {
    return lcg_generate(rng);
}

// Subtract with carry generator
void swc_init(swc_t *rng, uint32_t seed, uint32_t max) {
    rng->state = seed;
    rng->carry = 0;
    rng->max = max;
}

uint32_t swc_generate(swc_t *rng) {
    uint32_t prev_state = rng->state;
    rng->state = (rng->state - rng->carry);
    if (rng->state > prev_state) {
        rng->carry = 1;
    } else {
        rng->carry = 0;
    }
    rng->state %= rng->max;
    return rng->state;
}
