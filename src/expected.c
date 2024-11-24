#include "expected.h"

Expected expected_success(int value) {
    return (Expected){ .has_value = 1, .value = value };
}

Expected expected_failure(const char *error_message) {
    return (Expected){ .has_value = 0, .error_message = error_message };
}
