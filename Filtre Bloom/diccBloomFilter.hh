#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <string>
#include <iostream>

using namespace std;

class BloomFilterDictionary {
    public:
        //Constructor
        BloomFilterDictionary ();

        //Afegir paraula al diccionari
        void afegir (const string& s);

        //Comprovar si una paraula és al diccionari
        bool comprovar(const string& s);

        //Mostra el filtre de Bloom
        void imprimir ();
    private:
        //mida del vector bloom
        int mida = 47925;

        //vector bloom
        bool BloomFilter [47925];        

        //Funcions de hash
        int h1 (const string& s);

        int h2 (const string& s);

        int h3 (const string& s);

        int h4 (const string& s);

        int h5 (const string& s);

        int h6 (const string& s);

        int h7 (const string& s);

};

#endif