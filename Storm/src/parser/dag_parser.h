/*
 * dag_parser.h
 *
 *  Created on: 19-Apr-2016
 *      Author: Kaustav
 */

#ifndef PARSER_DAG_PARSER_H_
#define PARSER_DAG_PARSER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

int** dag_parser(int no_nodes, int no_edges) {

	FILE * fp;

	int** adj_matrix = new int*[no_nodes];
	for (int i = 0; i < no_nodes; i++)
	{
		adj_matrix[i] = new int[no_nodes];
		for (int j = 0; j < no_nodes; j++)
		{
			adj_matrix[i][j] = 0;
		}
	}

	fp = fopen("data.dag", "r");

	for (int i = 0; i < no_edges; i++)
	{
		int parent = 0, child = 0;
		fscanf(fp, "%d %d", &parent, &child);
		adj_matrix[parent][child] = 1;
	}

	fclose(fp);

	return adj_matrix;
}

#endif /* PARSER_DAG_PARSER_H_ */
