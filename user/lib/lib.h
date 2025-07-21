// Helper libarary with convenient functions
#include "sys.h"

#ifndef LIB_H
#define LIB_H

#define MAX_NUMBER_CHARACTER 100000000
char newline = '\n';

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

void errprint(int number) {
    if (number == 0) { return; }
    printint(number);
    sys_write(STDOUT, ": ", 2);
    switch(number) {
        case -1:
            sys_write(STDOUT, "Operation not permitted",23);
            break;
        case -2:
            sys_write(STDOUT, "No such file or directory",25);
            break;
        case -3:
            sys_write(STDOUT, "No such process",15);
            break;
        case -4:
            sys_write(STDOUT, "Interrupted system call",23);
            break;
        case -5:
            sys_write(STDOUT, "Input/output error",18);
            break;
        case -14:
            sys_write(STDOUT, "Bad address",11);
            break;
        case -19:
            sys_write(STDOUT, "No such device",14);
            break;
        case -22:
            sys_write(STDOUT, "Invalid argument",16);
            break;
        case -101:
            sys_write(STDOUT, "Network is unreachable",22);
            break;
    }
    sys_write(STDOUT,&newline,1);
    if (number < 0) {
        sys_exit(1);
    }
}
#endif