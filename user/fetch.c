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
        printf("Total RAM: %.2f MB\n", info.totalram / 1024.0 / 1024.0);
        printf("Free RAM:  %.2f MB\n", info.freeram / 1024.0 / 1024.0);
    }
    return 0;
}
