#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "IndexEntry.h"

template <typename K, typename V>
class HashTable
{
public:
	HashTable();
	~HashTable();

private:
	IndexEntry<K, V> table[];
};

template <typename K, typename V>
HashTable::HashTable()
{
	table = new IndexEntry<K, V>[3]();
}

template <typename K, typename V>
HashTable::~HashTable()
{

}

#endif
