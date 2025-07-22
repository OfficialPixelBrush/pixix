// Structures and syscalls for networking
#ifndef NET_H
#define NET_H
enum socket_protocol {
    AF_INET = 2
};

enum socket_type {
    SOCK_STREAM = 1,
    SOCK_DGRAM = 2,
    SOCK_RAW = 3
};

enum ipproto {
    IPPROTO_ICMP = 1,
    IPPROTO_UDP = 17
};

enum icmp_type {
    ICMP_ECHOREPLY = 0,
    ICMP_DEST_UNREACH = 3,
    ICMP_REDIRECT = 5,
    ICMP_ECHO = 8,
    ICMP_TIME_EXCEEDED = 11
};

struct sockaddr_in {
    unsigned short  sin_family;
    unsigned short  sin_port; 
    unsigned int    sin_addr;
    unsigned char   sin_zero[8];
};

struct icmphdr {
    unsigned char  type;
    unsigned char  code;
    unsigned short checksum;
    union {
        struct {
            unsigned short id;
            unsigned short sequence;
        } echo;
        unsigned int   gateway;
        struct {
            unsigned short __unused;
            unsigned short mtu;
        } frag;
    } un;
};

struct sockaddr {
    unsigned short sa_family;  // address family, e.g., AF_INET
    char sa_data[14];          // address data (protocol-specific)
};

static inline unsigned short htons(unsigned short x) {
    return (x << 8) | (x >> 8);
}
static inline unsigned int htonl(unsigned int x) {
    return ((x & 0x000000FFU) << 24) |
           ((x & 0x0000FF00U) << 8)  |
           ((x & 0x00FF0000U) >> 8)  |
           ((x & 0xFF000000U) >> 24);
}


int sys_socket(int family, int type, int protocol);
int sys_bind(int fd, const void *addr, int addrlen);
int sys_connect(int fd, struct sockaddr_in *uservaddr, int addrlen);
int sys_setsockopt(int sockfd, int level, int optname, const void *optval, int optlen);
int sys_sendto(int fd, const void *buf, unsigned int len, int flags, const struct sockaddr *addr, int addrlen);
int sys_recvfrom(int fd, void *buf, unsigned int size, int flags, struct sockaddr *addr, int *addrlen);
#endif