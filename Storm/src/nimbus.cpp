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
	int* values = config_parser();
	int no_nodes = values[0];
	int no_edges = values[1];

	int** adj_matrix = dag_parser(no_nodes, no_edges);

	int i;
	cout<< "Hello";
	cin>>i;
	cout<<i;

	int portno = 67838;
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

//	server_func(portno);
//	client_func(portno);

	/*for (int i = 0; i < no_nodes; i++)
	{
		for (int j = 0; j < no_nodes; j++)
		{
			cout << adj_matrix[i][j];
		}
		cout<<endl;
	}*/
	return 0;
}
