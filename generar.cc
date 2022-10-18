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
void escriure_fitxer(Sopa& sopa, ofstream& fw) {
    
    int n = sopa.size();

    fw << n << ' ';

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fw << sopa[i][j];
        }
    }

    fw << endl;     
}

int main () {
    string path = "sopes.txt";
    vector<string> diccionari;
    superSopa super_sopa;

    ofstream fw(path, ofstream::out);

    llegir_fitxer(diccionari, path);   

    vector<string> p;/* = {"abus", "era", "acer", "baba", "frare","reina", "abandonar",
                        "aire", "malalt", "nemo", "seny", "severa", "guineu",
                        "gust", "has", "haja", "conve", "entes", "idea", "hostal"}; */
    int a;
    srand(time(NULL));
    for(int i = 0; i < 20; ++i) {
        a = rand() % diccionari.size();
        p.push_back(diccionari[a]);
    }
    
    
    for (int n = 10; n <= 55; n += 5) {
        for (int j = 0; j < 10; ++j) {
            Sopa matriu = Sopa(n, vector<char>(n, '#'));

            super_sopa.generarSopa(p, matriu);

            escriure_fitxer(matriu, fw);
        }
    }   

    fw.close();    
}