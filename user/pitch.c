#include "lib/sys.h"
#include "lib/lib.h"

#define __NEW_UTS_LEN 64

struct utsname {
    char sysname[65];
    char nodename[65];
    char release[65];
    char version[65];
    char machine[65];
    char domainname[65];
};

struct sysinfo {
    long uptime;             /* Seconds since boot */
    unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
    unsigned long totalram;  /* Total usable main memory size */
    unsigned long freeram;   /* Available memory size */
    unsigned long sharedram; /* Amount of shared memory */
    unsigned long bufferram; /* Memory used by buffers */
    unsigned long totalswap; /* Total swap space size */
    unsigned long freeswap;  /* Swap space still available */
    unsigned short procs;    /* Number of current processes */
    unsigned long totalhigh; /* Total high memory size */
    unsigned long freehigh;  /* Available high memory size */
    unsigned int mem_unit;   /* Memory unit size in bytes */
    char _f[20-2*sizeof(long)-sizeof(int)];
                            /* Padding to 64 bytes */
};

int main() {
    struct utsname uts;
    sys_write(STDOUT,&newline,1);
    if(sys_uname(&uts) == 0) {
        sys_write(STDOUT,uts.nodename,65);
        sys_write(STDOUT,&newline,1);
        for (int i = 0; i < strlen(uts.nodename); i++) {
            sys_write(STDOUT,"-",1);
        }
        sys_write(STDOUT,"\nKernel:\t",9);
        sys_write(STDOUT,uts.sysname,65);
        sys_write(STDOUT," ",1);
        sys_write(STDOUT,uts.release,65);
        sys_write(STDOUT,"\nArch:\t",7);
        sys_write(STDOUT,uts.machine,65);
    }

    struct sysinfo info;
    if (sys_sysinfo(&info) == 0) {
        if (info.totalram) {
            sys_write(STDOUT,"\nRAM:\t[",7);
            float freeRam = (float)info.freeram/(float)info.totalram;
            for (float i = 1.0; i > 0.0; i-=0.05) {
                if (i <= freeRam) {
                    sys_write(STDOUT,"-",1);
                } else {
                    sys_write(STDOUT,"#",1);
                }
            }
            sys_write(STDOUT,"] ",2);
            printint((info.totalram-info.freeram)/1024);
            sys_write(STDOUT," / ",3);
            printint(info.totalram/1024);
            sys_write(STDOUT," KiB",4);
        }
        
        if (info.totalswap) {
            sys_write(STDOUT,"\nSwap:\t[",8);
            float freeSwap = (float)info.freeswap/(float)info.totalswap;
            for (float i = 1.0; i > 0.0; i-=0.05) {
                if (i <= freeSwap) {
                    sys_write(STDOUT,"-",1);
                } else {
                    sys_write(STDOUT,"#",1);
                }
            }
            sys_write(STDOUT,"] ",2);
            printint((info.totalswap-info.freeswap)/1024);
            sys_write(STDOUT," / ",3);
            printint(info.totalswap/1024);
            sys_write(STDOUT," KiB",4);
        }
        
        if (info.uptime) {
            sys_write(STDOUT,"\nUptime:\t[",9);
            printint(info.uptime/60/60);
            sys_write(STDOUT,"h ",2);
            printint(info.uptime/60%60);
            sys_write(STDOUT,"min ",4);
            printint(info.uptime%60);
            sys_write(STDOUT,"s",1);
        }
    }
    sys_write(STDOUT,&newline,1);
    sys_exit(0);
}
