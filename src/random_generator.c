#include "random_generator.h"

// Constants
#define MT19937_N 624
#define MT19937_M 397
#define MT19937_MATRIX_A 0x9908b0dfU   // constant vector a
#define MT19937_UPPER_MASK 0x80000000U // most significant w-r bits
#define MT19937_LOWER_MASK 0x7fffffffU // least significant r bits

// Mersenne Twister implementation
void mt19937_init(mt19937_t *rng, uint32_t seed) {
    rng->state[0] = seed;
    for (int i = 1; i < MT19937_N; i++) {
        rng->state[i] = 1812433253U * (rng->state[i-1] ^ (rng->state[i-1] >> 30)) + i;
    }
    rng->index = MT19937_N;
}

void mt19937_twist(mt19937_t *rng) {
    static const uint32_t mag01[2] = { 0x0U, MT19937_MATRIX_A };
    uint32_t y;

    for (int i = 0; i < MT19937_N; i++) {
        y = (rng->state[i] & MT19937_UPPER_MASK) | (rng->state[(i+1) % MT19937_N] & MT19937_LOWER_MASK);
        rng->state[i] = rng->state[(i + MT19937_M) % MT19937_N] ^ (y >> 1) ^ mag01[y & 0x1U];
    }
    rng->index = 0;
}

uint32_t mt19937_generate(mt19937_t *rng) {
    if (rng->index >= MT19937_N) {
        mt19937_twist(rng);
    }

    uint32_t y = rng->state[rng->index++];
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680U;
    y ^= (y << 15) & 0xefc60000U;
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

inline uint32_t lcg_generate(lcg_t *rng) {
    rng->state = (rng->a * rng->state + rng->c) % rng->m;
    return rng->state;
}

void minstd_rand0_init(lcg_t *rng, uint32_t seed) {
    lcg_init(rng, seed, 16807, 0, 2147483647U);
}

uint32_t minstd_rand0_generate(lcg_t *rng) {
    return lcg_generate(rng);
}

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
    rng->state -= rng->carry;
    rng->carry = rng->state > prev_state ? 1 : 0;
    rng->state %= rng->max;
    return rng->state;
}
