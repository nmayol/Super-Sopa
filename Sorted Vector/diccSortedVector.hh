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
        void afegir (vector<string>& dicc);
        //void afegir(const string& s);
        void ordenar();
        int first_ocurrence(int l, int r, const char& c, int iterador);
        int last_ocurrence(int l, int r, const char& c, int iterador);
        const int getSize();
        
        void imprimirTrobades();
        void netejaTrobades();
        map<string,int> getTrobades();
        void buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, int iterador, Sopa& s);


    private:
        ////// Atributs //////
        vector < string> v;
        map <string,int> trobades;
        ///////////////////////
    
        
        void merge(int l, int r, int m);
        void mergesort(int l, int r);
        bool compleixLimits(Sopa& s, const int& i,const int& j,const int& n);
        
        
};

#endif