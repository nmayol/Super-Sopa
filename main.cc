

#include "./SuperSopa/superSopa.hh"

using namespace std;

int main () {
    // n es la mida de la sopa
    int n;

    cout << "Introdueix la mida de la sopa: ";
    cin >> n;
    
    cout << "Utilitzem el diccionari Balena." << endl;
    vector<string> balena(5053);
    for (int i = 0; i < 5053; ++i) cin >> balena[i];
    cout << "Diccionari llegit." << endl;

    cout << "Ara es creara la sopa de mida " << n << endl;

    superSopa s = superSopa(n);
    cout << "CREADA!! Ara afegim les paraules..." << endl;

    s.construirParaules(balena);
    s.imprimirSopaTerminal();
    /*
    cout << "Sorted Vector:" << endl;
    s.resoldreVector();
    */
    
    
}