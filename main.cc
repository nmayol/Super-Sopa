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

int calcularFalsosPositius (map<string, int>& mapHash, map<string, int>& mapFiltre) {
    map<string,int>::iterator it, aux;
    int errors = 0;
    cout << "errors" << endl;
    for (it = mapHash.begin(); it != mapHash.end();) {
        string p = it->first;
        cout << p << endl;
        int q1 = it->second;
        ++it;
        mapHash.erase(it);

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

//retorna el moment actual
auto moment () {
    return chrono::steady_clock::now();
}

void afegir_prefix(HashTableDictionary& d, string s) {
    int n = s.size();

    string aux = "";
    for (int i = 0; i < n-1; ++i) {
        aux.push_back(s[i]);
        
        if (i > 1 and not d.comprovar(aux)) {
            d.afegir(aux);
        }
    }
}

int main () {
    /*Sopa sopa = {{'a', 'b', 'u', 's'},
                {'e', 'f', 'g', 'h'},
                {'i', 'j', 'k', 'l'},
                {'m', 'n', 'o', 'p'}};

    //sopa = {{'a', 'b', 'u'}, 
            //{'d', 'e', 's'}, 
            //{'g', 'h', 'i'}};*/
    ifstream fp_in;
    ofstream fp_out;
    superSopa super_sopa;
    string pathSopes = "sopes.txt";
    string pathResultat = "resultatFiltre.txt";
    string pathDiccionari = "./diccionaris/mare-balena-vocabulary-3.txt";

    string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;
    int maxim = 0;

    llegir_fitxer(diccionari, path);

    HashTableDictionary hash_table(diccionari.size());
    HashTableDictionary prefixos(diccionari.size()*10);  
    //superSopa super_sopa;  

    for (int i = 0; i < diccionari.size(); ++i) {
        if (diccionari[i].length() > maxim) maxim = diccionari[i].length();
        afegir_prefix(prefixos, diccionari[i]);
        hash_table.afegir(diccionari[i]);
    }

    int n = 4;
    Sopa matriu = Sopa(n, vector<char>(n, '#'));

    vector<string> p = {"abus", "era", "acer", "baba", "frare","reina", "abandonar",
                        "aire", "malalt", "nemo", "seny", "severa", "guineu",
                        "gust", "has", "haja", "conve", "entes", "idea", "hostal"};

    super_sopa.generarSopa(p, matriu);
    
    for (int i = 0; i < matriu.size(); ++i) {
        for (int j = 0; j < matriu.size(); ++j) {
            cout << matriu[i][j] << ' ';
        }
        cout << endl;
    }    

    map<string, int> resultat = super_sopa.resoldre(hash_table, prefixos, matriu);
    map<string, int>::iterator it;
    
    cout << "RESULTAT HASH" << endl;
    for (it = resultat.begin(); it != resultat.end(); ++it) {
        cout << it->first << ' ' << it->second << ' ' << endl;
    }

    SortedVector vector;
    vector.afegir(diccionari);
    
    map<string, int> resultat2 = super_sopa.resoldre(vector, matriu);

    cout << "RESULTAT VECTOR" << endl;
    for (it = resultat2.begin(); it != resultat2.end(); ++it) {
        cout << it->first << ' ' << it->second << ' ' << endl;
    }

    //cout << calcularFalsosPositius(resultat, resultat2) << endl;
}


//chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//chrono::steady_clock::time_point end = chrono::steady_clock::now();