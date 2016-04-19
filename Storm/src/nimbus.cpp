/*
 * nimbus.cpp
 *
 *  Created on: 19-Apr-2016
 *      Author: Kaustav
 */

#include <iostream>
#include <cstdio>
#include "config_parser.h"
#include "dag_parser.h"

using namespace std;

int main()
{
	int* values = config_parser();
	int no_nodes = values[0];
	int no_edges = values[1];

	int** adj_matrix = dag_parser(no_nodes, no_edges);

	cout<<"Hello test";

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
