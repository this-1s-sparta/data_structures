#include "hashtable.h"
#include <fstream>
#include <iostream>
#include <chrono>

HashTable::HashTable(const string& filename)
{
    maxSize=500;
    size=0;
    table = new int[maxSize]();// Allocate memory for the hash table and initialize with zeros
    for (unsigned int i=0;i<maxSize;i++)
    {
        table[i]=0;
    }
    
    ifstream inputFile(filename);// Open file for reading
    int number;
    while (inputFile >> number) // Read integers from file
    {
        insert(number);// Insert each number into the hash table
    }
}

HashTable::~HashTable() {
    delete[] table; // Deallocate memory for the hash table
}


void HashTable::insert(int number) 
{
    // Check if rehashing is needed
    if (getLoadFactor()>0.75) 
    {
        rehash();// If load factor exceeds threshold, rehash the table
    }

    unsigned int index = hashFunction(number);// Generate hash index for the number
    unsigned int start = index;
    while (table[index] != 0 && table[index] != number) // Linear probing for collision resolution
    {
        index = (index + 1) % maxSize;
        if (index == start) {
            // Table is full
            rehash();// Rehash the table if all slots are filled
            index = hashFunction(number);// Get new index after rehashing
            break;
        }
    }
    table[index] = number;// Insert number into hash table
    ++size;
}

// Method to get current size of hash table
unsigned int HashTable::getSize() 
{
    return size;
}
// Method to search for number in hash table
bool HashTable::search(int number)
{
    unsigned int index = hashFunction(number);// Generate hash index for the number
    unsigned int start = index;
    do 
    {
        if (table[index] == number) 
        {
            return true;// Number found in hash table
        }
        index = (index + 1) % maxSize;
    } 
    while (index != start && table[index] != 0);// Keep searching until start index or empty slot is reached
    return false;// Number not found in hash table
}
// Method to rehash the hash table
void HashTable::rehash() 
{
    unsigned int oldTableSize = maxSize;
    maxSize *= 2;// Double the size of the hash table
    int* oldTable = table;// Store pointer to old table
    table = new int[maxSize]();// Allocate memory for new larger table
    size = 0;// Reset size

    for (unsigned int i = 0; i < oldTableSize; ++i) 
    {
        if (oldTable[i] != 0) 
        {
            insert(oldTable[i]);// Reinsert elements into new table
        }
    }

    delete[] oldTable;
}

// Method to calculate load factor of the hash table
double HashTable::getLoadFactor()
{
    return static_cast<double>(size)/maxSize;
}

// Method to generate hash index for the number
unsigned int HashTable::hashFunction(int number) 
{
    return number % maxSize; 
}