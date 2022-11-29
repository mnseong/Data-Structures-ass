#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define MOD 2147483647
using namespace std;

int a_VALUE_FOR_HASH_CODE_CALCULATION, NUMBER_OF_THE_FOLLOWING_LINES;
double MIN_LOAD_FACTOR, MAX_LOAD_FACTOR;

class Node {
	public:
		Node() : key(""), value(0), linkNode(nullptr) {}
		Node(string key, int value) {
			this->key = key;
			this->value = value;
			this->linkNode = nullptr;
		}
		void chaining(Node* node) { linkNode = node; }
		string getKey() { return key; }
		int getValue() { return value; }
		Node* linkNode;
	private:
		string key;
		int value;
};

class HashTable {
	public:
		HashTable(int size = 512) {
			this->size = size;
			bucketList.resize(size);
			bucketNum.resize(size);
		}
	
		vector<Node> bucketList;
	
		void add(string key, int value) {
			int idx = hashCode(key) % size;
			Node* next = bucketList[idx].linkNode;
			Node* cur = &bucketList[idx];
			while (next != nullptr) {
				cur = next;
				if (cur->getKey() == key) return;
				next = next->linkNode;
			}
			Node *newNode = new Node(key, value);
			cur->chaining(newNode);
			numNode++;
			bucketNum[idx]++;
		}
	
		void remove(string key) {
			int idx = hashCode(key) % size;
			if (numNode == 0 || bucketNum[idx] == 0) return;
			if (bucketNum[idx] > 0) {
				Node* cur = bucketList[idx].linkNode;
				Node* prev = &bucketList[idx];
				while (cur != nullptr && cur->getKey() != key) {
					prev = cur;
					cur = cur->linkNode;
				}
				if (cur == nullptr) return;
				prev->chaining(cur->linkNode);
				delete(cur);
				numNode--;
				bucketNum[idx]--;
			}
		}
	
		void getKeyValue(int idx) {
			Node* cur = bucketList[idx].linkNode;
			while (cur != nullptr) {
				printf("(%s,%d)\n", cur->getKey().c_str(), cur->getValue());
				cur = cur->linkNode;
			}
		}
	
		int getNumNode() { return numNode; }
		int getSize() { return size; }
		double getLoadFactor() { return loadFactor; }
		int getMoreThanFive() {
			int result = 0;
			for (int i = 0; i < bucketNum.size(); i++) {
				if (bucketNum[i] > 5) result++;
			}
			return result;
		}
		int getLongest() {
			int tmp = bucketNum[0];
			int result = 0;
			for (int i = 0; i < bucketNum.size(); i++) {
				if (bucketNum[i] >= tmp) {
					tmp = bucketNum[i];
					result = i;
				}
			}
			return result;
		}
		void setLoadFactor() { loadFactor = (double)numNode / (double)size; }
	private:
		int size;
		int numNode;
		double loadFactor;
		vector<int> bucketNum;
		long hashFunction(int num, string key) {
			if (num == 0)
				return (key[0] % MOD);
			else {
				long sec = (long)key[num] + (a_VALUE_FOR_HASH_CODE_CALCULATION * hashFunction(num-1, key));
				return sec % MOD;
			}
		}
		int hashCode(string key) { return hashFunction((key.length()-1), key); }
};

HashTable* doubleRehash(HashTable* prev) {
	int len = prev->getSize();
	printf("Rehashing: %d -> %d\n", len, 2*len);
	HashTable* newTable = new HashTable(2*len);
	
	for (int i = 0; i < prev->bucketList.size(); i++) {
		Node *next = prev->bucketList[i].linkNode;
		while (next != nullptr) {
			string tmpKey = next->getKey();
			int tmpValue = next->getValue();
			
			newTable->add(tmpKey, tmpValue);
			next = next->linkNode;
		}
	}
	
	return newTable;
}

HashTable* halveRehash(HashTable* prev) {
	int len = prev->getSize();
	printf("Rehashing: %d -> %d\n", len, len / 2);
	HashTable* newTable = new HashTable(len / 2);
	
	for (int i = 0; i < prev->bucketList.size(); i++) {
		Node *next = prev->bucketList[i].linkNode;
		while (next != nullptr) {
			string tmpKey = next->getKey();
			int tmpValue = next->getValue();
			
			newTable->add(tmpKey, tmpValue);
			next = next->linkNode;
		}
	}
	
	return newTable;
}

HashTable* solution(int size) {
	HashTable* hashTable = new HashTable(size);
	char command = '\0';
	string key = "";
	int value = 0;
	double lf = 0.0;
	
	for (int i = 0; i < NUMBER_OF_THE_FOLLOWING_LINES; i++) {
		cin >> command >> key >> value;
		if (lf > MAX_LOAD_FACTOR) hashTable = doubleRehash(hashTable);
		else if (lf < MIN_LOAD_FACTOR && hashTable->getSize() >= 1024) hashTable = halveRehash(hashTable);
		
		if (command == 'i') hashTable->add(key, value);
		else hashTable->remove(key);
		
		hashTable->setLoadFactor();
		lf = hashTable->getLoadFactor();
	}
	
	return hashTable;
}

int main() {
	cin >> a_VALUE_FOR_HASH_CODE_CALCULATION >> MIN_LOAD_FACTOR >> MAX_LOAD_FACTOR >> NUMBER_OF_THE_FOLLOWING_LINES;

	HashTable* result = solution(512);
	
	printf("Number of entries: %d\n", result->getNumNode());
	printf("Size of the bucket array: %d\n", result->getSize());
	printf("%d buckets contain more than 5 elements\n", result->getMoreThanFive());
	printf("The longest bucket: %d\n", result->getLongest());
	result->getKeyValue(result->getLongest());
	
	return 0;
}
