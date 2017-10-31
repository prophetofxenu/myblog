#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_IP "45.55.196.222"
#define PORT 9002

int main(void) {

    int command = -1;
    puts("What would you like to do?");
    while(command < 0 || command > 3) {
        puts("0: Change the blog's title");
        puts("1: Change the blog's message of the day");
        puts("2: Change the blog's background color");
        puts("3: Make a new post");
        scanf("%d", &command);
        if(command < 0 || command > 3) {
            puts("Invalid command");
        }
    }

    int networkSocket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    int connectionStatus = connect(networkSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(connectionStatus < 0) {
        puts("There was an error connecting to the server");
        return 0;
    }

    send(networkSocket, &command, sizeof(command), 0);

}