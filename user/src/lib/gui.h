#include "sys.h"

#ifndef GUI_H
#define GUI_H
void printbar(float value, float max, float segments) {
    float segmentSize = 1.0/segments;
    float scaledValue = value/max;
    sys_write(STDOUT,"[",1);
    for (float i = 1.0; i > 0.0; i-=segmentSize) {
        if (i <= scaledValue) {
            sys_write(STDOUT,"-",1);
        } else {
            sys_write(STDOUT,"#",1);
        }
    }
    sys_write(STDOUT,"]",1);
}
#endif