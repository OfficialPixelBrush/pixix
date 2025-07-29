#include "lib/sys.h"
#include "lib/err.h"
#include "lib/str.h"
#include "lib/net.h"

int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    int port = 80;
    if (argcount < 2) {
        sys_write(STDOUT, "ping <ip> (port)\n", 17);
        sys_exit(1);
    } else if (argcount >= 3) {
        port = readint(args[2]);
    }
    int ip = readip(args[1]);
    int sock = sys_socket(AF_INET,SOCK_STREAM,0);
    if (sock < 0) printerr(sock);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = htonl(ip),
        .sin_port = htons(port)
    };
    
    sys_write(STDOUT, "Connecting to ", 14);
    printip(ip);
    sys_write(STDOUT, ":",1);
    printint(port);
    sys_write(STDOUT, "...\n",4);
    printerr(sys_connect(sock, &addr, sizeof(addr)));
    sys_write(STDOUT, "Connected to ", 13);
    printip(ip);
    sys_write(STDOUT, ":",1);
    printint(port);
    sys_write(STDOUT, "!\n",2);

    char *request = "GET / HTTP/1.1\r\nHost: 1.1.1.1\r\n\r\n";
    sys_write(sock, request, strlen(request));
    sys_write(STDOUT, "Sent!\n", 6);
    
    char buf[0];
    int len = sys_read(sock,buf,sizeof(buf));
    
    if (len < 0) {
        printerr(len);
    } else {
        sys_write(STDOUT, "IP is reachable!\n", 17);
    }

    sys_close(sock);
    sys_exit(0);
}