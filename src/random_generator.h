#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <stdint.h>

typedef struct {
    uint32_t state[624];
    int index;
} mt19937_t;

void mt19937_init(mt19937_t *rng, uint32_t seed);
uint32_t mt19937_generate(mt19937_t *rng);

typedef struct {
    uint32_t a;
    uint32_t c;
    uint32_t m;
    uint32_t state;
} lcg_t;

void lcg_init(lcg_t *rng, uint32_t seed, uint32_t a, uint32_t c, uint32_t m);
uint32_t lcg_generate(lcg_t *rng);

void minstd_rand0_init(lcg_t *rng, uint32_t seed);
uint32_t minstd_rand0_generate(lcg_t *rng);

void minstd_rand_init(lcg_t *rng, uint32_t seed);
uint32_t minstd_rand_generate(lcg_t *rng);

typedef struct {
    uint32_t state;
    uint32_t carry;
    uint32_t max;
} swc_t;

void swc_init(swc_t *rng, uint32_t seed, uint32_t max);
uint32_t swc_generate(swc_t *rng);

#endif // RANDOM_GENERATOR_H
