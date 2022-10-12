#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <string>
#include <cmath>
//esborrar
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class BloomFilterDictionary {
    public:
        //Constructor
        BloomFilterDictionary ();

        //Afegir paraula al diccionari
        void afegir (const string& s);

        //Comprovar si una paraula és al diccionari
        bool comprovar(const string& s);

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