// Helper libarary for error printing
#include "sys.h"
#include "num.h"

#ifndef ERR_H
#define ERR_H

void printerr(int number) {
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
        case -9:
            sys_write(STDOUT, "Bad file descriptor",19);
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
        case -25:
            sys_write(STDOUT, "Inappropriate ioctl for device",30);
            break;
        case -30:
            sys_write(STDOUT, "Read-only file system",21);
            break;
        case -101:
            sys_write(STDOUT, "Network is unreachable",22);
            break;
    }
    sys_write(STDOUT,"\n",1);
    if (number < 0) {
        sys_exit(1);
    }
}
#endif