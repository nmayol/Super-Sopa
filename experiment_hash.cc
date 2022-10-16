#include "./SuperSopa/superSopa.hh"

#include <iostream>
#include <fstream>
#include <chrono>

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

//retorna el moment actual
auto moment () {
    return chrono::steady_clock::now();
}

void afegir_prefix(HashTableDictionary& d, string s) {
    int n = s.size();

    string aux = "";
    for (int i = 0; i < n-1; ++i) {
        aux.push_back(s[i]);
        
        if (not d.comprovar(aux)) {
            d.afegir(aux);
        }
    }
}

int abs (int x) {
    if (x > 0) return x;
    return x*-1;
}

void mitjana (vector<double>& execucions, double& temps) {
    int n = execucions.size();

    double sumaT = 0;

    for (int i = 0; i < n; ++i) {
        sumaT += execucions[i];
    }

    temps = sumaT/n;
}

int main () {
    ifstream fp_in;
    ofstream fp_out;
    superSopa super_sopa;
    string pathSopes = "sopes.txt";
    string pathResultat = "./resultats/resultatHash.txt";
    string pathDiccionari = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, pathDiccionari);

    HashTableDictionary hash_table(diccionari.size());
    HashTableDictionary prefixos(diccionari.size()*10);  

    for (int i = 0; i < diccionari.size(); ++i) {
        afegir_prefix(prefixos, diccionari[i]);
        hash_table.afegir(diccionari[i]);
    }

    //EXPERIMENT COMPROVAR
    fp_in.open(pathSopes); 
    fp_out.open(pathResultat);

    char s;
    int n;

    for (int nSopes = 0; nSopes < 100; ++nSopes) {
        //llegir sopa
        fp_in >> n;
        Sopa sopa = Sopa(n, vector<char>(n, '#'));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                fp_in >> s;
                sopa[i][j] = s;
            }
        }

        //resoldre-la 10 cops
        vector<double> execucions; //temps de cada execució
        vector<int> nTrobades;
        for (int cops = 0; cops < 10; ++cops) {
            map<string, int> resultatHashTable;

            auto begin = moment();
            resultatHashTable = super_sopa.resoldre(hash_table, prefixos, sopa);
            auto end = moment();

            double t = chrono::duration_cast<chrono::microseconds>(end - begin).count();

            execucions.push_back(t);
            nTrobades.push_back(resultatHashTable.size());
        }

        double t;
 
        mitjana(execucions, t);

        fp_out << "Sopa: " << nSopes+1 << endl;
        fp_out << "Mida:" << n << endl;
        fp_out << "Temps: " << t << endl; //<< endl;

        for (int i = 0;  i < nTrobades.size(); ++i) fp_out << nTrobades[i] << ' ';
        fp_out << endl;
    }

    fp_in.close();    
    fp_out.close();   
}
