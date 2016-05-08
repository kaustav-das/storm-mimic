/*
 * server.h
 *
 *  Created on: 08-May-2016
 *      Author: Kaustav
 */

#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

void write_tofile(string str)
{
	ofstream outfile;
	outfile.open("s_file.dat", ios::app);

	// write inputted data into the file.
	outfile << str << endl;

	// close the opened file.
	outfile.close();
}

void s_error(const char *msg)
{
//    perror(msg);
	cout<<msg;
    exit(1);
}

void *server_func(void *p_no)
{
	cout<<"server : thread started\n";
	int argc = 2;

     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     // create a socket
     // socket(int domain, int type, int protocol)
     sockfd =  socket(AF_INET, SOCK_STREAM, 0);
     int enable = 1;
     setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

     if (sockfd < 0)
        s_error("ERROR opening socket");

     // clear address structure
     bzero((char *) &serv_addr, sizeof(serv_addr));

     portno = (intptr_t)p_no;

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
     else
    	 cout<<"server : Socket bound\n";

     // This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a backlog queue
     // until accept() call accepts the connection.
     // Here, we set the maximum size for the backlog queue to 5.
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


     // This send() function sends the 13 bytes of the string to the new socket
     send(newsockfd, "Message Received\n", 2048, 0);

     bzero(buffer,256);

     n = read(newsockfd,buffer,255);
     if (n < 0) s_error("ERROR reading from socket");
     write_tofile(buffer);

     close(newsockfd);
     close(sockfd);
}



#endif /* SOCKET_SERVER_H_ */
