

#include "./SuperSopa/superSopa.hh"

using namespace std;

int main () {
    // n es la mida de la sopa
    int n; cin >> n;
    superSopa s = superSopa(n);

    // poso aixo per provar
    
    vector <string> dic = {
         "abandonaren", "abandonat", "abans", "abatut", "abocada", "abocant",
                           "abracada", "abracades", "abracaren", "abracava", "abrandat", "abriga"
                            "abrigava", "abrusa", "abrusaren", "abscondir", "absencies", "absolta",
                            "absolutament" };





    s.costruirSopa(dic);
    
    s.imprimirSopa();
    
    cout << "Sorted Vector:" << endl;
    s.resoldreVector();
    
    
    
}