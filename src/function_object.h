#ifndef FUNCTION_OBJECT_H
#define FUNCTION_OBJECT_H

typedef struct {
    void *data;
    int (*invoke)(void *data, int arg);
} UnaryFunctionObject;

typedef struct {
    void *data;
    int (*invoke)(void *data, int arg1, int arg2);
} BinaryFunctionObject;

typedef struct {
    void *data;
    int (*invoke)(void *data, int arg);
} Predicate;

void unary_function_object_init(UnaryFunctionObject *f, void *data, int (*invoke)(void *, int));
void binary_function_object_init(BinaryFunctionObject *f, void *data, int (*invoke)(void *, int, int));
void predicate_init(Predicate *p, void *data, int (*invoke)(void *, int));

#endif // FUNCTION_OBJECT_H