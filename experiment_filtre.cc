#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

//#include "./SuperSopa/superSopa.hh"

using namespace std;

typedef vector<vector<char >> Sopa;

int main () {
    ifstream fp_in;
    string path = "sopes.txt";

    fp_in.open(path);    

    char s;
    int n;

    fp_in >> n;
    Sopa sopa = Sopa(n, vector<char>(n, '#'));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fp_in >> s;
            sopa[i][j] = s;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << sopa[i][j] << ' ';
        }
        cout << endl;
    }

    fp_in.close();    
}