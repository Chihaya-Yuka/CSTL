#include "function_object.h"

void unary_function_object_init(UnaryFunctionObject *f, void *data, int (*invoke)(void *, int)) {
    f->data = data;
    f->invoke = invoke;
}

void binary_function_object_init(BinaryFunctionObject *f, void *data, int (*invoke)(void *, int, int)) {
    f->data = data;
    f->invoke = invoke;
}

void predicate_init(Predicate *p, void *data, int (*invoke)(void *, int)) {
    p->data = data;
    p->invoke = invoke;
}