#include "superSopa.hh"



// crea una super sopa on l'atribut sopa té mida nxn
superSopa::superSopa(int mida) {
    n = mida;
    so.resize(n,vector<char >(n,NULL));
}

void superSopa::llegirDiccionari (vector<string>& v) {
    int m = v.size();
    for (int i = 0; i < m; ++i) {

    }
}

void superSopa::resoldreVector () {}

void superSopa::resoldreTrie () {}

void superSopa::resoldreBloom () {}

void superSopa::resoldreDHash () {}

void superSopa::imprimirSopa () {
    for (int i = 0; i < n; ++i) {
        cout << so[i][0];
        for (int j = 1; j < n; ++j) cout << ' ' << so[i][j];
        cout << endl;
    }
}



void superSopa::afegir (string s) {   
    // Escull una posició random i hi posa la paraula.
}

// Retorna true si ha pogut posar la lletra a la posició (i,j).
bool superSopa::afegirLletra (const int& i,const int& j, const int& c) {   
    // Escull una posició so[i][j] i hi posa la lletra.
    if(compleixLimits(i,j) and (so[i][j] == NULL or so[i][j] == c)) {
        so[i][j] = c;
        return true;
    }
    return false;
}

// Retorna true si la posició (i,j) és una posició de la Sopa.
bool superSopa::compleixLimits(const int& i,const int& j) {
    return(i >= 0 and j >= 0 and i < n and j < n);
}