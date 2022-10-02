#include <iostream>
#include <string>
#include <vector>

#include "./SuperSopa/superSopa.hh"

using namespace std;

int main () {
    // n es la mida de la sopa
    int n; cin >> n;
    superSopa s = superSopa(n);
    // poso aixo per provar
    vector <string> dic = {"a", "eee", "pol", "super", "sopa", "esternoclidomastoidal"};
    s.llegirDiccionari(dic);
    s.imprimirSopa();
    
}