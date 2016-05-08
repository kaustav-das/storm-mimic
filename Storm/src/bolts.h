/*
 * bolts.h
 *
 *  Created on: 08-May-2016
 *      Author: Kaustav
 */

#ifndef BOLTS_H_
#define BOLTS_H_

#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "meta_message.h"

using namespace std;

void *func1_init(void *m_msg);
void func1_client(int to_port, int a);
void func1_server(int from_port, int to_port);
void func1_handle_input(int to_port, char buffer[4096]);
int func1(int a);

void *func2_init(void *m_msg);
void func2_server(int from_port);
void func2_handle_input(char buffer[4096]);
int func2(int a);

void *func1_init(void *m_msg)
{
	meta_message *meta;
	meta = (meta_message *)m_msg;

	int from_port = meta->from_port;
	int to_port = meta->to_port;

	func1_server(from_port, to_port);

}

void *func2_init(void *m_msg)
{
	meta_message *meta;
	meta = (meta_message *)m_msg;

	int from_port = meta->from_port;

	func2_server(from_port);

}

void func1_client(int to_port, int a)
{

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	server = gethostbyname("localhost");

	char buffer[4096];
//	itoa (a,buffer,10);
	snprintf (buffer, sizeof(buffer), "%d",a);
	portno = to_port;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
		c_error("ERROR opening socket");
		cout<<"client : ERROR opening socket\n";
	}
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		cout<<"client : ERROR, no such host\n";
		cout<<portno;
		exit(0);
	}
//	else
//		cout<<"client : Socket opened\n";

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		 (char *)&serv_addr.sin_addr.s_addr,
		 server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		c_error("ERROR connecting");

	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0)
		 c_error("ERROR writing to socket");
	bzero(buffer,4096);
	close(sockfd);
}

void func1_server(int from_port, int to_port)
{

	 int sockfd, newsockfd, portno;
	 socklen_t clilen;
	 char buffer[4096];
	 struct sockaddr_in serv_addr, cli_addr;
	 int n;
	 // create a socket
	 // socket(int domain, int type, int protocol)
	 sockfd =  socket(AF_INET, SOCK_STREAM, 0);
	 int enable = 1;
	 setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

	 if (sockfd < 0)
		s_error("ERROR opening socket");

	 // clear address structure
	 bzero((char *) &serv_addr, sizeof(serv_addr));

	 portno = from_port;

	 //setup the host_addr structure for use in bind call
	 // server byte order
	 serv_addr.sin_family = AF_INET;

	 // automatically be filled with current host's IP address
	 serv_addr.sin_addr.s_addr = INADDR_ANY;

	 // convert short integer value for port must be converted into network byte order
	 serv_addr.sin_port = htons(portno);

	 // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
	 // bind() passes file descriptor, the address structure,
	 // and the length of the address structure
	 // This bind() call will bind  the socket to the current IP address on port, portno
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0)
			  s_error("ERROR on binding");
//	 else
//		 cout<<"server : Socket bound\n";

	 // This listen() call tells the socket to listen to the incoming connections.
	 // The listen() function places all incoming connection into a backlog queue
	 // until accept() call accepts the connection.
	 // Here, we set the maximum size for the backlog queue to 5.

	 while(1)
	 {
		 listen(sockfd,5);

		 // The accept() call actually accepts an incoming connection
		 clilen = sizeof(cli_addr);

		 // This accept() function will write the connecting client's address info
		 // into the the address structure and the size of that structure is clilen.
		 // The accept() returns a new socket file descriptor for the accepted connection.
		 // So, the original socket file descriptor can continue to be used
		 // for accepting new connections while the new socker file descriptor is used for
		 // communicating with the connected client.
		 newsockfd = accept(sockfd,
					 (struct sockaddr *) &cli_addr, &clilen);
		 if (newsockfd < 0)
			  s_error("ERROR on accept");

		 printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
		 string ip_ad(inet_ntoa(cli_addr.sin_addr));
		 int prt = (intptr_t) ntohs(cli_addr.sin_port);
		 stringstream ss;
		 ss << prt;
		 string str = ss.str();
		 write_tofile("server: got connection from" + ip_ad + " port " + str + "\n");

		 bzero(buffer,4096);

		 n = read(newsockfd,buffer,4095);
		 if (n < 0) s_error("ERROR reading from socket");


		 string tmp(buffer);
		 cout<<"Input1: " + tmp + "\n";

		 close(newsockfd);

		 func1_handle_input(to_port, buffer);
	 }
	 close(sockfd);
}

void func1_handle_input(int to_port, char buffer[4096])
{
	//do computation on buffer. check if exists else save in vector

	int a = atoi(buffer);
	a = func1(a);
	func1_client(to_port, a);
}

void func2_server(int from_port)
{

	 int sockfd, newsockfd, portno;
	 socklen_t clilen;
	 char buffer[4096];
	 struct sockaddr_in serv_addr, cli_addr;
	 int n;
	 // create a socket
	 // socket(int domain, int type, int protocol)
	 sockfd =  socket(AF_INET, SOCK_STREAM, 0);
	 int enable = 1;
	 setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

	 if (sockfd < 0)
		s_error("ERROR opening socket");

	 // clear address structure
	 bzero((char *) &serv_addr, sizeof(serv_addr));

	 portno = from_port;

	 //setup the host_addr structure for use in bind call
	 // server byte order
	 serv_addr.sin_family = AF_INET;

	 // automatically be filled with current host's IP address
	 serv_addr.sin_addr.s_addr = INADDR_ANY;

	 // convert short integer value for port must be converted into network byte order
	 serv_addr.sin_port = htons(portno);

	 // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
	 // bind() passes file descriptor, the address structure,
	 // and the length of the address structure
	 // This bind() call will bind  the socket to the current IP address on port, portno
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
			  sizeof(serv_addr)) < 0)
			  s_error("ERROR on binding");
//	 else
//		 cout<<"server : Socket bound\n";

	 // This listen() call tells the socket to listen to the incoming connections.
	 // The listen() function places all incoming connection into a backlog queue
	 // until accept() call accepts the connection.
	 // Here, we set the maximum size for the backlog queue to 5.

	 while(1)
	 {
		 listen(sockfd,5);

		 // The accept() call actually accepts an incoming connection
		 clilen = sizeof(cli_addr);

		 // This accept() function will write the connecting client's address info
		 // into the the address structure and the size of that structure is clilen.
		 // The accept() returns a new socket file descriptor for the accepted connection.
		 // So, the original socket file descriptor can continue to be used
		 // for accepting new connections while the new socker file descriptor is used for
		 // communicating with the connected client.
		 newsockfd = accept(sockfd,
					 (struct sockaddr *) &cli_addr, &clilen);
		 if (newsockfd < 0)
			  s_error("ERROR on accept");

		 printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));
		 string ip_ad(inet_ntoa(cli_addr.sin_addr));
		 int prt = (intptr_t) ntohs(cli_addr.sin_port);
		 stringstream ss;
		 ss << prt;
		 string str = ss.str();
		 write_tofile("server: got connection from" + ip_ad + " port " + str + "\n");

		 bzero(buffer,4096);

		 n = read(newsockfd,buffer,4095);
		 if (n < 0) s_error("ERROR reading from socket");

		 close(newsockfd);

		 func2_handle_input(buffer);
	 }
	 close(sockfd);
}

void func2_handle_input(char buffer[4096])
{
	//do computation on buffer. check if exists else save in vector
	string tmp(buffer);
	cout<<"Input2: " + tmp + "\n";
	int a = atoi(buffer);
	a = func2(a);
	stringstream ss;
	 ss << a;
	 string str = ss.str();
	cout<<"Output: " + str + "\n";
}

int func1(int a)
{
	a++;
	return a;
}

int func2(int a)
{
	a = a + 2;
	return a;
}

#endif /* BOLTS_H_ */
