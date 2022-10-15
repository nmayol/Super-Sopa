
#include "../SuperSopa/superSopa.hh"
#include <fstream>
typedef vector<vector<char >> Sopa;


Sopa llegirSopa(){
    
    cout << "Introdueix mida sopa: ";
    ifstream fp_in;
    int mida;

    fp_in.open("sopa.inp");
    fp_in >> mida;

    Sopa so(mida, vector<char>(mida));
    for (int i = 0; i < mida; ++i) {
        for(int j = 0; j < mida; ++j) fp_in >> so[i][j];
    }
    fp_in.close();
    cout << "sopa llegida" << endl;
    return so;
}

vector<string> llegirDiccionari(){
    
    vector<string> dicc(0);
    ifstream fp_in;
    fp_in.open("../diccionaris/mare-balena-vocabulary-3.txt");
    string s;
    while (fp_in >> s) {
        dicc.push_back(s);
    }
    fp_in.close();
    return dicc;
}

int main() {
    
    Sopa sopa= llegirSopa();
    superSopa ss = superSopa();

    vector<string> dicc = llegirDiccionari();

    SortedVector d;
    d.afegir(dicc);

    // Aquí comença la resolució
    ss.resoldre (d,sopa);

    // He posat que s'imprimeixin a un fitxer a part dins la carpeta S.V per comoditat
    d.imprimirTrobades();


}