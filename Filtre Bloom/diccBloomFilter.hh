#ifndef BLOOM_FILTER
#define BLOOM_FILTER

#include <string>

using namespace std;

class BloomFilterDictionary {
    public:
        BloomFilterDictionary ();

        void afegir (string s);

        bool comprovar(string s);
    private:
        
};


#endif