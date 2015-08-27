#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#define TABLE_SIZE 128
#include <array>
#include <functional>
#include "IndexEntry.h"

// LOAD FACTORRR

template <typename K, typename V>
class HashTable
{
public:
	HashTable();
	HashTable(int(*HashingFunction)(int data));
	~HashTable();

	void put(K key, V value);
	void remove(K key);
private:
	//IndexEntry<K, V> **table;
	std::array<IndexEntry<K, V>*, TABLE_SIZE> table;

	int defaultHash(int a) 
	{ 
		cout << "a: " << a << endl;
		return 2; 
	}
public:
	std::function<int(int)> hashFunction; // pointer to function that returns an int and accepts 1 int parameter (int)
};

template <typename K, typename V>
HashTable<K, V>::HashTable()
{
	table.fill(nullptr);
	//hashFunction = std::bind(&HashTable::defaultHash, _1);
}

template <typename K, typename V>
HashTable<K, V>::HashTable(int (*HashingFunction)(int data))
{
	table.fill(nullptr);
	hashFunction = std::bind(HashingFunction, _1);
}


template <typename K, typename V>
HashTable<K, V>::~HashTable()
{

}

template <typename K, typename V>
void HashTable<K, V>::put(K key, V value)
{
	// assuming for now that the key is a string
	std::hash<std::string> hf;
	size_t hash = hf(key); //hashFunction(sizeof(key));
	int index = hash % TABLE_SIZE;

	IndexEntry<K, V> *current = nullptr, *previous = nullptr;
	
	// Add a new entry to the "bucket" at the index calculated
	previous = table[index];
	if (table[index] != nullptr)
	{	// get to the entry with the same key
		current = previous->next;
		while (current != nullptr)
		{
			if (current->getKey() == key)
			{	// same key found
				current->setValue(value);	// update value
				return;
			}
			previous = current;
			current = current->next;
		}
		// at the end, no entries with the key found = make a new entry
		IndexEntry<K, V> *newEntry = new IndexEntry<K, V>(key, value);
		previous->next = newEntry;
	}
	else
	{	// no previous entries at this spot (yay!), so add new entry right away
		table[index] = new IndexEntry<K, V>(key, value);
	}
}

template <typename K, typename V>
void HashTable<K, V>::remove(K key)
{
	// assuming for now that the key is a string
	std::hash<std::string> hf;
	size_t hash = hf(key); //hashFunction(sizeof(key));
	int index = hash % TABLE_SIZE;

	IndexEntry<K, V> *current = table[index], *previous = nullptr;

	while (current != nullptr)
	{
		if (current->getKey() == key)
		{	// entry with key has been found. remove it
			if (current == table[index])
			{	// it's the only entry at this index
				table[index] = nullptr;
			}
			else
			{
				previous->next = current->next;
				delete current;
			}
			return;
		}
	}
}

#endif
