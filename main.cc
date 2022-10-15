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
        
        if (i > 1 and not d.comprovar(aux)) {
            d.afegir(aux);
        }
    }
}

int main () {
    /*string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, path);

    //AFEGIR ELEMENTS ALS DICCIONARIS

    //vector ordenat   
    SortedVector sorted_vector;    
    auto begin = moment();
    sorted_vector.afegir(diccionari);    
    auto end = moment();

    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    //trie
    TrieDictionary trie;
    begin = moment();

    for (int i = 0; i < diccionari.size(); ++i) {
        //trie.afegir(diccionari[i]);
    }

    end = moment();

    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    //bloom filter
    BloomFilterDictionary bloom_filter;
    begin = moment();

    for (int i = 0; i < diccionari.size(); ++i) {
        bloom_filter.afegir(diccionari[i]);
    }

    end = moment();

    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    //hash table
    HashTableDictionary hash_table(diccionari.size());
    begin = moment();

    for (int i = 0; i < diccionari.size(); ++i) {
        hash_table.afegir(diccionari[i]);
    }

    end = moment();

    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    
    //GENERAR SOPA
    int n = 10;
    Sopa sopa = Sopa(n,vector<char>(n, '#'));
    superSopa super_sopa;    
    
    //super_sopa.generarSopa(n, sopa);


    //RESOLDRE SOPA
    super_sopa.resoldre(sorted_vector, sopa);

    super_sopa.resoldre(hash_table, sopa);

    super_sopa.resoldre(bloom_filter, sopa);

    super_sopa.resoldre(trie, sopa);  */

    Sopa sopa = {{'a', 'b', 'u', 's'},
                {'e', 'f', 'g', 'h'},
                {'i', 'j', 'k', 'l'},
                {'m', 'n', 'o', 'p'}};

    //sopa = {{'a', 'b', 'u'}, 
            //{'d', 'e', 's'}, 
            //{'g', 'h', 'i'}};

    string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;
    int maxim = 0;

    llegir_fitxer(diccionari, path);

    HashTableDictionary hash_table(diccionari.size());
    HashTableDictionary prefixos(diccionari.size()*10);  
    superSopa super_sopa;  

    for (int i = 0; i < diccionari.size(); ++i) {
        if (diccionari[i].length() > maxim) maxim = diccionari[i].length();
        afegir_prefix(prefixos, diccionari[i]);
        hash_table.afegir(diccionari[i]);
    }

    Sopa matriu = Sopa(8, vector<char>(8, '#'));
    super_sopa.generarSopa(diccionari, matriu);
    
    for (int i = 0; i < matriu.size(); ++i) {
        for (int j = 0; j < matriu.size(); ++j) {
            cout << matriu[i][j] << ' ';
        }
        cout << endl;
    }    

    map<string, int> resultat = super_sopa.resoldre(hash_table, prefixos, matriu, maxim);
    map<string, int>::iterator it;
    
    cout << "resultat" << endl;
    for (it = resultat.begin(); it != resultat.end(); ++it) {
        cout << it->first << ' ' << it->second << ' ' << endl;
    }
}


//chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//chrono::steady_clock::time_point end = chrono::steady_clock::now();