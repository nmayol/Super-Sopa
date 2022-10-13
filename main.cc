#include "./SuperSopa/superSopa.hh"

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

int main () {
    int n = 10;
    string path = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, path);

    //temps vector ordenat    
    SortedVector sorted_vector;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    //temps trie

    //temps bloom filter

    //temps hash table

    BloomFilterDictionary bloom_filter;
    HashTableDictionary hash_table;
    TrieDictionary trie;

    
    

    
    
    //chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << std::endl;

    /*
    // n es la mida de la sopa
    int n;

    cout << "Introdueix la mida de la sopa: ";
    cin >> n;
    
    cout << "Utilitzem el diccionari Balena." << endl;
    vector<string> balena(5053);
    for (int i = 0; i < 5053; ++i) cin >> balena[i];
    cout << "Diccionari llegit." << endl;

    cout << "Ara es creara la sopa de mida " << n << endl;

    superSopa s = superSopa(n);
    cout << "CREADA!! Ara afegim les paraules..." << endl;

    s.construirParaules(balena);
    s.imprimirSopaTerminal();
    s.imprimirSopa ();*/    
}