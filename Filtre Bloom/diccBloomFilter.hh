#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <string>
#include <vector>
#include <cmath>

using namespace std;

class BloomFilterDictionary {
    public:
        //Constructors
        BloomFilterDictionary ();

        BloomFilterDictionary (int m);

        //Afegir paraula al diccionari
        void afegir (const string& s);

        //Comprovar si una paraula és al diccionari
        bool comprovar(const string& s);

    private:
        //mida del vector bloom
        int mida = 47925;

        //vector bloom
        vector<bool> BloomFilter;        

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