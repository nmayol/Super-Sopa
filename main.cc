#include <iostream>
#include <string>
#include <vector>

#include "./SuperSopa/superSopa.hh"

using namespace std;

int main () {
    // n es la mida de la sopa
    int n; cin >> n;
    cout << "aaaaaaaaaa";
    superSopa s = superSopa(n);
    // poso aixo per provar
    
    vector <string> dic = {"a", "eee", "pol", "super", "sopa", "esternoclidomastoidal"};
    s.costruirSopa(dic);
    s.llegirDiccionari(dic);
    s.imprimirSopa();
    
}