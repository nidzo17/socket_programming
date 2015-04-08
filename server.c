#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main() {
    int listen_fd1, listen_fd2, connection_fd1, connection_fd2;
    int PORT1 = 50007;
    int PORT2 = 53007;
    struct sockaddr_in serv_addr1, serv_addr2, client_addr; 
    socklen_t client_length;
    char buffer[1024] = {0};
	
    // SOCKET 1
    listen_fd1 = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr1, 0, sizeof(serv_addr1));
	
    serv_addr1.sin_family = AF_INET;
    serv_addr1.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr1.sin_port = htons(PORT1);
    
    bind(listen_fd1, (struct sockaddr*)&serv_addr1, sizeof(serv_addr1)); 
    listen(listen_fd1, 1); 
    
    // SOCKET 2
    listen_fd2 = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr2, 0, sizeof(serv_addr2));
    
    serv_addr2.sin_family = AF_INET;
    serv_addr2.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr2.sin_port = htons(PORT2);
    
    bind(listen_fd2, (struct sockaddr*)&serv_addr2, sizeof(serv_addr2)); 
    listen(listen_fd2, 1); 
	
    client_length = sizeof(client_addr);
	
    while(1) {
        connection_fd1 = accept(listen_fd1, (struct sockaddr*) &client_addr, &client_length); 
	connection_fd2 = accept(listen_fd2, (struct sockaddr*) &client_addr, &client_length); 
	if (read(connection_fd1, buffer, sizeof(buffer) - 1) < 0)
	    break;
	printf("Received from 1st socket: %s\n", buffer);
		
	printf("Sending to 2nd socket: %s\n", buffer);
	if (write(connection_fd2, buffer, strlen(buffer)) < 0) {
	    fprintf(stderr, "ERROR: Writing to socket failed.\n");
	    return 1;
	}
	
        memset(&buffer, 0, sizeof(buffer)); 
	close(connection_fd1);
	close(connection_fd2);
	sleep(1);
    }	
    return 0;
}

