#include "diccDHashing.hh"


void HashTableDictionary::HashTableDictionary() {
    {
        hashTable = new int[TABLE_SIZE];
        curr_size = 0;
        for (int i=0; i<TABLE_SIZE; i++)
            hashTable[i] = -1;
    } 
}


bool HashTableDictionary::isFull() {
 
        // if hash size reaches maximum size
        return (curr_size == TABLE_SIZE);
    }

int HashTableDictionary::hash1(string key) {
    int length = key.length();
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += (int)key[i];
    }

        return (sum % TABLE_SIZE);
    }

int HashTableDictionary::hash2(string key) {
    int length = key.length();
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += (int)key[i];
    }
        return (7 - (sum % 7));
    }
 

void HashTableDictionary::insertHash(string key)
    {
        // if hash table is full
        if (isFull())
            return;
 
        // get index from first hash
        int index = hash1(key);
 
        // if collision occurs
        if (hashTable[index] != -1) {
            // get index2 from second hash
            int index2 = hash2(key);
            int i = 1;
            bool found = false;
            while (!found) {
                // get newIndex
                int newIndex = (index + i * index2) % TABLE_SIZE;
                // if no collision occurs, store
                // the key
                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    found = true;
                }
                i++;
            }
        }
 
        // if no collision occurs
        else
            hashTable[index] = key;
        curr_size++;
    }

bool HashTableDictionary::comprovar (string s) {
    return true;  
}

bool HashTableDictionary::isEmpty() {
    int sum;
    for(int i; i = 0; i++) sum+= table[i].size();
    if(sum == 0) return true;
    return false;
    index = hash % tablesize
}

void HashTableDictionary::imprimir() {
    ofstream fp_out;
    fp_out.open("./DHashing/out.txt");
    for(int i = 0; i < hashGroups; i++) {
        auto bItr = table[i].begin();
        for(;bItr != table[i].end(); bItr++) {
            fp_out << bItr << endl;
        }
    }
    fp_out.close();

}

