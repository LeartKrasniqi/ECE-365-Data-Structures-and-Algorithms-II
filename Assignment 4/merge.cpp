// Leart Krasniqi
// DSA 2
// Prof. Sable
// Assignment # 4

// This program implements Dynamic Programming to solve 
// a problem from the 1998 regional ACM Programming Contest.
// A file with blocks of strings is loaded with blocks of
// three strings and the program checks to see if the third
// string is a valid merge of the first two.

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

// Global array to hold all possible merges
int arr[1001][1001];

int main()
{
	string in, out, A, B, C;

	cout << "Enter name of input file: ";
	cin >> in;
	cout << "Enter name of output file: ";
	cin >> out;

	ifstream fin(in);
	ofstream fout(out);

	// Ensure input file is open
	if (fin.is_open())
	{
		// Put each line into respective string
		while (getline(fin, A) && getline(fin, B) && getline(fin, C))
		{
			// If C is not the same size as A + B, it cannnot be a merge
			if ((A.length() + B.length()) != C.length())
			{
				fout << "*** NOT A MERGE ***" << endl;
				continue;
			}

			// Resets global array to zeros
			memset(arr, 0, sizeof(arr));

			// Initialization of Global Array
			for (int i = 0; i <= A.length(); i++)
			{
				for (int j = 0; j <= B.length(); j++)
				{
					// Checking B string against C string
					if ( (i == 0) && (j > 0) )
					{
						if (B[j - 1] == C[j - 1])
						{
							if (j == 1)
								arr[i][j] = 1;
							else 
								arr[i][j] = arr[i][j - 1];

							continue;
						}
					}
					// Checking A string against C string 
					else if ( (i > 0) && (j == 0) )
					{
						if (A[i - 1] == C[i - 1])
						{
							if (i == 1)
								arr[i][j] = 1;
							else
								arr[i][j] = arr[i - 1][j];

							continue;
						}
					}

					// Bottom Up Dynamic Programming
					if ( (i > 0) && (j > 0) )
					{
						// Makes entry zero unless one of the below cases is met
						arr[i][j] = 0;

						if (arr[i - 1][j] || arr[i][j - 1])
						{
							// Check if both A and B match C
							if ( (A[i - 1] == B[j - 1]) && (C[i + j - 1] == A[i - 1]) )
								arr[i][j] = 1;

							// Check if A matches C and we can backtrack
							else if ( (arr[i - 1][j]) && (C[i + j - 1] == A[i - 1]))
								arr[i][j] = 1;

							// Check if B matches C and we can backtrack
							else if ( (arr[i][j - 1]) && (C[i + j - 1] == B[j - 1]) )
								arr[i][j] = 1;

						}
					}
				}
			}


			// The Backtracking

			// If the bottom-right most entry is not a 1
			// there does not exist a valid merge
			if (arr[A.length()][B.length()])
			{
				int i = A.length();
				int j = B.length();

				while ( (i > 0) && (j >= 0) )
				{	
					// If the global entry is 1 and we are in the first row or
					// the global entry above is 0, make the corresp. entry in
					// C upper-case and head leftwards
					if ( (arr[i][j] == 1) && (j == 0 || arr[i][j - 1] == 0) )
					{
						C[i + j - 1] = toupper(C[i + j - 1]);
						i--;
					}
					// Otherwise, head upwards
					else
						j--;
				}

				// C should now contain the proper string
				fout << C << endl;
			}
			else
				fout << "*** NOT A MERGE ***" << endl;

		}

	}

	fin.close();
	fout.close();

	return 0;
}
