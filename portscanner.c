// code tutorial here: http://www.binarytides.com/tcp-connect-port-scanner-c-code-linux-sockets/
// understanding syn-syn-ack: http://www.inetdaemon.com/tutorials/internet/tcp/3-way_handshake.shtml

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){

    struct hostent *host;
    int err, i, sock, start, end;
    char hostname[100];
    struct sockaddr_in sa;

    printf("Enter hostname or IP:");
    gets(hostname);

    printf("\n");

    printf("Enter start port number: ");
    scanf("%d", &start);

    printf("\n");

    printf("Enter end port number: ");
    scanf("%d", &end);

    strncpy((char*)&sa, "", sizeof sa);
    sa.sin_family = AF_INET;

    if(isdigit(hostname[0])){
        sa.sin_addr.s_addr = inet_addr(hostname);  
    }
    else if (  (host = gethostbyname(hostname)) != 0){
        strncpy((char*)&sa.sin_addr, (char*) host->h_addr, sizeof sa.sin_addr);
    }
    else {
        herror(hostname);
        exit(2);
    }

    for(i = start;  i <= end; i++){
        printf("Scanning port %i\n",i);

        sa.sin_port = htons(i);
        sock = socket(AF_INET, SOCK_STREAM, 0);

        if(socket < 0){
            exit(1);    
        }

        err = connect(sock, (struct sockaddr*)&sa, sizeof sa);

        if (err < 0){
            fflush(stdout);
        }
        else {
            printf("Port %i is open\n", i);
        }
        close(sock);
    }
    fflush(stdout);
    return 0;
}
