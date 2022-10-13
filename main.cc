#include "./SuperSopa/superSopa.hh"

using namespace std;

void llegir_fitxer (vector<string>& v, const string& path) {
    ifstream fp_in;
        string a;
        fp_in.open(path);
        while (fp_in >> a) {
            totes.push_back(a);
        }
        fp_in.close(); 
}

int main () {
    int n = 10;
    string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari();

    llegir_fitxer(diccionari, path);

    cout << diccionari[0] << endl;

    /*
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
    s.imprimirSopa ();*/    
}