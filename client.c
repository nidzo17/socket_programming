#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

int main() {
    int socket1, socket2;
    int PORT1 = 50007;
    int PORT2 = 53007;
    struct sockaddr_in serv_addr1, serv_addr2; 
    char buffer[1024] = {0};
    
    if ((socket1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "ERROR: Creating 1st socket failed.\n");
        return 1;
    } 
    if ((socket2 = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        fprintf(stderr, "ERROR: Creating 2nd socket failed.\n");
        return 1;
    } 
    
    memset(&serv_addr1, 0, sizeof(serv_addr1)); 
    memset(&serv_addr2, 0, sizeof(serv_addr2)); 
	
    serv_addr1.sin_family = AF_INET;
    serv_addr1.sin_port = htons(PORT1); 
    serv_addr2.sin_family = AF_INET;
    serv_addr2.sin_port = htons(PORT2); 
    
    if ((inet_pton(AF_INET, "127.0.0.1", &serv_addr1.sin_addr) <= 0) || \
		(inet_pton(AF_INET, "127.0.0.1", &serv_addr2.sin_addr) <= 0)) {
        fprintf(stderr, "ERROR: Converting addresses from text to binary form failed .\n");
        return 1;
    } 

    if (connect(socket1, (struct sockaddr *)&serv_addr1, sizeof(serv_addr1)) < 0) {
       fprintf(stderr, "ERROR: 1st socket connection failed.\n");
       return 1;
    } 

    if (connect(socket2, (struct sockaddr *)&serv_addr2, sizeof(serv_addr2)) < 0) {
       fprintf(stderr, "ERROR: 2nd socket connection failed.\n");
       return 1;
    } 
    
    printf("> ");
    fgets(buffer, 1024, stdin);
    
    printf("Sending to 1st socket: %s\n", buffer);
    if (write(socket1, buffer, sizeof(buffer)) < 0) {
         fprintf(stderr, "ERROR: Writing to socket failed.\n");
         return 1;
    }
    
	memset(&buffer, 0, sizeof(buffer));
    while(1) {
	    if (read(socket2, buffer, sizeof(buffer) - 1) <= 0)
            break;
        printf("Received from 2nd socket: %s\n", buffer);
        memset(&buffer, 0, sizeof(buffer));
	}
	
    close(socket1);
    close(socket2);
	
    return 0;
}

