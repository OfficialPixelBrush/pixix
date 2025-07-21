#include "lib/sys.h"
#include "lib/lib.h"
#include "lib/net.h"

int main() {
    sys_write(STDOUT,"Started!\n",9);
    int sock = sys_socket(AF_INET,SOCK_STREAM,0);
    if (sock < 0) errprint(sock);
    sys_write(STDOUT,"Socket gotten!\n",15);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = htonl(0x55D7CBAF), // 85.215.203.175
        .sin_port = htons(80)
    };
    
    sys_write(STDOUT, "Connecting...\n", 14);
    errprint(sys_connect(sock, &addr, sizeof(addr)));
    sys_write(STDOUT, "Connected!\n", 11);

    char *request = "GET / HTTP/1.1\r\nHost: 85.215.203.175\r\n\r\n";
    sys_write(sock, request, strlen(request));
    sys_write(STDOUT, "Sent!\n", 6);
    
    char buf[0];
    int len = sys_read(sock,buf,sizeof(buf));
    //printint(len);
    if (len < 0) {
        errprint(len);
    } else {
        sys_write(STDOUT, "Server is reachable!\n", 21);
    }

    sys_close(sock);
    sys_exit(0);
}