#ifndef GENERATOR_H
#define GENERATOR_H

typedef struct Generator {
    int (*next)(void *state);
    void *state;
} Generator;

Generator create_range(int start, int end);

#endif // GENERATOR_H
