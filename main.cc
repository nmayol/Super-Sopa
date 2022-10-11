

#include "./SuperSopa/superSopa.hh"

using namespace std;

int main () {
    // n es la mida de la sopa
    int n;

    cout << "Introdueix la mida de la sopa: ";
    cin >> n;
    cout << "Ara es creara la sopa de mida " << n << endl;

    superSopa s = superSopa(n);
    cout << "CREADA!! Ara afegim les paraules..." << endl;

    // poso aixo per provar
    
    vector <string> dic = {
         "abandonaren", "abandonat", "abans", "abatut", "abocada", "abocant",
                           "abracada", "abracades", "abracaren", "abracava", "abrandat", "abriga"
                            "abrigava", "abrusa", "abrusaren", "abscondir", "absencies", "absolta",
                            "absolutament" };





    //s.costruirSopa(dic);
    s.construirParaules(dic);
    s.imprimirSopaTerminal();
    /*
    cout << "Sorted Vector:" << endl;
    s.resoldreVector();
    */
    
    
}