/*
 * spout.h
 *
 *  Created on: 08-May-2016
 *      Author: Kaustav
 */

#ifndef SPOUT_H_
#define SPOUT_H_


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

void *spout_init(void *m_msg)
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	server = gethostbyname("localhost");

	meta_message *meta;
	meta = (meta_message *)m_msg;

	portno = meta->to_port;

	int ck = 0;

	while( ck < 2)
	{
		srand (time(NULL));
		int r = rand() % 100;
//		stringstream ss;
//		ss << r;
//		string str = ss.str();
		char buffer[4096];
//		itoa (r,buffer,10);
		snprintf (buffer, sizeof(buffer), "%d",r);

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
//		else
//			cout<<"client : Socket opened\n";

		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		bcopy((char *)server->h_addr,
			 (char *)&serv_addr.sin_addr.s_addr,
			 server->h_length);
		serv_addr.sin_port = htons(portno);
		if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
			c_error("ERROR connecting");

		string tmp(buffer);
		cout<<"Input: " + tmp + "\n";

		n = write(sockfd, buffer, strlen(buffer));
		if (n < 0)
			 c_error("ERROR writing to socket");
		bzero(buffer,256);
		close(sockfd);

		ck++;
		sleep(5);
	}
}


#endif /* SPOUT_H_ */
