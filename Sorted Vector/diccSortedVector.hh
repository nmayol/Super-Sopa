#ifndef SORTEDVECTOR_HH
#define SORTEDVECTOR_HH

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

class SortedVector {
    public:
        SortedVector ();
        bool comprovar(string s);
        int first_ocurrence(int l, int r, const char& c);
        int last_ocurrence(int l, int r, const char& c);
        const int getSize();
        const int getIterador();
        void setIterador(const int& i);
        void imprimirTrobades();
    private:
       
        vector < string> v;
        int iterador;
        set <int> trobades;
        void construirVector();
        
};

#endif