// Helper library for error printing
#include "sys.h"
#include "num.h"

#ifndef ERR_H
#define ERR_H

void printerr(int number) {
    if (number == 0) { return; }
    sys_write(STDOUT,"Error ", 6);
    printint(number);
    sys_write(STDOUT,"\n", 1);
    if (number < 0) {
        sys_exit(1);
    }
}

#endif