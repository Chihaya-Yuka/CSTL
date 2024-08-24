# CSTL - Standard Template Library for C ⭐

**CSTL** 是一个为 C 语言提供的标准模板库，旨在为 C 语言嵌入式开发者提供更加现代化的编程体验。如通过 CSTL，您可以使用常见的数据结构和算法，提升 C 语言开发的效率和代码可读性。

CSTL 是一个开源项目，果您在使用过程中有任何建议或遇到问题，欢迎通过 [Issues](https://github.com/Chihaya-Yuka/CSTL/issues) 进行反馈。

## Features

- **丰富的数据结构**：
  - 动态数组 (`Vector`)
  - 链表 (`List`)
  - 堆栈 (`Stack`)
  - 队列 (`Queue`)
  - 字典 (`Map`)
  - 集合 (`Set`)

- **高效的算法**：
  - 排序 (`Sort`)
  - 搜索 (`Search`)
  - 查找最大/最小值 (`Max/Min`)
  - 过滤 (`Filter`)
  - 映射 (`Map`)
  - 归约 (`Reduce`)

- **函数对象**：支持一元和二元函数对象、谓词等，用于算法中的各种操作。

- **通用接口**：所有数据结构和算法均通过通用接口实现，支持泛型编程。

- **简洁易用**：与 C++ STL 类似的 API 设计，让 C 语言开发者能够轻松上手。

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
