#include "lib/sys.h"
#include "lib/num.h"
#include "lib/str.h"
#include "lib/err.h"
#include "lib/gui.h"
#include "img/pixix.h"

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

int cpuid_procinfo() {
    int eax;
    __asm__ __volatile__(
        "cpuid"
        : "=a"(eax)
        : "a"(1)
    );
    return eax;
}

// This WILL implode on a pre-pentium machine
void cpuid_vendor(char *vendor) {
    int eax, ebx, ecx, edx;
    __asm__ __volatile__(
        "cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(0)
    );

    // Vendor string is stored in EBX, EDX, ECX (in this order)
    *(int *)(vendor + 0) = ebx;
    *(int *)(vendor + 4) = edx;
    *(int *)(vendor + 8) = ecx;
    vendor[12] = '\0';
}

static inline char has_cpuid(void) {
    int eflags;
    int mod_eflags;

    __asm__ __volatile__(
        "pushfl\n\t"
        "popl %0\n\t"            // Save original EFLAGS
        "movl %0, %1\n\t"
        "xorl $0x200000, %1\n\t" // Toggle ID bit (bit 21)
        "pushl %1\n\t"
        "popfl\n\t"
        "pushfl\n\t"
        "popl %1\n\t"            // Read back EFLAGS
        "pushl %0\n\t"
        "popfl\n\t"              // Restore original EFLAGS
        : "=&r"(eflags), "=&r"(mod_eflags)
        :
        : "cc"
    );

    return ((eflags ^ mod_eflags) & 0x200000) != 0;
}

// Just makes this easier
// Also, default to Intel
int vendorStringToId(char* vendor) {
    if (strcmp(vendor,"GenuineIntel") == 0) {
        return 0;
    }
    if (strcmp(vendor,"AuthenticAMD") == 0) {
        return 1;
    }
    return 0;
}

// All of this info has been taken from https://en.wikipedia.org/wiki/CPUID
void printCpuModel(int vendor_id, int processor_info) {
    int familyId = (processor_info >> 8) & 0xF;
    int extendedFamilyId = (processor_info >> 20) & 0xFF;
    if (familyId == 0xF) {
        familyId += extendedFamilyId;
    }
    if (vendor_id == 1) {
        switch(familyId) {
            case 0x4:
                sys_write(STDOUT,"Am486",5);
                return;
            case 0x5:
                sys_write(STDOUT,"K5/K6",5);
                return;
            case 0x6:
                sys_write(STDOUT,"K7/Athlon",9);
                return;
            case 0x0F:
                sys_write(STDOUT,"K8/Hammer",9);
                return;
            case 0x10:
                sys_write(STDOUT,"K10/Phenom",10);
                return;
            case 0x17:
                sys_write(STDOUT,"Zen 1/2",7);
                return;
            case 0x19:
                sys_write(STDOUT,"Zen 3/4",7);
                return;
            case 0x1A:
                sys_write(STDOUT,"Zen 5",5);
                return;
        }
    // Default to Intel
    } else {
        switch(familyId) {
            case 0x4:
                sys_write(STDOUT,"486",3);
                return;
            case 0x5:
                sys_write(STDOUT,"Pentium",7);
                return;
            case 0x6:
                sys_write(STDOUT,"Pentium II or later",19);
                return;
            case 0x0F:
                sys_write(STDOUT,"Pentium 4",9);
                return;
            case 0x13:
                sys_write(STDOUT,"Intel Core",10);
                return;
        }
    }
    printhex(familyId);
}

void _start() {
    struct utsname uts;
    struct sysinfo info;
    printerr(sys_uname(&uts));
    printerr(sys_sysinfo(&info));

    char vendor[13] = "NoCpuidInst";
    int vendor_id = 0;
    int processor_info = 0;
    if (has_cpuid) {
        cpuid_vendor(vendor);
        vendor_id = vendorStringToId(vendor);
        processor_info = cpuid_procinfo();
    }

    size_t n = sizeof(pixix_logo) / sizeof(pixix_logo[0]);
    for (int i = 0; i < n; i++) {
        if (i < n) {
            sys_write(STDOUT,pixix_logo[i],strlen(pixix_logo[i]));
            sys_write(STDOUT,"\x1b[0m ",6);
        }
        switch(i) {
            case 0:
                sys_write(STDOUT,uts.nodename,65);
                break;
            case 1:
                for (int i = 0; i < strlen(uts.nodename); i++) {
                    sys_write(STDOUT,"-",1);
                }
                break;
            case 2:
                sys_write(STDOUT,"Kernel:\t",9);
                sys_write(STDOUT,uts.sysname,65);
                sys_write(STDOUT," ",1);
                sys_write(STDOUT,uts.release,65);
                break;
            case 3:
                sys_write(STDOUT,"CPU:\t",5);
                sys_write(STDOUT,vendor,12);
                //printhex(processor_info);
                sys_write(STDOUT," ",1);
                printCpuModel(vendor_id, processor_info);
                sys_write(STDOUT," (",2);
                sys_write(STDOUT,uts.machine,65);
                sys_write(STDOUT,")",1);
                break;
            case 4:
                if (info.totalram) {
                    int totalRam = (int)((double)info.totalram * ((double)info.mem_unit / (1024.0)));
                    int freeRam  = (int)((double)info.freeram  * ((double)info.mem_unit / (1024.0)));
                    sys_write(STDOUT,"RAM:\t",5);
                    printbar((float)freeRam,(float)totalRam,10.0f);
                    sys_write(STDOUT," ",1);
                    printfix(totalRam-freeRam,1000,2);
                    sys_write(STDOUT," / ",3);
                    printfix(totalRam,1000,2);
                    sys_write(STDOUT," MiB",4);
                }
                break;
            case 5:
                if (info.totalswap) {
                    int totalSwap = (int)((double)info.totalram * ((double)info.mem_unit / (1024.0)));
                    int freeSwap  = (int)((double)info.freeram  * ((double)info.mem_unit / (1024.0)));
                    sys_write(STDOUT,"Swap:\t",6);
                    printbar((float)freeSwap,(float)totalSwap,10.0f);
                    sys_write(STDOUT," ",1);
                    printfix((totalSwap-freeSwap)/1000,1000,2);
                    sys_write(STDOUT," / ",3);
                    printfix(totalSwap/1000,100,2);
                    sys_write(STDOUT," MiB",4);
                }
                break;
            case 6:
                if (info.uptime) {
                    sys_write(STDOUT,"Uptime:\t",9);
                    printint(info.uptime/60/60);
                    sys_write(STDOUT,"h ",2);
                    printint(info.uptime/60%60);
                    sys_write(STDOUT,"min ",4);
                    printint(info.uptime%60);
                    sys_write(STDOUT,"s",1);
                }
                break;
        }
        sys_write(STDOUT,"\n",1);
    }
    sys_exit(0);
}
