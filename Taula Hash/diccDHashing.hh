#ifndef HASH_TABLE
#define HASH_TABLE

#include <string>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;


class HashTableDictionary {
    public:
        //constructora
        HashTableDictionary (int mida);
        //Afegir una paraula al diccionari
        void afegir (string key);
        //mira si esta la paraula al diccionari
        bool comprovar(string key);
        int hash1(string key);
        int hash2(string key);
        void escriure();
        
        
    private:
        static const int tableSize;
        int *hashTable;
        int curr_size;
        int maxcolision;
    

        
        
};

#endif