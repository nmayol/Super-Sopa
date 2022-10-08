

#include "./SuperSopa/superSopa.hh"
#include <algorithm>
using namespace std;

int main () {
    // n es la mida de la sopa
    cout << "introdueix la mida de la sopa: (el vector de prova funciona amb mida >= 7)." << endl;
    int n; cin >> n;
    cout << "ara es crearà la sopa (pot trigar una mica)." << endl;
    superSopa s = superSopa(n);

    // poso aixo per provar
    
    vector <string> dic = {"a", "eee", "pol", "super", "sopa", "esternoclidomastoidal"};


    
    s.costruirSopa(dic);
    //s.llegirDiccionari(dic);
    s.imprimirSopa();
    
}