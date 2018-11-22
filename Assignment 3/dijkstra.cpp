// Leart Krasniqi
// DSA II - Prof. Sable
// Assignment 3

// This program prompts a user to input a set of vertices
// and edges with certain weights.  The program then 
// implements Dijkstra Algorithm to find the shortest
// path from a user-specified first node to all remaining 
// vertices.  The paths are outputted to a specified 
// output file in a specific format.

#include "graph.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>

int main()
{
	std::string fin, fout, line, vertex;
	graph g;


	std::cout << "Enter name of graph file: ";
	std::cin >> fin;

	std::ifstream input(fin.c_str());

	// Inserts the data into the graph
	if (input.is_open())
	{
		while (getline(input, line))
			g.insert(line);

		input.close();
	}

	// Prompts user for valid vertex 
	do 
	{
		std::cout << "Enter a valid vertex id for the starting vertex: ";
		std::cin >> vertex;

	} while (g.contains(vertex) == false);


	// Performs the algorithm and measures time elapsed
	clock_t t1 = clock();
	g.dijkstra(vertex);
	clock_t t2 = clock();

	double diff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;
	std::cout << "Total time (in seconds) to apply Dijkstra's algortihm: " << diff << std::endl;


	// Outputs paths to user specified file
	std::cout << "Enter name of outpule file: ";
	std::cin >> fout;
	g.output(fout);

	return 0;

}
