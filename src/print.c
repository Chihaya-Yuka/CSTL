#include "print.h"
#include <stdlib.h>

void print_int(const void* value) {
    printf("%d", *(const int*)value);
}

void print_float(const void* value) {
    printf("%f", *(const float*)value);
}

void print_double(const void* value) {
    printf("%lf", *(const double*)value);
}

void print_char(const void* value) {
    printf("%c", *(const char*)value);
}

void print_string(const void* value) {
    printf("%s", *(const char**)value);
}

void print_pointer(const void* value) {
    printf("%p", value);
}

PrintArgs create_print_args(size_t capacity) {
    PrintArgs args = {
        .args = (PrintArg*)malloc(sizeof(PrintArg) * capacity),
        .count = 0,
        .capacity = capacity
    };
    return args;
}

void destroy_print_args(PrintArgs* args) {
    if (args && args->args) {
        free(args->args);
        args->args = NULL;
        args->count = 0;
        args->capacity = 0;
    }
}

void vprint_formatted(const char* format, PrintArgs* args) {
    size_t arg_index = 0;
    const char* curr = format;
    
    while (*curr) {
        if (*curr == '{') {
            if (strncmp(curr, PRINT_ESCAPE, 2) == 0) {
                putchar('{');
                curr += 2;
                continue;
            }
            if (strncmp(curr, PRINT_PLACEHOLDER, 2) == 0) {
                if (arg_index < args->count) {
                    args->args[arg_index].func(args->args[arg_index].value);
                    arg_index++;
                }
                curr += 2;
                continue;
            }
        }
        putchar(*curr);
        curr++;
    }
}
