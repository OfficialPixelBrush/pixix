// Helper libarary for numbers
#include "sys.h"

#define MAX_NUMBER_CHARACTER 100000000

#ifndef NUM_H
#define NUM_H
void printint(int number) {
    if (number < 0) {
        sys_write(STDOUT,"-",1);
        number=-number;
    }
    if (number == 0) {
        sys_write(STDOUT,"0",1);
    }
    int divisor = MAX_NUMBER_CHARACTER;
    int foundNonZero = 0;
    while(divisor > 0) {
        int result = number / divisor;
        if (result != 0) {
            foundNonZero = 1;
        }
        if (foundNonZero) {
            char resChar = '0'+result;
            sys_write(STDOUT,&resChar,1);
        }
        number = number % divisor;
        divisor /= 10;
    }
}

void printfix(int number, int scaler, int digitsAfterDecimal) {
    if (number < 0) {
        sys_write(STDOUT,"-",1);
        number=-number;
    }
    if (number == 0) {
        sys_write(STDOUT,"0",1);
    }
    int digitsSinceDecimal = -1;
    int divisor = MAX_NUMBER_CHARACTER;
    int foundNonZero = 0;
    while(divisor > 0) {
        // Get the whole number
        int result = number / divisor;
        // If the divisor and scaler match up, print a period
        if (divisor*10 == scaler) {
            sys_write(STDOUT,".",1);
            digitsSinceDecimal = 0;
        }
        // Count how many decimal numbers we have left
        if (digitsSinceDecimal >= 0) {
            digitsSinceDecimal++;
        }
        // If we're done, we're done
        if (digitsSinceDecimal > digitsAfterDecimal) {
            break;
        }
        // Search for the leading 0
        if (result != 0 && digitsSinceDecimal == 0) {
            foundNonZero = 1;
        }
        if (foundNonZero) {
            char resChar = '0'+result;
            sys_write(STDOUT,&resChar,1);
        }
        number = number % divisor;
        divisor /= 10;
    }
}

void printhex(int number) {
    // 2345859625
    //   8BD2FA29
    for (int i = sizeof(int)*2-1; i >= 0; i--) {
        char out = '0';
        char offset = ((number >> i*4) & 0xF) & 0xFF;
        if (offset > '9'-'0') {
            offset += 7;
        }
        out += offset;
        sys_write(STDOUT,&out,1);
    }
}

int readnum(const char *p) {
    int result = 0;
    const char *end = p;
    while (*end) end++;
    end--;
    for (const char* q = p; q <= end; ++q) {
        result = result << 4;
        char c = *q;
        if (c >= '0' && c <= '9') {
            result |= (c - '0');
        } else if (c >= 'A' && c <= 'F') {
            result |= (c - 'A' + 10);
        }
    }
    return result;
}

#endif