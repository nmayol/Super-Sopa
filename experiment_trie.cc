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

auto moment () {
    return chrono::steady_clock::now();
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
    string pathResultat = "./resultats/resultatTrie.txt";
    string pathDiccionari = "./diccionaris/quijote-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, pathDiccionari);

    TrieDictionary trie; 
    sort(diccionari.begin(), diccionari.end());

    int meitat = diccionari.size()/2;
    for (int i = meitat; i < diccionari.size(); ++i) trie.afegir(diccionari[i]);
    for (int j = meitat - 1; j >= 0; --j) trie.afegir(diccionari[j]);
    trie.simplificaArbre();
    
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
        for (int cops = 0; cops < 10; ++cops) {
            map<string, int> resultatTrieDictionary;

            auto begin = moment();
            trie.buidarResultats();
            trie.iniciarResultat();
            super_sopa.resoldre(trie, sopa);
            auto end = moment();

            double t = chrono::duration_cast<chrono::microseconds>(end - begin).count();

            execucions.push_back(t);
        }
        
        double t;
 
        mitjana(execucions, t);      

        fp_out << nSopes+1 << ' ' << n << ' ' << t << ' ' << ' ' << trie.paraulesTotals() << endl;
    }

    fp_in.close();    
    fp_out.close();   
}