//programa per generar sopes i desar-les en un fitxer

#include <iostream>
#include <fstream>
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
    ofstream fw(path, ofstream::out);

    if (fw.is_open()) {
        int n = sopa.size();

        fw << n << ' ';

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                fw << sopa[i][j] << ' ';
            }
        }

        fw << '\n';
    }
    else cout << "Problem with opening file";

    fw.close();
}

int main () {
     string path = "./diccionaris/sopes.txt";

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