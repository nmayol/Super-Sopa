#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <string>

class BloomFilterDictionary {
    public:
        BloomFilterDictionary ();

        void afegir (string s);

        bool comprovar(string s);
    private:
        
};

#endif