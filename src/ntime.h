#ifndef CTIME_UTILS_H
#define CTIME_UTILS_H

#include <time.h>

time_t get_current_timestamp(void);

long long get_current_timestamp_ms(void);

char* format_time(const char* format, time_t timestamp);

void sleep_seconds(unsigned int seconds);

void sleep_milliseconds(unsigned int milliseconds);

#endif // CTIME_UTILS_H
