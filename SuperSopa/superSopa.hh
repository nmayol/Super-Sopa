#ifndef SUPER_SOPA
#define SUPER_SOPA

#include "diccBloomFilter.hh"
#include "diccDHashing.hh"
#include "diccSortedVector.hh"
#include "diccTrie.hh"

#include <string>

class BloomFilterDictionary {
    public:
        BloomFilterDictionary ();

        void afegir (string s);

        bool comprovar(string s);
    private:
        
};

#endif