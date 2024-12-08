#include <stdio.h>
#include <stdlib.h>
#include "template.h"
#include "expected.h"
#include "mdspan.h"
#include "flat_set.h"
#include "flat_map.h"
#include "generator.h"
#include "map.h"
#include "set.h"
#include "random_generator.h"
#include "max_min.h"
#include "filter.h"
#include "reduce.h"
#include "vector.h"
#include "list.h"
#include "rb_tree.h"
#include "print.h"

int int_compare(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);
}



void *sum(void *accumulator, const void *item, void *context) {
    *(int *)accumulator += *(const int *)item;
    return accumulator;
}

int is_even(const void *item, void *context) {
    return (*(const int *)item) % 2 == 0;
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

    Generator gen = create_range(1, 5);
    value = 0;
    while ((value = gen.next(gen.state)) != -1) {
        printf("Generated: %d\n", value);
    }

    FlatMap map;
    flat_map_init(&map, 10);
    flat_map_insert(&map, 1, 100);
    printf("FlatMap key 1: %d\n", flat_map_get(&map, 1));
    flat_map_free(&map);

    FlatSet set;
    flat_set_init(&set, 10);
    flat_set_insert(&set, 42);
    printf("FlatSet contains 42: %d\n", flat_set_contains(&set, 42));
    flat_set_free(&set);

    Mdspan md;
    mdspan_init(&md, 2, 3);
    mdspan_set(&md, 1, 2, 99);
    printf("Mdspan (1,2): %d\n", mdspan_get(&md, 1, 2));
    mdspan_free(&md);

    Expected e = expected_success(42);
    if (e.has_value) {
        printf("Expected value: %d\n", e.value);
    }

    // RB Tree example
    RBTree tree;
    RBTree_init(&tree);
    RBTree_insert(&tree, 42);
    printf("RBTree contains 42: %d\n", RBTree_contains(&tree, 42));
    RBTree_insert(&tree, 100);
    RBTree_insert(&tree, 20);
    RBTree_insert(&tree, 75);
    RBTree_insert(&tree, 150);
    printf("RBTree contains 20: %d\n", RBTree_contains(&tree, 20));
    printf("RBTree contains 75: %d\n", RBTree_contains(&tree, 75));
    RBTree_delete(&tree, 42);
    printf("RBTree contains 42 after deletion: %d\n", RBTree_contains(&tree, 42));
    printf("RBTree contains 100: %d\n", RBTree_contains(&tree, 100));
    RBTree_delete(&tree, 75);
    printf("RBTree contains 75 after deletion: %d\n", RBTree_contains(&tree, 75));
    RBTree_delete(&tree, 20);
    printf("RBTree contains 20 after deletion: %d\n", RBTree_contains(&tree, 20));
    printf("RBTree contains 150: %d\n", RBTree_contains(&tree, 150));

    RBTree_free(&tree);

    // Template example
    Array_int* int_array = Array_int_create(10);
    Array_int_push(int_array, 1);
    Array_int_push(int_array, 2);
    Array_int_push(int_array, 3);
    Array_float* float_array = Array_float_create(10);
    Array_float_push(float_array, 1.1f);
    Array_float_push(float_array, 2.2f);
    List_int* int_list = List_int_create();
    List_int_push_front(int_list, 1);
    List_int_push_front(int_list, 2);
    Array_int_destroy(int_array);
    Array_float_destroy(float_array);
    List_int_destroy(int_list);

    // Print example
    char* band = "MyGO!!!!!";
    print("BanG Dream, It's {}", band);
    return 0;
}
