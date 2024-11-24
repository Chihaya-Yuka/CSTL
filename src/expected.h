#ifndef EXPECTED_H
#define EXPECTED_H

typedef struct {
    int has_value;
    union {
        int value;
        const char *error_message;
    };
} Expected;

Expected expected_success(int value);
Expected expected_failure(const char *error_message);

#endif // EXPECTED_H
