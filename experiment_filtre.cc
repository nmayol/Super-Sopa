#include <iostream>
#include <fstream>
#include <chrono>
#include <map>

#include "./SuperSopa/superSopa.hh"

using namespace std;

//retorna el moment actual
auto moment () {
    return chrono::steady_clock::now();
}

void llegir_fitxer (vector<string>& v, const string& path) {
    ifstream fp_in;
    string a;
    fp_in.open(path);
    while (fp_in >> a) {
        v.push_back(a);
    }
    fp_in.close(); 
}

void afegir_prefix (BloomFilterDictionary& d, string s) {
    int n = s.size();

    string aux = "";
    for (int i = 0; i < n-1; ++i) {
        aux.push_back(s[i]);
        
        if (not d.comprovar(aux)) {
            d.afegir(aux);
        }
    }
}

void mitjana (vector<pair<double, int>>& execucions, double& temps, int& errors) {
    int n = execucions.size();

    double sumaT = 0;
    double sumaE = 0;

    for (int i = 0; i < n; ++i) {
        sumaT += execucions[i].first;
        sumaE += execucions[i].second;
    }

    temps = sumaT/n;
    errors = sumaE/n;
}

int main () {
    ifstream fp_in;
    ofstream fp_out;
    superSopa super_sopa;
    string pathSopes = "sopes.txt";
    string pathResultat = "./resultats/resultatFiltre.txt";
    string pathDiccionari = "./diccionaris/quijote-vocabulary-6.txt";

    //llegir diccionari    
    vector<string> diccionari;

    llegir_fitxer(diccionari, pathDiccionari);
    
    BloomFilterDictionary bloom_filter(diccionari.size());
    BloomFilterDictionary prefixos(diccionari.size()*2);

    TrieDictionary trie; 
    sort(diccionari.begin(), diccionari.end());

    int meitat = diccionari.size()/2;
    for (int i = meitat; i < diccionari.size(); ++i) trie.afegir(diccionari[i]);
    for (int j = meitat - 1; j >= 0; --j) trie.afegir(diccionari[j]);

    auto begin = moment();
    for (int i = 0; i < diccionari.size(); ++i) {
        afegir_prefix(prefixos, diccionari[i]);
        bloom_filter.afegir(diccionari[i]);
    } 
    auto end = moment(); 

    double ta = chrono::duration_cast<chrono::microseconds>(end - begin).count();
    
    //EXPERIMENT COMPROVAR
    fp_in.open(pathSopes); 
    fp_out.open(pathResultat);

    fp_out << ta << endl;

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
        vector<pair<double, int>> execucions; //temps i errors de cada execuci??
        int trobadesFiltre = 0, trobadesVector = 0;
        for (int cops = 0; cops < 10; ++cops) {            
            auto begin = moment();
            trobadesFiltre = super_sopa.resoldre(bloom_filter, prefixos, sopa);
            auto end = moment();       

            trie.iniciarResultat();
            super_sopa.resoldre(trie, sopa);
            
            double t = chrono::duration_cast<chrono::microseconds>(end - begin).count();
            
            int e = trobadesFiltre - trie.paraulesTotals();
            
            execucions.push_back({t, e});           
        }        

        double t;
        int e;
        mitjana(execucions, t, e);

        //nombre de la sopa, mida, temps, paraules vector, paraules filtre, falsos positius
        fp_out << nSopes+1 << ' ' << n << ' ' << t << ' ' << trie.paraulesTotals() << ' ' << trobadesFiltre << ' ' << e << endl;
    }

    fp_in.close();    
    fp_out.close();
}