#include "./SuperSopa/superSopa.hh"
using namespace std;

int main() {
    
    cout << "Introdueix la mida de la Super Sopa: ";
    
    
    int n;
    cin >> n;
    cout << n << endl;
    
    superSopa ss = superSopa(n);
    cout << "Llegim la Super Sopa" << endl;
    ss.llegir();
    
    // Un cop llegida la Super Sopa, inicialitzem els diccionaris.

    char metode;
    cout << "Quin metode vols utilitzar per buscar les paraules?" << endl;
    cout << "v - sorted vector / t - trie / b - filtre bloom / h - taula hash" << endl;
    cin >> metode;

    /*  He pensat que millor fer una execucio per metode, ja que el 
        diccionari es molt pesat, per tant, nomes el guardem per la 
        estructura de dades que ho necessita.

        Com les sopes les genera un altre programa, podem executar el
        programa 4 vegades amb la mateixa sopa.

        Tambe al tenir les sopes ja generades, podem crear els outpus
        i comprovarne els seus resultats.
    */

    if (metode == 'v') {

        cout << "Heu escollit el metode SORTED VECTOR" << endl;
        /*  Lectura diccionari.
        */
        cout << "Diccionari guardat correctament!" << endl;
        ss.resoldreVector ();
        cout << " FET! Per veure la solucio sha d'anar al fitxer out.txt del directori Sorted Vector.";
        /*  Metode per bucar paraules a la Sopa.
            + output de paraules trobades i temps tardat.
        */
    }
    else if (metode == 't') {

        cout << "Heu escollit el metode TRIE" << endl;
        /* Lectura diccionari -> guardar en arbre.
        */
        TrieDictionary dicTrie = TrieDictionary();
        dicTrie.llegirTrie();
        cout << "Diccionari guardat correctament!" << endl;

        /*  Metode per bucar paraules a la Sopa.
            + output de paraules trobades i temps tardat.
        */
        cout << "Imprimim el diccionari guardat:" << endl;
        dicTrie.escriure();
        cout << endl << "Ara simplifiquem" << endl;
        dicTrie.simplificaArbre();
        dicTrie.escriure();
        cout << endl;
    }
    else if (metode == 'b') {

        cout << "Heu escollit el metode FILTRE BLOOM" << endl;
        /* Lectura diccionari
        */
        cout << "Diccionari guardat correctament!" << endl;

        /*  Metode per bucar paraules a la Sopa.
            + output de paraules trobades i temps tardat.
        */
    }
    else if (metode == 'h'){

        cout << "Heu escollit el metode TAULA HASH" << endl;
        /* Lectura diccionari
        */
        cout << "Diccionari guardat correctament!" << endl;

        /*  Metode per bucar paraules a la Sopa.
            + output de paraules trobades i temps tardat.
        */
    }

    
    


}
