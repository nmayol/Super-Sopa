#ifndef SUPER_SOPA
#define SUPER_SOPA

#include <vector>
#include <string>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include<fstream>


using namespace std;


#include "../Filtre Bloom/diccBloomFilter.hh"
#include "../Taula Hash/diccDHashing.hh"
#include "../Sorted Vector/diccSortedVector.hh"
#include "../Trie/diccTrie.hh"


typedef vector<vector<char >> Sopa;

class superSopa {
    public:
        superSopa ();
        superSopa (const int& mida);        

        // Metodes per resoldre-la de cadascuna de les maneres
        void resoldreVector (); 
        void buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, SortedVector& sv);

        void resoldreTrie ();
        void resoldreDHash ();
        void resoldreBloom ();        
        
        void imprimirSopa ();  

        /*  Imprimeix la sopa a la Terminal.
        */
        void imprimirSopaTerminal();

        /*  Coloca un nombre determinat de paraules a la sopa i despres
            la ompla amb lletres de forma aleatoria.
        */
        void construirParaules(const vector<string>& dicc);
 
    private:
        Sopa so;
        vector<vector<bool>> visitat;
        
        int n;
        void afegirParaula (string s, int i0, int j0, vector<vector<bool>>& pos, int k,bool& afegida);
        void afegirLletra(const int& i,const int& j, const char& c);
        void omplebuits();
        bool compleixLimits(const int& i,const int& j);
        int randomInferiorA(int x);
        bool caracterSituable(const int& i,const int& j, const char& c);
        void imprimirParaulaenSopa (const vector< vector< bool>>& pos);

        /*  Coloca una paraula p a la superSopa. Retorna cert si s'ha 
            pogut colocar, false altrament.
        */
        bool colocarParaulaRec(const string& p, int l, int i, int j);

        /*  Mira si la posicio {i,j} existeix a la sopa. Cert si existeix,
            fals altrament.
        */
        bool posok(int i, int j);
        
};

#endif