// Leart Krasniqi
// DSA II - Prof. Sable
// Assignment 2

// This file defines the functions of the
// heap class.

#include "heap.h"

// Constructor for heap class
heap::heap(int capacity)
{
	mapping = new hashTable(capacity * 2);		// Make hashtable for the mapping
	data.resize(capacity + 1);
	this->capacity = capacity;	// Set capacity of heap to value provided by user
	size = 0;
}

int heap::insert(const std::string &id, int key, void *pv)
{
	if (size < capacity)
	{
		if (mapping->contains(id))		// Checks if hash table has the id
			return 2;
		else
		{
			size++;						// Inserts new element into heap and
			data[size].id = id;			// uses percolateUp to preserve structure
			data[size].key = key;
			data[size].pData = pv;
			mapping -> insert(id, &data[size]);
			percolateUp(size);

			return 0;
		}
	}
	else
		return 1;
}

int heap::setKey(const std::string &id, int key)
{
	if (mapping->contains(id))
	{
		node *pn = static_cast<node *> (mapping->getPointer(id));	// Points to id value

		int oldKey = pn->key;		// Remember old key

		pn->key = key;
		int pos = getPos(pn);

		if (oldKey < key)				// Depending on the value of the key, we
			percolateDown(pos);			// either percolate up or down to find its
		if (oldKey > key)				// proper location in the heap
			percolateUp(pos);

		return 0;
	}
	else
		return 1;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
	if (size != 0)
	{
		// Write to the proper addresses if they are specifified
		if (pId != NULL)
			*pId = data[1].id;

		if (pKey != NULL)
			*pKey = data[1].key;

		if (ppData != NULL)
			*(static_cast<void **> (ppData)) = data[1].pData;


		// Deletion implementation influenced by Figure 6.12 in our textbook
		mapping -> remove(data[1].id);
		data[1] = data[size];
		size--;
		percolateDown(1);

		return 0;
	} else
		return 1;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
	// Check if node with given id exists
	if (mapping -> contains(id))
	{
		node *pn = static_cast<node *> (mapping -> getPointer(id)); 	// Reference to specified node
		int oldKey = pn -> key;

		// Write to the proper addresses if they are specifified
		if (pKey != NULL)
			*pKey = pn -> key;

		if (ppData != NULL)
			*(static_cast<void **> (ppData)) = pn -> pData;

		// Remove id from hash table and update pn
		mapping -> remove(id);
		*pn = data[size];
		int newKey = pn -> key;
		size--;

		int pos = getPos(pn);

		// Maintain structure of heap
		if (newKey < oldKey)
			percolateUp(pos);
		else if (newKey > oldKey)
			percolateDown(pos);

		return 0;
	} else
		return 1;
}

// Implementation influenced by Figure 6.8 in our textbook 
void heap::percolateUp(int posCur)
{
	node temp = data[posCur];		// Temporary variable to store the item at posCur
	for( ; (posCur > 1) && (temp.key < data[posCur / 2].key); posCur /= 2)
	{
		data[posCur] = data[posCur / 2];
		mapping -> setPointer(data[posCur].id, &data[posCur]);		// Remaps hash table
	}

	data[posCur] = temp;			
	mapping -> setPointer(data[posCur].id, &data[posCur]);
}

// Implementation influenced by Figure 6.12 in our textbook
void heap::percolateDown(int posCur)
{
	node temp = data[posCur];
	int child, l, r;

	for ( ; (posCur * 2) <= size; posCur = child)
	{
		l = posCur * 2;
		r = l + 1;

		if ((l < size) && (data[r].key < data[l].key))
			child = r;
		else
			child = l;

		if (data[child].key < temp.key)
		{
			data[posCur] = data[child];
			mapping -> setPointer(data[posCur].id, &data[posCur]);
		} else
			break;
	}

	data[posCur] = temp;
	mapping -> setPointer(data[posCur].id, &data[posCur]);	
}

int heap::getPos(node *pn)
{
	int pos = pn - &data[0];
	return pos;
}
