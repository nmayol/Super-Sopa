#ifndef SORTEDVECTOR_HH
#define SORTEDVECTOR_HH

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SortedVector {
    public:
        SortedVector ();
        SortedVector (const vector<string>& vs);

        void construirVector();

        void afegir (string s);

        bool comprovar(string s);
        
        void resoldre();
        
    private:
        vector <string> v;
        void OrdenarVector();
        
};

#endif