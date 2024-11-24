#include "generator.h"
#include <stdlib.h>

typedef struct RangeState {
    int current;
    int end;
} RangeState;

static int range_next(void *state) {
    RangeState *range = (RangeState *)state;
    if (range->current >= range->end) {
        return -1; // Signal end
    }
    return range->current++;
}

Generator create_range(int start, int end) {
    RangeState *state = (RangeState *)malloc(sizeof(RangeState));
    state->current = start;
    state->end = end;

    Generator gen = { .next = range_next, .state = state };
    return gen;
}
