#ifndef HASH_TABLE
#define HASH_TABLE

#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;


class HashTableDictionary {
    public:
        //Constructora
        HashTableDictionary (int mida);
        //hashFunctions
        int hash1(string key);
        int hash2(string key);
        //Afegir una paraula al diccionari
        void afegir (string key);
        //Mira si la paraula existeix al diccionari
        bool comprovar(string key);
        
        //void escriure();
        
    private:
        int tableSize;
        string *hashTable;
        int curr_size;
        int maxcolision;      
};

#endif