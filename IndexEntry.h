#pragma once
#ifndef INDEXENTRY_H
#define INDEXENTRY_H

template <typename K, typename V>
class IndexEntry
{
	K key;
	V value;
public:
	IndexEntry();
	IndexEntry(K Key, V Value);
	~IndexEntry();

	IndexEntry * next;

	K getKey() { return key; }
	V getValue() { return value; }
	void setValue(V val)
	{
		value = val;
	}
private:

};


template <typename K, typename V>
IndexEntry<K, V>::IndexEntry()
{
	next = nullptr;
}

template <typename K, typename V>
IndexEntry<K, V>::IndexEntry(K Key, V Value)
{
	next = nullptr;
	this->key = Key;
	this->value = Value;
}

template <typename K, typename V>
IndexEntry<K, V>::~IndexEntry()
{
}

#endif