#include "lib/sys.h"
#include "lib/net.h"
#include "lib/str.h"
#include "lib/num.h"
#include "lib/err.h"

#define MAX_LENGTH 512
    
char typedBytes[MAX_LENGTH];
char outBytes[MAX_LENGTH];
char inBytes[MAX_LENGTH];
char currentChat[MAX_LENGTH];
char* username = "PixixIRC";
size_t usernameLength = 8;

int logon(int sock, char* username) {
    sys_write(sock,"CAP LS 302\r\n",12);

    // Send nick
    memcpy(outBytes,"NICK ",5);
    memcpy(outBytes+5,username,usernameLength);
    memcpy(outBytes+5+usernameLength,"\r\n",2);
    outBytes[5+usernameLength+2] = '\0';
    sys_write(sock,outBytes,strlen(outBytes));

    // Send User
    memcpy(outBytes,"USER ",5);
    memcpy(outBytes+5, username, usernameLength);
    memcpy(outBytes+5+usernameLength, " 0 * :", 6);
    memcpy(outBytes+5+usernameLength+6, username, usernameLength);
    memcpy(outBytes+5+usernameLength+6+usernameLength,"\r\n",2);
    outBytes[5+usernameLength+6+usernameLength+2] = '\0';
    sys_write(sock,outBytes,strlen(outBytes));

    sys_write(sock,"CAP END\r\n",9);
    return 0;
}

// A very basic IRC Client
int main(int argc, char *argv[]) {
    char **args = argv;
    int argcount = argc;
    if (argcount < 3) {
        sys_write(STDOUT, "irc <ip> <port> (user)\n", 23);
        sys_exit(1);
    } else if (argcount > 3) {
        username = args[3];
        usernameLength = strlen(username);
    }
    int ip = readip(args[1]);
    short port = readint(args[2]);
    int sock = sys_socket(AF_INET,SOCK_STREAM,0);
    if (sock < 0) printerr(sock);

    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_addr = htonl(ip),
        .sin_port = htons(port)
    };
    
    printerr(sys_connect(sock, &addr, sizeof(addr)));
    sys_write(STDOUT, "Connected to ", 13);
    printip(ip);
    sys_write(STDOUT, "!\n",2);

    // Make socket non-blocking
    int flags = sys_fcntl(sock,F_GETFL,0);
    sys_fcntl(sock, F_SETFL, flags | O_NONBLOCK);
    // Make STDIN non-blocking
    flags = sys_fcntl(STDIN,F_GETFL,0);
    sys_fcntl(STDIN, F_SETFL, flags | O_NONBLOCK);
    
    logon(sock,username);

    while(1) {
        int typedLength = sys_read(STDIN, typedBytes, MAX_LENGTH-3);
        if (typedLength > 0) {
            // Convert newline to CLRF
            if (typedBytes[typedLength - 1] == '\n') {
                typedBytes[typedLength - 1] = '\r';
                typedBytes[typedLength] = '\n';
                typedLength++;
            }
            typedBytes[typedLength] = '\0';

            // Check if command
            if (typedBytes[0] == '.') {
                switch(typedBytes[1]) {
                    // Exit
                    case 'q':
                        sys_close(sock);
                        sys_exit(0);
                        break;
                    // Chat message
                    case 'm':
                        size_t currentChatLen = strlen(currentChat);
                        size_t messageLen = typedLength - 3;
                        size_t totalLen = 8 + currentChatLen + 2 + messageLen;

                        memcpy(outBytes, "PRIVMSG ", 8);
                        memcpy(outBytes + 8, currentChat, currentChatLen);
                        memcpy(outBytes + 8 + currentChatLen, " :", 2);
                        memcpy(outBytes + 8 + currentChatLen + 2, typedBytes + 3, messageLen);
                        outBytes[totalLen] = '\0';

                        sys_write(STDOUT, "-> ",3);
                        sys_write(STDOUT, typedBytes+3, messageLen);
                        sys_write(sock, outBytes, totalLen);
                        break;
                    case 'j':
                        // Remove '.j ' and '\r\n'
                        size_t chatLen = typedLength - 5;
                        memcpy(currentChat, typedBytes + 3, chatLen);
                        currentChat[chatLen] = '\0';

                        sys_write(sock,"JOIN ",5);
                        sys_write(sock,currentChat,strlen(currentChat));
                        sys_write(sock,"\r\n",2);
                        break;
                    case 'c':
                        sys_write(STDOUT,"Currently in ",13);
                        sys_write(STDOUT,currentChat,strlen(currentChat));
                        sys_write(STDOUT,"\n",1);
                        break;
                }
            } else {
                // Raw (for manual IRC stuff)
                sys_write(sock,typedBytes,typedLength);
            }
        } else if (typedLength < 0 && typedLength != -11) {
            sys_write(STDOUT, "STDIN: ", 7);
            printerr(typedLength);
        }

        int inLength = sys_read(sock, inBytes, MAX_LENGTH);
        if (inLength > 0) {
            // Hacky but should suffice
            /*
            if (inBytes[0] == 'P' &&
                inBytes[1] == 'I' &&
                inBytes[2] == 'N' &&
                inBytes[3] == 'G'
            ) {
                inBytes[1] = 'O';
                sys_write(sock,inBytes,strlen(inBytes));
            }*/
            sys_write(STDOUT,inBytes,inLength);
        } else if (inLength < 0 && inLength != -11) {
            sys_write(STDOUT, "SOCKET: ", 8);
            printerr(inLength);
        }
    }
    sys_exit(0);
}