/**
 * hash.h
 *  Implements a hash table with our own developed hash function
 */
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Map.h"

#include <cstdlib>
#include <math.h> 

#include <vector>
#include <queue>

using namespace std;

class hashtable : public Map 
{
public:
	
	hashtable()
	{
		for(int i = 0; i < 11; i++)
		{
			buckets.push_back(make_pair("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", -1)); // setting the buckets with NULL pairs 
		}

		NUM_buckets = 11;
		elements = 0;

		resize_size.push(23); // adding in all of the resize factors
		resize_size.push(41);
		resize_size.push(83);
		resize_size.push(163);
		resize_size.push(331);
		resize_size.push(641);
		resize_size.push(1283);
		resize_size.push(2579);
		resize_size.push(5147);
		resize_size.push(10243);
		resize_size.push(20483);
		resize_size.push(40961);
	}
	~hashtable(){}

	void add(const string& word)
	{
		int index = find_index(word);

		if(index != -1) // if the word already exists
		{
			buckets[index] = make_pair(word, 1);
			elements++;

			load_factor = (double(elements))/NUM_buckets;

			if(load_factor > 0.5)
				resize_buckets();
		}
	}
	
	void reportAll(ostream &output)
	{
		
		for(int i = 0; i < buckets.size(); i++)
		{
			if(buckets[i].second != -1)
				cout << buckets[i].first << " " << buckets[i].second << endl;
		}
	}

private:

	vector<pair<string, int> > buckets;

	queue<int> resize_size;

	int NUM_buckets;

	int elements;

	double load_factor;

	int find_index(const string& word){

		int hash = hash_str(word); // getting the hash function

		int j = 0; // counter set to 0

		bool stop = false;

		while(!stop)
		{
			hash = (hash + j * j) % NUM_buckets;
			j++;

			// if the word already exists, update the counter 
			if(buckets[hash].first == word)
			{
				buckets[hash].second = buckets[hash].second + 1;

				stop = true;
				hash = -1;
			}

			// if the word does not exist, return the index to insert
			if(buckets[hash].second == -1 && hash != -1)
			{
				stop = true;
			}	
		}

		return hash;
	}

	void resize_buckets()
	{
		
		int new_size = resize_size.front();
		resize_size.pop();

		NUM_buckets = new_size;

		vector<std::pair<std::string, int> > copy = buckets;

		buckets.clear();

		for(int i = 0; i < new_size; i++)
		{

		buckets.push_back(make_pair("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", -1));

		}

		for(int i = 0; i < copy.size(); i++)
		{
			if(copy[i].second != -1)
			{
				this->add(copy[i].first);
			}
		}

	}

	int hash_str(const string& word)
	{
		unsigned long long blocks[14] = {0};

		int current_block = 13;
		int next_set;

		for(int i = word.size(); i > 0; i -= 8)
		{
			next_set = current_block - 4; 

			unsigned long long block = 0;

			for(int j = 0; j < 8; j++)
			{
				if(word[(i-1)-j] > 0)
				{
					block += (unsigned long long)((pow(128.0,j)) * (word[(i-1)-j])); // calc long long 128^7 * a1 + 128^6 * a2 + ... + 128 * a7 + a8
				}
			}

			while(block > 1)
			{
				blocks[current_block] = block % 40961;
	    		block /= 40961;
	        	current_block--;
	    	}

	    	current_block = next_set; // next set of w's
		}

		unsigned long long hash = ((unsigned long long)(34394 * blocks[0]) + (unsigned long long)(36706 * blocks[1]) + (unsigned long long)(38074 * blocks[2]) + (unsigned long long)(16351 * blocks[3]) + (unsigned long long)(2623 * blocks[4]) 
			+ (unsigned long long)(10174 * blocks[5]) + (unsigned long long)(22339 * blocks[6]) + (unsigned long long)(27779 * blocks[7]) + (unsigned long long)(36642 * blocks[8]) + (unsigned long long)(19250 * blocks[9]) + (unsigned long long)(36216 * blocks[10]) 
			+ (unsigned long long)(33514 * blocks[11]) + (unsigned long long)(24019 * blocks[12]) + (unsigned long long)(5552 * blocks[13]));
		
		int hash_index = hash % NUM_buckets;
	
		return hash_index;
	}
};

#endif