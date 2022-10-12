#include "diccTrie.hh"

TrieDictionary::TrieDictionary() {
    arrel = nullptr;
}

bool TrieDictionary::esbuit() const {
    return (arrel == nullptr);
}

void TrieDictionary::afegirRec(node_trie* n, const string& info, int i) {

    // guardem el primer caracter a un string.
    string s(1, info[i]);

    if (n == nullptr) {             /* arbre buit */
        node_trie* aux;
        aux = new node_trie;

        aux->info = s;
        aux->dre = nullptr;
        aux->esq = nullptr;
        aux->cnt = nullptr;
        
        n = aux;

        ++i;

        /* si es la ultima lletra, guardem com a final de paraula i
           acabem amb recursivitat.
        */
        if (i < info.size()) afegirRec(n->cnt, info, i);
        else n->finalparaula = true;
    }
    else if (n->info == s) {            /* cas 1: mateix caracter */
        ++i;
        if (i < info.size()) afegirRec(n->cnt, info, i);
        else n->finalparaula = true;
    }
    else if (n->info > s) afegirRec(n->dre, info, i);   /* cas 2: busquem dreta */
    else if (n->info < s) afegirRec(n->esq, info, i);   /* cas 3: busquem esquerra*/
    
}

void TrieDictionary::afegir_node(const string& p) {

    /* comencem crida recursiva */
    afegirRec(arrel, p, 0);
}

void TrieDictionary::llegirTrie() {

    cout << "Mida diccionari: ";
    int mida;
    cin >> mida;

    cout << "Introdueix les paraules" << endl;
    for (int i = 0; i < mida; ++i) {

        string p;
        cin >> p;

        afegir_node(p);     
    }
    cout << "arbre llegit correctament!" << endl;
    // agrupar prefixes.
}

