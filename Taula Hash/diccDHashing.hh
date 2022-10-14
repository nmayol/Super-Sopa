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
        HashTableDictionary ();
        //Afegir una paraula al diccionari
        void afegir (int key, string s);
        //mira si esta la paraula al diccionari
        bool comprovar(int key, string s);
        void escriure();
        int hashFunction(int key);
        
    private:
        static const int tablesize;
        list<string> table[tablesize];

    

        
        
};

#endif