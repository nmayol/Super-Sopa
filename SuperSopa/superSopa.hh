#ifndef SUPER_SOPA
#define SUPER_SOPA

#include <vector>
#include <string>
#include <map>
#include <time.h>
#include <random>

//esborrar
#include <iostream>

using namespace std;


#include "../Filtre Bloom/diccBloomFilter.hh"
#include "../Taula Hash/diccDHashing.hh"
#include "../Sorted Vector/diccSortedVector.hh"
#include "../Trie/diccTrie.hh"


typedef vector<vector<char >> Sopa;

class superSopa {
    public:
        superSopa ();       

        void generarSopa(const vector<string>& dicc, Sopa& sopa);

        // Metodes per resoldre-la de cadascuna de les maneres       
        map<string, int> resoldre (SortedVector& d, Sopa& sopa); 
        void resoldre (TrieDictionary& d, Sopa& sopa);
        void resoldre (map<string, int>& res, HashTableDictionary& d, HashTableDictionary& pre, Sopa& sopa);
        void resoldre (map<string, int>& res, BloomFilterDictionary& d, BloomFilterDictionary& pre, Sopa& sopa);
               
        bool comprovarPosicio (int i, int j, matbool& v);
        void resoldreRecursiuHash (matbool& v, string paraula, int i, int j);
        void resoldreRecursiuFiltre (matbool& v, string paraula, int i, int j);
 
    private:        
        //vector<vector<bool>> visitats;
        vector<vector<bool>> visitat;
        map<string, int> resultat;
        map<string, int>::iterator itResultat;

        HashTableDictionary pre_hash, d_hash;
        BloomFilterDictionary pre_filtre, d_filtre;
        Sopa sopa;
        int n;

        void omplebuits(Sopa& sopa);
        bool colocarParaulaRec(const string& p, int l, int i, int j, Sopa& sopa);
        bool posok(int n, int i, int j);
        int randomInferiorA(int x);  
        
        //void calculaDireccions(matbool& v, const string& par, int i, int j);
        void calculaDireccions(TrieDictionary& d, const Sopa& so, matbool& v, const string& par, int i, int j);
   
};

#endif
