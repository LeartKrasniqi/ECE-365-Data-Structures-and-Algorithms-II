// Leart Krasniqi
// DSA II - Prof. Sable
// Assignment 3

// This file defines the functions of the
// graph class.

#include "graph.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#define VERTICES 512

// Constructor for graph class
graph::graph()
{
	size = 0;
	mapping = new hashTable(VERTICES);
}

// Inserts node(s) into the graph 
void graph::insert(const std::string &input)
{
	std::string line, name1, name2, weight;
	node *node1, *node2;
	edge e;

	// Split up command into proper tokens
	std::istringstream iss(input);
	iss >> name1 >> name2 >> weight;

	// First node
	if (mapping -> contains(name1))
		node1 = (node *)mapping -> getPointer(name1);
	else
	{
		node1 = new node;
		node1 -> id = name1;
		node1 -> visited = false;
		node1 -> distance = INT_MAX;
		nodeList.push_back(node1);
		mapping -> insert(name1, node1);
		size++;
	}

	// Second node
	if (mapping -> contains(name2))
		node2 = (node *)mapping -> getPointer(name2);
	else
	{
		node2 = new node;
		node2 -> id = name2;
		node2 -> visited = false;
		node2 -> distance = INT_MAX;
		nodeList.push_back(node2);
		mapping -> insert(name2, node2);
		size++;
	}

	// Inserting the edge that connects the nodes
	e.cost = stoi(weight);
	e.next = node2;
	node1 -> adjList.push_back(e);

}

// Checks to see if graph contains node with
// specified id.
// Returns true if graph does contain node
bool graph::contains(const std::string &id)
{
	return (mapping -> contains(id));
}

// Performs Dijkstra's Algorithm on a starting node
void graph::dijkstra(const std::string &id)
{
	heap dijkstraHeap(size);

	// Putting the starting node in both the path list and the heap
	node *start = (node *) mapping -> getPointer(id);
	start -> distance = 0;
	start -> path.push_back(id);
	dijkstraHeap.insert(id, start -> distance, start);

	
	// Insert the remaining nodes into the heap
	for (std::list<node *>::const_iterator iter = nodeList.begin(); iter != nodeList.end(); iter++)
	{
		if ((*iter) -> id != id)
			dijkstraHeap.insert((*iter) -> id, (*iter) -> distance, *iter);
	}


	// Performing the actual algorithm
	for (int i = 0; i < size; i++)
	{
		node *temp;
		dijkstraHeap.deleteMin(NULL, NULL, &temp);
		for (std::list<edge>::const_iterator iter = temp->adjList.begin(); (iter != temp->adjList.end()) && (temp -> distance != INT_MAX); iter++)
		{
			// Implementation inspired by Figure 9.31 in our textbook
			if ((iter->cost + temp->distance) < (iter->next->distance)	&&	(iter->next->visited == false))
			{
				// Update the distance and the heap
				iter->next->distance = (iter->cost + temp->distance);
				dijkstraHeap.setKey(iter->next->id, iter->next->distance);

				// Update the path list 
				iter->next->path = temp->path;
				iter->next->path.push_back(iter->next->id);
			}
		}

		temp->visited = true;
	}
}


// Outputs the paths from nodes to a user specified file
void graph::output(const std::string &file)
{
	std::ofstream outfile;
	outfile.open(file);

	for(std::list<node *>::const_iterator iter = nodeList.begin(); iter != nodeList.end(); iter++)
	{
		if ((*iter)->distance == INT_MAX)
			outfile << (*iter)->id << ": NO PATH" << std::endl;
		else
		{
			outfile << (*iter)->id << ": " << (*iter)->distance << " [";

			for (std::list<std::string>::const_iterator iter2 = (*iter)->path.begin(); iter2 != --(*iter)->path.end(); iter2++)
				outfile << *iter2 << ", ";

			outfile << (*iter)->path.back() << "]" << std::endl;

		} 
	}

	outfile.close();
}

