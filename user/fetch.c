#include <unistd.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

int main() {
    struct utsname uts;
    if(uname(&uts) == 0) {
        printf("OS Name: %s\n", uts.sysname);
        printf("Node Name: %s\n", uts.nodename);
        printf("Release: %s\n", uts.release);
        printf("Version: %s\n", uts.version);
        printf("Machine: %s\n", uts.machine);
    }
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        unsigned long usedRam = info.totalram - info.freeram;
        printf("RAM: %.2f/%.2f MB\n", usedRam / 1024.0 / 1024.0,  info.totalram / 1024.0 / 1024.0);
        unsigned long usedSwap = info.totalswap - info.freeswap;
        printf("Swap:  %.2f/%.2f MB\n", usedSwap / 1024.0 / 1024.0, info.totalswap / 1024.0 / 1024.0);
        printf("Uptime: %ld min, %ld s\n", info.uptime/60, info.uptime%60);
    }
    return 0;
}
