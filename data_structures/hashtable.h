#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using namespace std;
 

class HashTable 
{
    
private:
    unsigned int hashFunction(int number);// Hash function to generate index from number
    int* table;// Array to store hash table
    unsigned int maxSize,size;// Maximum size of table and current number of elements
    
public:
    HashTable(const string& filename);// Constructor
    ~HashTable();// Destructor
    void insert(int number);// Insert number into hash table
    unsigned int getSize();// Get current size of hash table
    bool search(int number);// Search for number in hash table
    void rehash();// Rehash the hash table
    double getLoadFactor();// Calculate load factor of the hash table
};

#endif 