// Leart Krasniqi
// DSA II - Prof. Sable
// Assignment 3

// This header file defines the graph class

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <list>
#include "heap.h"

class graph
{
	public:

		// Constructor that initializes Hash Table for
		// the graph
		graph();


		// Inserts node(s) into the graph 
		void insert(const std::string &input);

		
		// Checks to see if graph contains node with
		// specified id.
		// Returns true if graph does contain node
		bool contains(const std::string &id);

		
		// Performs Dijkstra's Algorithm on a starting node
		void dijkstra(const std::string &id);


		// Outputs the paths from nodes to a user specified file
		void output(const std::string &file);


	private:

		int size;
		class node;

		class edge
		{
			public:
				int cost;	// weight of the edge
				node *next;	// Points to node next node 
		};
		
		class node
		{
			public:
				std::string id;
				std::list<edge> adjList;		// Adjacency List implementation
				std::list<std::string> path;	// List to store the path taken, if any
				bool visited;
				int distance;	// Distance from starting node to current node


		}; 

		std::list<node *> nodeList;
		hashTable *mapping;
};

#endif
