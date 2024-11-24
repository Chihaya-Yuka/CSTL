#ifndef MDSPAN_H
#define MDSPAN_H

typedef struct {
    int *data;
    int rows;
    int cols;
} Mdspan;

void mdspan_init(Mdspan *md, int rows, int cols);
int mdspan_get(Mdspan *md, int row, int col);
void mdspan_set(Mdspan *md, int row, int col, int value);
void mdspan_free(Mdspan *md);

#endif // MDSPAN_H
