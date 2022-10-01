#ifndef SUPER_SOPA
#define SUPER_SOPA

#include "diccBloomFilter.hh"
#include "diccDHashing.hh"
#include "diccSortedVector.hh"
#include "diccTrie.hh"

#include <string>

typedef vector<vector<char >> Sopa;

class superSopa {
    public:
        superSopa ();
        void llegirDiccionari();
        void resoldreVector (); 
        void resoldreTrie ();
        void resoldreDHash ();
        void resoldreBloom ();        
        
 
    private:
        Sopa so;
        void afegir (string s);

        
};

#endif