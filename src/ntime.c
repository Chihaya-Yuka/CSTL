#include "ntime.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

time_t get_current_timestamp(void) {
    return time(NULL);
}

long long get_current_timestamp_ms(void) {
#ifdef _WIN32
    FILETIME ft;
    LARGE_INTEGER li;

    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;

    return (li.QuadPart - 116444736000000000LL) / 10000;
#else
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec) * 1000 + (long long)(tv.tv_usec) / 1000;
#endif
}

char* format_time(const char* format, time_t timestamp) {
    struct tm* timeinfo;
    char* buffer = (char*)malloc(80 * sizeof(char));
    
    if (buffer == NULL) {
        return NULL;
    }

    timeinfo = localtime(&timestamp);
    strftime(buffer, 80, format, timeinfo);
    return buffer;
}

void sleep_seconds(unsigned int seconds) {
#ifdef _WIN32
    Sleep(seconds * 1000);
#else
    sleep(seconds);
#endif
}

void sleep_milliseconds(unsigned int milliseconds) {
#ifdef _WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds * 1000);
#endif
}
