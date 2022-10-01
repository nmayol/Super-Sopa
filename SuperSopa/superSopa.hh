#ifndef SUPER_SOPA
#define SUPER_SOPA

#include <vector>
#include <string>


#include "../Filtre Bloom/diccBloomFilter.hh"
#include "../Taula Hash/diccDHashing.hh"
#include "../Sorted Vector/diccSortedVector.hh"
#include "../Trie/diccTrie.hh"


typedef vector<vector<char >> Sopa;

class superSopa {
    public:
        superSopa ();
        superSopa (int n);
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