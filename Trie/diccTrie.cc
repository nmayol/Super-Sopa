#include "diccTrie.hh"

TrieDictionary::TrieDictionary() {
    arrel = nullptr;
    totalTrobat = 0;
}


void TrieDictionary::afegirRec(node_trie* &n, const string& info, int i) {

    string s(1, info[i]);

    if (n == nullptr) {             
        node_trie* aux;
        aux = new node_trie;

        aux->info = s;              
        aux->dre = nullptr;
        aux->esq = nullptr;
        aux->cnt = nullptr;
        aux->finalparaula = false;
        
        n = aux;
        ++i;

        if (i < info.size()) afegirRec(n->cnt, info, i);
        else n->finalparaula = true;
    }
    else if (n->info == s) {            
        ++i;
        if (i < info.size()) afegirRec(n->cnt, info, i);
        else n->finalparaula = true;
    }
    else if (n->info > s) afegirRec(n->dre, info, i);   
    else if (n->info < s) afegirRec(n->esq, info, i);
    
}

void TrieDictionary::afegir(const string& p) {

    afegirRec(arrel, p, 0);
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

void TrieDictionary::llegirTrie() {

    int mida;
    cin >> mida;

    for (int i = 0; i < mida; ++i) {

        string p;
        cin >> p;

        afegir(p);    
    }

}

void TrieDictionary::escriureRec(node_trie* n) const {

    if (n != nullptr) {
        cout << " " << n->info;
        escriureRec(n->dre);
        escriureRec(n->cnt);
        escriureRec(n->esq);
    }
    else cout << " 0";
}

void TrieDictionary::escriure() const {

    escriureRec(arrel);
}

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

    int j = 0;
    if (n == nullptr) {
        r = false;
        return;
    }
    else if (i == par.size()) {
        if (n->finalparaula) results[par]++;
        r = true;
        return;
    }
    else if (n->info[0] == par[i] and inclouParaula(par, n->info, i, j)) {
        
        if (j == 0) {
            i += n->info.size();
            r = true;
            if (n->finalparaula and i == par.size()) {
                results[par]++;
                ++totalTrobat;
            }
            return;
        }
        else {
            int salt = n->info.size();
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

bool TrieDictionary::comprovar(const string& c) {

    bool r = false;
    existeixParaula(c, arrel, 0, r);
    return r;
}

void TrieDictionary::buidarResultats() {

    results.clear();
}

void TrieDictionary::imprimirResultats() const {

    map<string,int>::const_iterator it = results.begin();

    while (it != results.end()) {
        cout << it->first << ' ' << it->second << endl;
        ++it;
    }
}

int TrieDictionary::midaMap() const {

    return results.size();
}

int TrieDictionary::paraulesTotals() const {
    return totalTrobat;
}

void TrieDictionary::iniciarResultat() {
    totalTrobat = 0;
}