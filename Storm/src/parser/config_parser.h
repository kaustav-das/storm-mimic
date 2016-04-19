/*
 * config_parser.h
 *
 *  Created on: 19-Apr-2016
 *      Author: Kaustav
 */

#ifndef PARSER_CONFIG_PARSER_H_
#define PARSER_CONFIG_PARSER_H_

#include <fstream>

using namespace std;

int* config_parser()
{
	int no_nodes;
	int no_edges;
	int* values = new int[2];

	ifstream infile;
	infile.open("data.config");
	infile >> no_nodes;
	infile >> no_edges;
	infile.close();

	values[0] = no_nodes;
	values[1] = no_edges;

	return values;
}

#endif /* PARSER_CONFIG_PARSER_H_ */
