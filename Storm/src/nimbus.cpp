/*
 * nimbus.cpp
 *
 *  Created on: 19-Apr-2016
 *      Author: Kaustav
 */

#include <iostream>
#include <cstdio>
#include <pthread.h>

#include "parser/config_parser.h"
#include "parser/dag_parser.h"
#include "socket/server.h"
#include "socket/client.h"

using namespace std;

int main()
{

	/*int* values = config_parser();
	int no_nodes = values[0];
	int no_edges = values[1];

	int** adj_matrix = dag_parser(no_nodes, no_edges);

	int portno = 55679;
	int rc;
	pthread_t threadID1, threadID2;

	rc = pthread_create(&threadID1, NULL, &server_func, (void *)portno);
	if (rc){
	 cout << "Error:unable to create thread," << rc << endl;
	 exit(-1);
	}

	rc = pthread_create(&threadID2, NULL, &client_func, (void *)portno);
	if (rc){
	 cout << "Error:unable to create thread," << rc << endl;
	 exit(-1);
	}

	pthread_join(threadID2, NULL);*/
	return 0;
}
