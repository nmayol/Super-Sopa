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
    string pathResultat = "./resultats/resultatVector.txt";
    string pathDiccionari = "./diccionaris/mare-balena-vocabulary-3.txt";

    vector<string> diccionari;

    llegir_fitxer(diccionari, pathDiccionari);

    SortedVector sorted_vector;
    sorted_vector.afegir(diccionari);  

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
        int result = 0;
        vector<double> execucions; //temps de cada execució
        for (int cops = 0; cops < 10; ++cops) {
            sorted_vector.netejaTrobades();

            auto begin = moment();
            super_sopa.resoldre(sorted_vector, sopa);
            auto end = moment();

            double t = chrono::duration_cast<chrono::microseconds>(end - begin).count();
            result += sorted_vector.consultarResults();

            execucions.push_back(t);
        }
        
        double t; 
        mitjana(execucions, t);

        result /= 10;

        fp_out << nSopes+1 << ' ' << n << ' ' << t << ' ' << result << endl;
    } 
}