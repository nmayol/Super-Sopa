//programa per generar sopes i desar-les en un fitxer

#include <iostream>
#include "./SuperSopa/superSopa.hh"

using namespace std;

void llegir_fitxer (vector<string>& v, const string& path) {
    ifstream fp_in;
    string a;
    fp_in.open(path);
    while (fp_in >> a) {
        v.push_back(a);
    }
    fp_in.close(); 
}

//escriu la sopa al final del fitxer path
void escriure_fitxer(Sopa& sopa, const string& path) {

}

int main () {
     string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, path);

    superSopa super_sopa;
    int n = 10; //mida supersopa

    for (int i = 0; i < 100; ++i) {
        Sopa matriu = Sopa(n, vector<char>(n, '#'));

        super_sopa.generarSopa(diccionari, matriu);

        escriure_fitxer(matriu, "path del fitxer on guardem les sopes");
    }
}