/*
 * nimbus.cpp
 *
 *  Created on: 19-Apr-2016
 *      Author: Kaustav
 */

#include <iostream>
#include <cstdio>
#include <pthread.h>
#include <cstdlib>

#include "parser/config_parser.h"
#include "parser/dag_parser.h"
#include "socket/server.h"
#include "socket/client.h"
#include "bolts.h"
#include "spout.h"
#include "meta_message.h"

using namespace std;

int main()
{
	meta_message spout, bolt1, bolt2;

	spout.from_port = 0;
	spout.to_port = 21010;

	bolt1.from_port = 21010;
	bolt1.to_port = 21000;

	bolt2.from_port = 21000;
	bolt2.to_port = 21020;

	int rc;
	pthread_t thread_spout, thread_bolt1, thread_bolt2;

	rc = pthread_create(&thread_bolt2, NULL, &func2_init, (void *)&bolt2);
	if (rc){
	 cout << "Error:unable to create thread," << rc << endl;
	 exit(-1);
	}

	rc = pthread_create(&thread_bolt1, NULL, &func1_init, (void *)&bolt1);
	if (rc){
	 cout << "Error:unable to create thread," << rc << endl;
	 exit(-1);
	}

	rc = pthread_create(&thread_spout, NULL, &spout_init, (void *)&spout);
	if (rc){
	 cout << "Error:unable to create thread," << rc << endl;
	 exit(-1);
	}

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
	}*/

	pthread_join(thread_spout, NULL);
	return 0;
}
