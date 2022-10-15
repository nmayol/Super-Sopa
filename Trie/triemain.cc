#include "diccTrie.hh"
using namespace std;

typedef vector<vector<bool>> matbool;
typedef vector<vector<char>> sopa;

int main() {

    
    /* Lectura diccionari -> guardar en arbre.
    */
    TrieDictionary dicTrie = TrieDictionary();
    dicTrie.llegirTrie();
    cout << "Diccionari guardat correctament!" << endl;

    /*  Guardem el diccionari a un trie i el simplifiquem.
    */
    cout << "Imprimim el diccionari guardat:" << endl;
    cout << "Ara simplifiquem" << endl;
    dicTrie.simplificaArbre();
    dicTrie.escriure();
    
    cout << "Introdueix mida sopa: ";
    int mida;
    cin >> mida;

    sopa so(mida, vector<char>(mida));
    for (int i = 0; i < mida; ++i) {
        for(int j = 0; j < mida; ++j) cin >> so[i][j];
    }
    cout << "sopa llegida" << endl;

    matbool v = matbool(mida, vector<bool>(mida, false));

    string o;
    cin >> o;

    while (o != "stop") {
        if (dicTrie.existeixParaula(o)) cout << "existeix!" << endl;
        else cout << "nooo" << endl;
        cin >> o;
    }

    //dicTrie.buscarParaules(so, v);
    //dicTrie.buscarParaulesSopa(ss);
}