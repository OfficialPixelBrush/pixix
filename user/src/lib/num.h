// Helper library for numbers
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
        sys_write(STDOUT, "-", 1);
        number = -number;
    }

    int integerPart = number / scaler;
    int fractionPart = number % scaler;

    // Print integer part
    char buf[32];
    int idx = 0;
    if (integerPart == 0) {
        buf[idx++] = '0';
    } else {
        int temp = integerPart;
        while (temp > 0) {
            buf[idx++] = (temp % 10) + '0';
            temp /= 10;
        }
        // reverse
        for (int i = 0; i < idx / 2; i++) {
            char c = buf[i];
            buf[i] = buf[idx - 1 - i];
            buf[idx - 1 - i] = c;
        }
    }
    sys_write(STDOUT, buf, idx);

    if (digitsAfterDecimal > 0) {
        sys_write(STDOUT, ".", 1);

        // Scale fraction to digitsAfterDecimal
        for (int i = 0; i < digitsAfterDecimal; i++) {
            fractionPart *= 10;
            char c = (fractionPart / scaler) + '0';
            sys_write(STDOUT, &c, 1);
            fractionPart %= scaler;
        }
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

void printoct(int number) {
    char buf[12];
    int i = 0;
    if (number == 0) {
        sys_write(STDOUT, "0", 1);
        return;
    }
    while (number > 0) {
        buf[i++] = '0' + (number & 0x7);
        number >>= 3;
    }
    // print in reverse
    while (i--) {
        sys_write(STDOUT, &buf[i], 1);
    }
}

int readhex(const char *p) {
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

int readoct(const char* p) {
    int result = 0;
    while (*p) {
        if (*p < '0' || *p > '7') {
            break;
        }
        result = (result << 3) | (*p - '0');
        ++p;
    }
    return result;
}

#endif