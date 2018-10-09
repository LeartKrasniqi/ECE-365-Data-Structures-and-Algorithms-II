// Leart Krasniqi
// DSA II - Prof. Sable
// Assignment 1

// This file defines the functions of the
// hashTable class.

#include "hash.h"
#define TRUE 1
#define FALSE 0

int primes[] = { 98317, 196613, 393241, 786433, 1572869, 
				3145739, 6291469, 12582917, 25165843, 
				50331653, 100663319, 201326611, 402653189, 
				805306457, 1610612741 };

// Constructs the hash table with a set size and no entries
hashTable::hashTable(int size)
{
	capacity = getPrime(size);
	data.resize(capacity);
	filled = 0;

	for (int i = 0; i < capacity; i++)
	{
		data[i].isOccupied = FALSE;
		data[i].isDeleted = FALSE;
	}
}

// Inserts elements into the table and utilizes linear 
// probing to resolve conflicts
// Adopted from: https://www.sanfoundry.com/cpp-program-implement-hash-tables-linear-probing/
// and from	   : http://www.cs.rmit.edu.au/online/blackboard/chapter/05/documents/contribute/chapter/05/linear-probing.html
int hashTable::insert(const std::string &key, void *pv)
{
	if (capacity <= (2 * filled))		// Checks if table needs to be rehashed
	{
		if(!rehash())
			return 2;
	}

	int keyAddress = hash(key);
	int probe = -1;

	while (data[keyAddress].isOccupied)
	{
		if (data[keyAddress].key == key)				// If the key already exists in the table
		{												// and is not deleted, return 1
			if (!(data[keyAddress].isDeleted))
				return 1;
			else 										// If the key already exists in the table
			{											// and was previously deleted, mark it as
				data[keyAddress].isDeleted = FALSE;		// not deleted anymore
				return 0;								
			}											
		} else if ((data[keyAddress].isDeleted) && (probe == -1))	// Implementation of Linear Probing
		{
			probe = keyAddress;
		}
		keyAddress++;
		if (keyAddress == capacity)		// Prevents accessing an element not in the data vector
			keyAddress = 0;
	}

	if (probe != -1)					// Puts the data in the probed spot
		keyAddress = probe;

	data[keyAddress].key = key;
	data[keyAddress].isOccupied = TRUE;
	data[keyAddress].isDeleted = FALSE;
	data[keyAddress].pv = pv;
	filled++;
	return 0;
}

bool hashTable::contains(const std::string &key)
{
	if (findPos(key) == -1)
		return FALSE;
	else
		return TRUE;
}

// Assigns vector address to keys
// Adopted from: https://stackoverflow.com/questions/8317508/hash-function-for-a-string
int hashTable::hash(const std::string &key)
{
	unsigned h = 31;
   	for (std::size_t i = 0; i < key.length(); i++) 
    	h = (h * 76963) ^ (key[i] * 54059);		// Utilizes bitwise XOR 
   	return (h % capacity);
}

int hashTable::findPos(const std::string &key)
{
	int keyAddress = hash(key);
	while (data[keyAddress].isOccupied)
	{
		if (data[keyAddress].key == key)
		{
			if (data[keyAddress].isDeleted)
				return -1;
			else 
				return keyAddress;
		} else
		{
			keyAddress++;
			if (keyAddress == capacity)		// Prevents accessing an element not in data vector
				keyAddress = 0;
		}
	}
	return -1;
}

// Make the hash table bigger if needed
bool hashTable::rehash()
{
	std::vector<hashItem> data_copy = data;		// Copy over the data to a temporary vector
	int newCapacity = getPrime(2 * capacity);
	try
	{
		data.resize(newCapacity);
	}
	catch (std::bad_alloc)
	{
		return FALSE;
	}
	capacity = newCapacity;
	filled = 0;

	for (int i = 0; i < capacity; i++)		// Make sure data vector is empty so we can
	{										// map values again 
		data[i].isOccupied = FALSE;
		data[i].isDeleted = FALSE;
	}

	//copy over data elements into resized vector 
	for (int i = 0; i < data_copy.size(); i++)
	{
		if((data_copy[i].isOccupied == TRUE) && (data_copy[i].isDeleted == FALSE))
			insert(data_copy[i].key);
	}

	return TRUE;

}

unsigned int hashTable::getPrime(int size)
{
	for (int i = 0; i < sizeof(primes)/sizeof(int); i++)
	{
		if (size <= primes[i])
			return primes[i];
	}
}
