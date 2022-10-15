#ifndef SUPER_SOPA
#define SUPER_SOPA

#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <fstream>


using namespace std;


#include "../Filtre Bloom/diccBloomFilter.hh"
#include "../Taula Hash/diccDHashing.hh"
#include "../Sorted Vector/diccSortedVector.hh"
#include "../Trie/diccTrie.hh"


typedef vector<vector<char >> Sopa;

class superSopa {
    public:
        //MÈTODES FINALS
        superSopa ();
        //superSopa (const int& mida);

        void generarSopa(const vector<string>& dicc, Sopa& sopa);

        // Metodes per resoldre-la de cadascuna de les maneres       
        void resoldre (SortedVector& d, Sopa& sopa); 
        void resoldre (TrieDictionary& d, Sopa& sopa);
        map<string, int> resoldre (HashTableDictionary& d, HashTableDictionary& pre, Sopa& sopa);
        map<string, int> resoldre (BloomFilterDictionary& d, Sopa& sopa);

        //ALTRES MÈTODES
        
               
        
        bool comprovarPosicio (Sopa& sopa, vector<vector<bool>>& v, int i, int j);
        void resoldreRecursiu (Sopa& sopa, HashTableDictionary& pre, HashTableDictionary& d, string paraula, vector<vector<bool>>& visitats, int i, int j);

        
        //void imprimirSopa ();  

        /*  Imprimeix la sopa a la Terminal.
        */
        //void imprimirSopaTerminal();

        /*  Coloca un nombre determinat de paraules a la sopa i despres
            la ompla amb lletres de forma aleatoria.
        */
        //void construirParaules(const vector<string>& dicc);

        /*  Llegeix una sopa de lletres.
        */
        //void llegir();
        
        //int mida() const;
        //char getchar(int i, int j) const;
 
    private:       
        int n;
        vector<vector<bool>> visitat;
        map<string, int> resultat;
        map<string, int>::iterator itResultat;

        void omplebuits(Sopa& sopa);
        bool colocarParaulaRec(const string& p, int l, int i, int j, Sopa& sopa);
        bool posok(int i, int j);
        int randomInferiorA(int x);
        
        //Sopa so;
        /*void afegirParaula (string s, int i0, int j0, vector<vector<bool>>& pos, int k,bool& afegida);
        void afegirLletra(const int& i,const int& j, const char& c);
        
        bool compleixLimits(const int& i,const int& j);
        bool caracterSituable(const int& i,const int& j, const char& c);
        void imprimirParaulaenSopa (const vector< vector< bool>>& pos);*/

        /*  Coloca una paraula p a la superSopa. Retorna cert si s'ha 
            pogut colocar, false altrament.
        */
        
        /*  Mira si la posicio {i,j} existeix a la sopa. Cert si existeix,
            fals altrament.
        */
        
        
};

#endif
