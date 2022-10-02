#ifndef SUPER_SOPA
#define SUPER_SOPA

#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;


#include "../Filtre Bloom/diccBloomFilter.hh"
#include "../Taula Hash/diccDHashing.hh"
#include "../Sorted Vector/diccSortedVector.hh"
#include "../Trie/diccTrie.hh"


typedef vector<vector<char >> Sopa;

class superSopa {
    public:
        superSopa ();
        superSopa (int mida);
        void llegirDiccionari(vector<string>& v);
        void costruirSopa(const vector<string>& dicc);

        // Metodes per resoldre-la de cadascuna de les maneres
        void resoldreVector (); 
        void resoldreTrie ();
        void resoldreDHash ();
        void resoldreBloom ();        
        
        void imprimirSopa ();  
 
    private:
        Sopa so;
        int n;
        bool afegirParaula (string s, int i0, int j0, vector<vector<bool>>& pos, int k);
        void afegirLletra(const int& i,const int& j, const char& c);
        bool compleixLimits(const int& i,const int& j);
        int randomInferiorA(int x);
        bool caracterSituable(const int& i,const int& j, const char& c);
        
};

#endif