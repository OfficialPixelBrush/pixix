// Helper libarary for strings
#include "sys.h"

#ifndef STR_H
#define STR_H

int strlen(const char* p) {
    int length = 0;
    for (; *p; p++) {
        if (*p == '\0') {
            return length;
        }
        length++;
    }
    return length;
}
#endif