#ifndef HASH_TABLE
#define HASH_TABLE

#include <string>
#include <list>

using namespace std;

class HashTableDictionary {
    public:
        //Constructora
        HashTableDictionary ();
        HashTableDictionary (int mida);



        //Afegir una paraula al diccionari
        void afegir (string key);

        //Mira si la paraula existeix al diccionari
        bool comprovar(string key);       
        
    private:
        int tableSize;
        int primerPetit;
        string *hashTable;
        int maxcolision;  
        bool esPrimer (int n);
        int seguentPrimer(int n);
        int abansPrimer (int n);
        //hashFunctions
        int hash1(string key);
        int hash2(string key);
};

#endif