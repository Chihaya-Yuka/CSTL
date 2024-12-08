#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "template.h"

#define PRINT_PLACEHOLDER "{}"
#define PRINT_ESCAPE "{{"
#define PRINT_ESCAPE_END "}}"

typedef void (*print_func)(const void*);

void print_int(const void* value);
void print_float(const void* value);
void print_double(const void* value);
void print_char(const void* value);
void print_string(const void* value);
void print_pointer(const void* value);

#define GET_PRINT_FUNC(x) _Generic((x), \
    int: print_int, \
    float: print_float, \
    double: print_double, \
    char: print_char, \
    char*: print_string, \
    void*: print_pointer, \
    default: print_pointer)

typedef struct {
    const void* value;
    print_func func;
} PrintArg;

typedef struct {
    PrintArg* args;
    size_t count;
    size_t capacity;
} PrintArgs;

PrintArgs create_print_args(size_t capacity);
void vprint_formatted(const char* format, PrintArgs* args);
void destroy_print_args(PrintArgs* args);

#define ADD_PRINT_ARG(args, value) do { \
    if ((args).count < (args).capacity) { \
        (args).args[(args).count].value = &(value); \
        (args).args[(args).count].func = GET_PRINT_FUNC(value); \
        (args).count++; \
    } \
} while(0)

#define EXPAND(...) __VA_ARGS__
#define FOR_EACH_1(what, args, x) what(args, x)
#define FOR_EACH_2(what, args, x, ...) what(args, x); EXPAND(FOR_EACH_1(what, args, __VA_ARGS__))
#define FOR_EACH_3(what, args, x, ...) what(args, x); EXPAND(FOR_EACH_2(what, args, __VA_ARGS__))
#define FOR_EACH_4(what, args, x, ...) what(args, x); EXPAND(FOR_EACH_3(what, args, __VA_ARGS__))
#define FOR_EACH_5(what, args, x, ...) what(args, x); EXPAND(FOR_EACH_4(what, args, __VA_ARGS__))

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, N, ...) N
#define FOR_EACH_RSEQ_N() 5, 4, 3, 2, 1, 0

#define FOR_EACH_(N, what, args, ...) EXPAND(FOR_EACH_##N(what, args, __VA_ARGS__))
#define FOR_EACH(what, args, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, args, __VA_ARGS__)

#define print(format, ...) do { \
    PrintArgs args = create_print_args(16); \
    FOR_EACH(ADD_PRINT_ARG, args, __VA_ARGS__); \
    vprint_formatted(format, &args); \
    destroy_print_args(&args); \
} while(0)

#define println(format, ...) print(format "\n", __VA_ARGS__)

#endif // PRINT_H
