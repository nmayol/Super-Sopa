#ifndef SORTEDVECTOR_HH
#define SORTEDVECTOR_HH


#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

typedef vector<vector<char >> Sopa;



class SortedVector {
    public:
        SortedVector ();
        void afegir (const vector<string>& dicc);
        int first_ocurrence(int l, int r, const char& c, const int& iterador);
        int last_ocurrence(int l, int r, const char& c, const int& iterador);
        const int getSize();
        
        void imprimirTrobades();
        void buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, int iterador, Sopa& s);
    private:
        ////// Atributs //////
        vector < string> v;
        set <int> trobades;
        ///////////////////////
    
        
        void merge(int l, int r, int m);
        void mergesort(int l, int r);
        bool compleixLimits(Sopa& s, const int& i,const int& j,const int& n);
        
        
};

#endif