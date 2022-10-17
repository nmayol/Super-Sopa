#ifndef SORTEDVECTOR_HH
#define SORTEDVECTOR_HH


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef vector<vector<char >> Sopa;



class SortedVector {
    public:

        SortedVector ();

        /*  Afegeix el diccionari
            Pre: cert.
            Post: L'atribut v ara es el diccionari dicc, pero ordenat.
        */
        void afegir (vector<string>& dicc);
        
        /*  Retorna la mida del diccionari (es a dir, de l'atribut vector)
            Pre: Cert.
            Post: La mida del diccionari.
        */
        const int getSize();
        
        /* Imprimeix les paraules trobades i el numero docurrencies de cada una a un fitxer
           Pre: Cert
           Post: Es disposen les paraules trobada i el seu nombre d'ocurrències corresponent pel canal de sortida.
        */
        void imprimirTrobades();

        /* Esborra les paraules trobades, reinicialitza el map
           Pre: trobades pot tenir o no  paraules
           Post: trobades està buit
        */
        void netejaTrobades();

        /* Retorna les paraules trobades i el numero docurrencies de cada una
           Pre: Cert
           Post: retorna el map amb les paraules trobades
        */
        map<string,int> getTrobades();

        /* Funcio creada per recorrer la sopa amb backtracking i trobar les paraules
           Pre: (i,j) són posició de la sopa / 0 <= l < r < v.size() / 0 <= iterador
           Post: trobades tindrà una paraula més si v[l].size() = iterador
        */
        void buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, int iterador, Sopa& s);


    private:

        ////// Atributs //////
        vector < string> v;
        map <string,int> trobades;
        ///////////////////////
    
        
        /*  Ordena el diccionari d'entrada
            Pre: El vector pot estar o no ordenat.
            Post: El vector esta ordenat.
        */
        void merge(int l, int r, int m);
        void mergesort(int l, int r);

        /* Busca la primera ocurrència del caracter c en la posicio iterador d'una paraula
           fent així més gran el prefix buscat.
           Pre: 0 <= iterador / els valors entre l i r tenen el mateix prefix de mida iterador-1.
           Post: Es retorna la primera ocurrencia de les paraules que tenen prefix iterador-1 i el caracter c a la posicio iterador
        */
        int firstOcurrence(int l, int r, const char& c, int& iterador);

        /* Busca l'última ocurrència del caracter c en la posicio iterador d'una paraula,
           fent així més gran el prefix buscat 
           Pre: 0 <= iterador / els valors entre l i r tenen el mateix prefix de mida iterador-1.
           Post: Es retorna l'ultima ocurrencia de les paraules que tenen prefix iterador-1 i el caracter c a la posicio iterador
        */
        int lastOcurrence(int l, int r, const char& c, int& iterador);

        /* Retorna cert si la posicio (i,j) es troba dins els limits de la sopa
           Pre: (i,j) pot ser o no posicio de la sopa s
           Post: cert si (i,j) es posicio de la sopa s
        */
        bool compleixLimits(Sopa& s, const int& i,const int& j,const int& n);
        
        
};

#endif