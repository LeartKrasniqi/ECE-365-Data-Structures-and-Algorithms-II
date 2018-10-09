// Leart Krasniqi
// DSA II - Prof. Sable
// Assignment 1

// This program implements a hash table to create
// a spell-checking program.  A dictionary is loaded
// into the hash table and it is used to check
// an input file provided by the user. 

#include "hash.h"
#include <iostream>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

int main()
{
	string dicName, inFile, outFile, word, line;
	hashTable *dictionary = new hashTable(50000);

	cout << "Enter the name of the dictionary: ";
	cin >> dicName;

	clock_t start = clock();
	ifstream dicFile(dicName.c_str()); 

	// This loads the dictionary into the hash table 
	if (dicFile.is_open())
	{
		while (!(dicFile.eof()))
		{
			getline(dicFile, word);
			for (int i = 0; i < word.length(); i++)
				word[i] = tolower(word[i]);				// Make every word lowercase before we put them into the hash table 
			
			dictionary -> insert(word);
		}

		dicFile.close();
	}
	
	clock_t end = clock();
	double time_elap = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << time_elap << endl;


	cout << "Enter name of input file: ";
	cin >> inFile;
	cout << "Enter name of output file: ";
	cin >> outFile;

	start = clock();
	ifstream input(inFile.c_str());
	ofstream output(outFile.c_str());

	int numLine = 1;	
	bool ignore = false;


	if (input.is_open())
	{
		string buf = "";
		while (!input.eof())
		{
			getline(input, line);
			transform(line.begin(), line.end(), line.begin(), ::tolower);	// Converts string to lowercase
			for (int i = 0; i < line.length(); i++)
			{
				int a = line[i];

				while ((a >= '0' and a <= '9') or (a >= 'a' and a <= 'z') or (a == '-') or (a == 39))
				{
					buf.push_back(line[i]);				// If valid character, put into buffer
					if ((a >= '0' and a <= '9'))
						ignore = true;

					if (i != (line.length() - 1))
					{
						i++;
						a = line[i];
					} else
						break;
				}
				
				if (buf == "")
					ignore = true;

				if (!ignore)
				{
					if (buf.length() > 20)
						output << "Long word at line " << numLine << ", starts: " << buf.substr(0,20) << endl;

					else if (!(dictionary -> contains(buf)))
						output << "Unknown word at line " << numLine << ": " << buf << endl;
				}

				ignore = false;		// Reset ignore variable and buffer
				buf = "";
			}

			numLine++;
		}
	}

	end = clock();
	time_elap = ((double)(end - start)) / CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to check document: " << time_elap << endl;

	input.close();
	output.close();

	return 0;
}
