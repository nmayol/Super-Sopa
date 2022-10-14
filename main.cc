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

int main () {
    string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, path);

    //AFEGIR ELEMENTS ALS DICCIONARIS
    //vector ordenat   
    SortedVector sorted_vector;    
    auto begin = moment();

    for (int i = 0; i < diccionari.size(); ++i) {
        //sorted_vector.afegir(diccionari[i]);
    }

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
    HashTableDictionary hash_table;
    begin = moment();

    for (int i = 0; i < diccionari.size(); ++i) {
        //hahs_table.afegir(diccionari[i]);
    }

    end = moment();

    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    
    //GENERAR SOPA
    int n = 10;
    Sopa sopa = Sopa(n,vector<char>(n, '#'));
    superSopa super_sopa;    
    
    super_sopa.generarSopa(n, sopa);


    //RESOLDRE SOPA
    super_sopa.resoldre(sorted_vector, sopa);

    super_sopa.resoldre(hash_table, sopa);

    super_sopa.resoldre(bloom_filter, sopa);

    super_sopa.resoldre(trie, sopa);     
}


//chrono::steady_clock::time_point begin = chrono::steady_clock::now();
//chrono::steady_clock::time_point end = chrono::steady_clock::now();