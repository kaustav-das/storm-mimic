/*
 * client.h
 *
 *  Created on: 08-May-2016
 *      Author: Kaustav
 */

#ifndef SOCKET_CLIENT_H_
#define SOCKET_CLIENT_H_



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;

void c_error(const char *msg)
{
	//    perror(msg);
	cout<<msg;
    exit(0);
}

void *client_func(void *p_no)
{
	cout<<"client : thread started\n";
	int argc = 3;

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    server = gethostbyname("127.0.0.1"); //Not working; exiting

    char buffer[256] = "testmessage";
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", "myhost");
       cout<<"client : wrong argument";
       exit(0);
    }
    portno = (intptr_t)p_no;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//    int enable = 1;
//    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));
    if (sockfd < 0) {
        c_error("ERROR opening socket");
        cout<<"client : ERROR opening socket\n";
    }
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        cout<<"client : ERROR, no such host\n";
        exit(0);
    }
    else
    	cout<<"client : Socket opened\n";

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        c_error("ERROR connecting");
//    bzero(buffer,256);
//    fgets(buffer,255,stdin);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0)
         c_error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd, buffer, 255);
    if (n < 0)
         c_error("ERROR reading from socket");
    printf("%s\n", buffer);
    close(sockfd);
}

#endif /* SOCKET_CLIENT_H_ */
