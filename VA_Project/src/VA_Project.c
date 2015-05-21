/*
 ============================================================================
 Name        : VA_Project.c
 Author      : JP
 Version     :
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <wiringPi.h>

#define PORTNUMBER 2345
#define	IPSERVER "192.168.2.100"

int main(void) {

    int mysocket, n;
    struct sockaddr_in server_address;

    char buffer[256];

    wiringPiSetup();
    pinMode(7, OUTPUT);
	pinMode(0, INPUT);
//wasd

    mysocket = socket(AF_INET, SOCK_STREAM, 0); //Create Socket

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(IPSERVER);
    server_address.sin_port = htons(PORTNUMBER);

    int conn_err = connect(mysocket,(struct sockaddr *) &server_address,sizeof(server_address));

    if(conn_err < 0)
    	printf("Connection error");

    strcpy(buffer, "test_string\n");

    n = send(mysocket, buffer, strlen(buffer), 0);
    if(n < 0)
		printf("Send error\n");

    while(strcmp(buffer, "CLOSE\n") != 0) {
		memset(buffer, 0, sizeof(buffer));
		n = recv(mysocket, buffer, 256, 0);
		if(n == 0)
			printf("recieve error\n");

		printf("%s\n",buffer);

		if(strcmp(buffer, "ON\n") == 0)
			digitalWrite(7, HIGH);
		if(strcmp(buffer, "OFF\n") == 0)
			digitalWrite(7, LOW);
    }

    close(mysocket);

    return EXIT_SUCCESS;
}
