#include "diccTrie.hh"


const vector<pair<int,int>> DIR = {make_pair( 1, 0), make_pair( 1, 1),
                                   make_pair( 0, 1), make_pair(-1, 1),
                                   make_pair(-1, 0), make_pair(-1,-1),
                                   make_pair( 0,-1), make_pair( 1,-1)};

TrieDictionary::TrieDictionary() {
    arrel = nullptr;
}

bool TrieDictionary::esbuit() const {
    return (arrel == nullptr);
}

void TrieDictionary::afegirRec(node_trie* &n, const string& info, int i) {

    // guardem el primer caracter a un string.
    string s(1, info[i]);

    if (n == nullptr) {             /* arbre buit */
        node_trie* aux;
        aux = new node_trie;

        aux->info = s;
        aux->dre = nullptr;
        aux->esq = nullptr;
        aux->cnt = nullptr;
        aux->finalparaula = false;
        aux->cerca = 0;
        
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

void TrieDictionary::afegir(const string& p) {

    /* comencem crida recursiva */
    afegirRec(arrel, p, 0);
}

void TrieDictionary::llegirTrie() {

    cout << "Mida diccionari: ";
    int mida;
    cin >> mida;

    for (int i = 0; i < mida; ++i) {

        string p;
        cin >> p;

        afegir(p);    
    }
    cout << "arbre llegit correctament!" << endl;
    // agrupar prefixes.
}

void TrieDictionary::simplificaRec(node_trie* &n) {

    if (n != nullptr) {

        node_trie* seg = n->cnt;

        if (n->dre == nullptr and n->esq == nullptr and seg != nullptr and seg->dre == nullptr and seg->esq == nullptr and not n->finalparaula) {
            n->info += seg->info;
            n->finalparaula = seg->finalparaula;
            n->cnt = seg->cnt;
            simplificaRec(n);
        }
        simplificaRec(n->dre);
        simplificaRec(n->cnt);
        simplificaRec(n->esq);
    }
}

void TrieDictionary::simplificaArbre() {

    simplificaRec(arrel);
}

void TrieDictionary::escriureRec(node_trie* n) {

    if (n != nullptr) {
        cout << " " << n->info;
        escriureRec(n->dre);
        escriureRec(n->cnt);
        escriureRec(n->esq);
    }
    else cout << " 0";
}

void TrieDictionary::escriure() {
/* Pre: cert */ 
/* Post: El canal estandar de sortida cont� el recorregut en inordre d'a */ 
    escriureRec(arrel);
}

bool TrieDictionary::posok(int i, int j, int n, const vector<vector<bool>>& v) {

    return (i >= 0 and i < n and j >= 0 and j < n and not v[i][j]);
}

// a: par, b: n
bool TrieDictionary::inclouParaula(const string& a, const string& b, int i, int& k) {

    bool resultat = true;

    if (a.size() - i <= b.size()) {
        k = 0;
        int mida = a.size() - i;
        while (k < mida) {
            if (a[i] != b[k]) resultat = false;
            ++i; ++k;
        }
        k = 0;
    }
    else {
        k = 0;
        while (k < b.size()) {

            if (a[i] != b[k]) resultat = false;
            ++i; ++k;
        }
        k = 1;
    }
    return resultat;

}

void TrieDictionary::existeixParaula(const string& par, node_trie* n, int i, bool& r) {

    if (n != nullptr) cout << "n: " << n->info << " par: " << par << " i: " << i << endl;
    int j = 0;
    if (n == nullptr) {
        r = false;
        return;
    }
    else if (i == par.size()) {
        if (n->finalparaula) cout << "TROBAT " << par << endl;
        r = true;
        return;
    }
    else if (n->info.size() == par.size() and n->info == par) {
        existeixParaula(par, n->cnt, i+1, r);
    }
    // act - aca
    else if (inclouParaula(par, n->info, i, j)) {
        
        if (j == 0) {
            i += n->info.size();
            r = true;
            if (n->finalparaula and i == par.size()) cout << "TROBAT " << par << endl;
            
            return;
        }
        else {
            int salt = n->info.size();
            cout << endl << salt << endl;
            existeixParaula(par, n->cnt, i+salt, r);
        } 
        
    }
    else if (n->info[0] < par[i]) {
        existeixParaula(par, n->esq, i, r);
    }
    else if (n->info[0] > par[i]) {
        existeixParaula(par, n->dre, i, r);
    }
    
}

void TrieDictionary::calculaDireccions(const sopa& so, matbool& v, const string& par, int i, int j) {

    v[i][j] = true;
    //string par(1, so[i][j]);

    for (int k = 0; k < DIR.size(); ++k) {

        int di = i + DIR[k].first;
        int dj = j + DIR[k].second;

        if (posok(di, dj, so.size(), v)) {

            string seg(1, so[di][dj]);
            string suma = par + seg;

            bool existeix = false;
            existeixParaula(suma, arrel, 0, existeix);

            if (existeix) {
                calculaDireccions(so, v, suma, di, dj);
            }
        }
    }
}

void TrieDictionary::buscarParaules(const sopa& so, matbool& v) {

    for (int i = 0; i < so.size(); ++i) {
        for (int j = 0; j < so.size(); ++j) {

            string primer(1, so[i][j]);
            bool existeix = false;

            existeixParaula(primer, arrel, 0, existeix);
            cout << existeix << endl;

            if (existeix) {
                calculaDireccions(so, v, primer, i,j);
            }
        }
    }
}

bool TrieDictionary::comprovar(const string& c) {

    bool r = false;
    existeixParaula(c, arrel, 0, r);
    return r;
}