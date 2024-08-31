# CSTL - Standard Template Library for C ⭐

<div align="center">
  
  ![CSTL Logo](/.github/logo.png)

  ![GitHub](https://img.shields.io/github/license/Chihaya-Yuka/CSTL)

  [![Website](https://img.shields.io/badge/Website-online-brightgreen)](https://cstl.awaland.xyz/)
  
</div>

**CSTL** is a standard template library for the C programming language, designed to provide a more modern programming experience for C language embedded developers. With CSTL, you can use common data structures and algorithms to improve the efficiency and readability of your C code.

CSTL is an open-source project. If you have any suggestions or encounter issues while using it, please feel free to provide feedback through [Issues](https://github.com/Chihaya-Yuka/CSTL/issues).

## Features

- **Rich Data Structures**:
  - Dynamic Array (`Vector`)
  - Linked List (`List`)
  - Stack (`Stack`)
  - Queue (`Queue`)
  - Dictionary (`Map`)
  - Set (`Set`)

- **Efficient Algorithms**:
  - Sorting (`Sort`)
  - Searching (`Search`)
  - Finding Maximum/Minimum (`Max/Min`)
  - Filtering (`Filter`)
  - Mapping (`Map`)
  - Reducing (`Reduce`)

- **Function Objects**: Supports unary and binary function objects, predicates, etc., for various operations within algorithms.

- **Generic Interfaces**: All data structures and algorithms are implemented with generic interfaces, supporting generic programming.

- **Simple and Easy to Use**: API design similar to C++ STL, making it easy for C developers to get started.

## Example

```C
#include <stdio.h>
#include "max_min.h"
#include "filter.h"
#include "reduce.h"
#include "random_generator.h"
#include "vector.h"
#include "list.h"
#include "set.h"
#include "map.h"

int int_compare(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}

int is_even(const void *item, void *context) {
    return (*(const int *)item) % 2 == 0;
}

void *sum(void *accumulator, const void *item, void *context) {
    *(int *)accumulator += *(const int *)item;
    return accumulator;
}

int main() {
    mt19937_t mt_rng;
    mt19937_init(&mt_rng, 42);
    printf("Mersenne Twister: %u\n", mt19937_generate(&mt_rng));

    lcg_t minstd0_rng;
    minstd_rand0_init(&minstd0_rng, 42);
    printf("minstd_rand0: %u\n", minstd_rand0_generate(&minstd0_rng));

    lcg_t minstd_rng;
    minstd_rand_init(&minstd_rng, 42);
    printf("minstd_rand: %u\n", minstd_rand_generate(&minstd_rng));

    swc_t swc_rng;
    swc_init(&swc_rng, 42, 100);
    printf("Subtract with carry: %u\n", swc_generate(&swc_rng));

    int numbers[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(numbers) / sizeof(numbers[0]);

    int *max = (int *)find_max(numbers, size, sizeof(int), int_compare);
    printf("Max: %d\n", *max);

    int *min = (int *)find_min(numbers, size, sizeof(int), int_compare);
    printf("Min: %d\n", *min);

    size_t result_size;
    int *filtered = (int *)filter(numbers, size, sizeof(int), is_even, NULL, &result_size);
    printf("Filtered: ");
    for (size_t i = 0; i < result_size; i++) {
        printf("%d ", filtered[i]);
    }
    printf("\n");
    free(filtered);

    int initial_value = 0;
    int *sum_result = (int *)reduce(numbers, size, sizeof(int), sum, &initial_value, NULL);
    printf("Sum: %d\n", *sum_result);

    // Vector example
    Vector v;
    vector_init(&v);
    vector_push_back(&v, 10);
    vector_push_back(&v, 20);
    printf("Vector size: %zu\n", vector_size(&v));
    printf("Vector element at index 1: %d\n", vector_get(&v, 1));
    vector_free(&v);

    // List example
    Node *head;
    list_init(&head);
    list_append(&head, 5);
    list_append(&head, 15);
    printf("List size: %zu\n", list_size(head));
    list_free(head);

    // Set example
    Set s;
    set_init(&s);
    set_insert(&s, 42);
    printf("Set contains 42: %d\n", set_contains(&s, 42));
    set_remove(&s, 42);
    printf("Set contains 42 after removal: %d\n", set_contains(&s, 42));
    set_free(&s);

    // Map example
    Map m;
    map_init(&m);
    map_insert(&m, 1, 100);
    int value;
    if (map_get(&m, 1, &value)) {
        printf("Map value for key 1: %d\n", value);
    }
    map_remove(&m, 1);
    if (!map_get(&m, 1, &value)) {
        printf("Key 1 not found in map.\n");
    }
    map_free(&m);
    printf("It's MyGO!!!!!");
    return 0;
}
```
