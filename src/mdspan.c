#include "mdspan.h"
#include <stdlib.h>

void mdspan_init(Mdspan *md, int rows, int cols) {
    md->data = (int *)malloc(rows * cols * sizeof(int));
    md->rows = rows;
    md->cols = cols;
}

int mdspan_get(Mdspan *md, int row, int col) {
    return md->data[row * md->cols + col];
}

void mdspan_set(Mdspan *md, int row, int col, int value) {
    md->data[row * md->cols + col] = value;
}

void mdspan_free(Mdspan *md) {
    free(md->data);
}
