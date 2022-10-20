#include "./Filtre Bloom/diccBloomFilter.hh"

#include <iostream>
#include <fstream>

using namespace std;

int main () {
    vector<string> paths = {"./diccionaris/mare-balena-vocabulary-3.txt",
                            "./diccionaris/dracula-vocabulary-4.txt",
                            "./diccionaris/quijote-vocabulary-6.txt"};

    for (string path : paths) {
        cout << "Fitxer: " << path << endl;

        BloomFilterDictionary b;
        vector<string> totes;  

        ifstream fp_in;
        string a;
        fp_in.open(path);
        while (fp_in >> a) {
            totes.push_back(a);
        }
        fp_in.close(); 
		
		int mida = totes.size();
        cout << "Mida: " << mida << endl;

        int encerts = 0, comprovacions = 0;
        int fPositius = 0, fNegatius = 0;
        for (int i = 0; i < mida; ++i) {
            string w = totes[i];
            b.afegir(w);
		
			//ha de sortir positiu
            for (int j = 0; j <= i; ++j) {
                ++comprovacions;
                if (not b.comprovar(totes[j])) ++fNegatius;
                else ++encerts;
            }
			
			//ha de sortit negatiu
            for (int j = i+1; j < mida; ++j) {
                ++comprovacions;
                if (b.comprovar(totes[j])) ++fPositius;
                else ++encerts;
            }
        }

        cout << "Falsos negatius: " << fNegatius << endl;
        cout << "Falsos positius: " << fPositius << endl;
        cout << "Errors totals: " << fNegatius+fPositius << endl;
        cout << "Encerts: " << encerts << endl;
        cout << "Comprovacions totals: " << comprovacions << endl;
    }    
}
