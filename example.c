#include <stdio.h>
#include "max_min.h"
#include "filter.h"
#include "reduce.h"
#include "random_generator.h"
#include "vector.h"
#include "list.h"
#include "set.h"
#include "map.h"
#include "rb_tree.h"

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
    List_node *head;
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

    // RB-Tree example
    RBTree_node tree;
    rb_tree_init(&tree, 0);
    rb_tree_insert(&tree, 12);
    rb_tree_insert(&tree, 42);
    rb_tree_insert(&tree, 114);
    rb_tree_insert(&tree, 514);
    rb_tree_insert(&tree, 15);
    rb_tree_insert(&tree, 14);
    rb_tree_insert(&tree, 21);
    if(rb_tree_find(&tree, 42)) {
        printf("Found 42 in tree.\n");
    }
    if(!rb_tree_find(&tree, 100)) {
        printf("Did not find 100 in tree.\n");
    }
    if(rb_tree_find(&tree, 14)) {
        printf("Found 14 in tree.\n");
    }
    rb_tree_remove(&tree, 14);
    if(!rb_tree_find(&tree, 14)) {
        printf("Did not find 14 in tree after removal.\n");
    }

    return 0;
}