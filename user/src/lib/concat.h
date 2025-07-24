
#include "sys.h"
#include "mem.h"

#ifndef CONCAT_H
#define CONCAT_H

// Taken from https://stackoverflow.com/questions/8465006/how-do-i-concatenate-two-strings-in-c
char* strcat(const char* a, const char* b, size_t *out_size) {
    size_t len_a = strlen(a);
    size_t len_b = strlen(b);
    size_t total_len = len_a + len_b + 1;

    // Allocate enough memory for a + b + null terminator
    char *res = sys_malloc(total_len);
    if (!res) return 0;  // Check malloc failure

    // Copy string a to res
    for (size_t i = 0; i < len_a; i++) {
        res[i] = a[i];
    }
    // Copy string b to res starting after a
    for (size_t j = 0; j < len_b; j++) {
        res[len_a + j] = b[j];
    }
    // Null terminate
    res[len_a + len_b] = '\0';

    if (out_size) *out_size = total_len;
    return res;
}
#endif