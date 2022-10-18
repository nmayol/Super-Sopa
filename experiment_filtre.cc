#include <iostream>
#include <fstream>
#include <chrono>
#include <map>
//#include <vector>

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

int abs (int x) {
    if (x > 0) return x;
    return x*-1;
}

int calcularFalsosPositius (map<string, int>& mapVector, map<string, int>& mapFiltre) {
    map<string,int>::iterator it, aux;
    int errors = 0;


    for (it = mapVector.begin(); it != mapVector.end(); ++it) {
        string p = it->first;
        int q1 = it->second;
        mapVector.erase(it);

        int q2 = 0;
        aux = mapFiltre.find(p);
        if (aux != mapFiltre.end()) {
            q2 = aux->second;
            mapFiltre.erase(aux);
        }
        
        errors += abs(q2-q1);
    }

    for (it = mapFiltre.begin(); it != mapFiltre.end(); ++it) {
        errors += it->second;
    }

    return errors;
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
    string pathDiccionari = "./diccionaris/mare-balena-vocabulary-3.txt";

    //llegir diccionari    
    vector<string> diccionari;

    llegir_fitxer(diccionari, pathDiccionari);
    
    BloomFilterDictionary bloom_filter(diccionari.size());
    BloomFilterDictionary prefixos(diccionari.size()*10);
    SortedVector sorted_vector;
    sorted_vector.afegir(diccionari);    

    for (int i = 0; i < diccionari.size(); ++i) {
        afegir_prefix(prefixos, diccionari[i]);
        bloom_filter.afegir(diccionari[i]);
    } 

    //EXPERIMENT COMPROVAR
    fp_in.open(pathSopes); 
    fp_out.open(pathResultat);

    char s;
    int n;

    for (int nSopes = 0; nSopes < 100; ++nSopes) {
        cout << "Sopa: " << nSopes << endl;
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
        vector<pair<double, int>> execucions; //temps i errors de cada execució
        for (int cops = 0; cops < 10; ++cops) {
            cout << cops << endl;
            map<string, int> resultatFiltre;
            map<string, int> resultatVector;

            cout << "ep" << endl;

            auto begin = moment();
            super_sopa.resoldre(resultatFiltre, bloom_filter, prefixos, sopa);
            auto end = moment();

            cout << "haha" << endl;

            double t = chrono::duration_cast<chrono::microseconds>(end - begin).count();

            resultatVector = super_sopa.resoldre(sorted_vector, sopa);

            cout << "hola" << endl;

            int e = calcularFalsosPositius(resultatFiltre, resultatVector);
            cout << "e" << endl;
            execucions.push_back({t, e});

            cout << "fi" << endl;
        }

        double t;
        int e;
        mitjana(execucions, t, e);

        fp_out << "Sopa: " << nSopes+1 << endl;
        fp_out << "Mida:" << n << endl;
        fp_out << "Temps: " << t << endl;
        fp_out << "Errors: " << e << endl << endl;
    }

    fp_in.close();    
    fp_out.close();
}