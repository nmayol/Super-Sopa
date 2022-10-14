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

void TrieDictionary::afegir_node(const string& p) {

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

        afegir_node(p);    
    }
    cout << "arbre llegit correctament!" << endl;
    // agrupar prefixes.
}

void TrieDictionary::simplificaRec(node_trie* &n) {

    if (n != nullptr) {

        node_trie* seg = n->cnt;

        if (seg != nullptr and seg->dre == nullptr and seg->esq == nullptr and not n->finalparaula) {
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

/* nomes funciona amb arbre no reduit */
bool TrieDictionary::buscarChar(const string& c, node_trie* n) {

    if (n != nullptr) {

        cout << "n: " << n->info << " c: " << c << endl;
        if (c == n->info) {
            
            cout << "cas1: son iguals." << endl;
            if (n->finalparaula) cout << "TROBAT " << c << endl;
            return true;
        }
        else if (c < n->info) {
            buscarChar(c, n->dre);
        }
        else if (c > n->info) {
            buscarChar(c, n->esq);
        }
    }
    else {
        return false;
        //n = nullptr;
    }
}

bool TrieDictionary::posok(int i, int j, int n, const vector<vector<bool>>& v) {

    return (i >= 0 and i < n and j >= 0 and j < n and not v[i][j]);
}

bool TrieDictionary::busquemParaula(const string& c, node_trie* n, int i, bool& b) {

    if (n == nullptr or i == c.size()) {
        //cout << "FALSE" << endl;
        b = false;
        return false;
    }
    else {

        string letter(1, c[i]);
        cout << "c: " << c << " i: " << letter << " n: " << n->info << endl;

        if (letter == n->info) {

            //cout << "cas 1: iguals" << endl;
            if (n->finalparaula and i == c.size() - 1) {
                //cout << "n: " << n->finalparaula << "i: " << i << endl;
                cout << "TRUE" << endl << "TROBAT " << c << endl;
                b = true;
                if (n->cnt == nullptr) b = false;
                return true;
            }
            else if (i == c.size() - 1) {
                //cout << "TRUE" << endl;
                b = true;
                return true;
            }
            else {
                string cc(1, c[i+1]);
                if (n->cnt != nullptr) {
                    //if (n->cnt->info == cc) busquemParaula(c, n->cnt, i+1, b);
                    //else if (n->cnt->info > cc) busquemParaula(c, n->cnt->dre, i+1, b);
                    //else busquemParaula(c, n->cnt->esq, i+1, b);
                    //else busquemParaula(c, n->cnt, i, b);
                    busquemParaula(c, n->cnt, i+1, b);
                }
            }
        }
        else if (letter < n->info) {
            //cout << "dreta" << endl;
            busquemParaula(c, n->dre, i, b);
        }
        else if (letter > n->info) {
            //cout << "esquerra" << endl;
            busquemParaula(c, n->esq, i, b);
        }
    }
    return false;
}

void TrieDictionary::cercaDireccions(const superSopa& ss, vector<vector<bool>>& v, int i, int j, const string& par, int ind) {

    //v[i][j] = true;

    for (int k = 0; k < DIR.size(); ++k) {

        int diri = i + DIR[k].first;
        int dirj = j + DIR[k].second;

        if (posok(diri, dirj, ss.mida(), v)) {

            string c(1, ss.getchar(diri, dirj));
            string aux = par+c;
            
            bool r = false;
            bool f = busquemParaula(aux, arrel, 0, r);
            //if (r) cout << "true" << endl;
            //else cout << "false" << endl;
            if (r) {
                v[diri][dirj] = true;
                cercaDireccions(ss, v, diri, dirj, aux, 0);
                v[diri][dirj] = false;
            }
            
        }
    }
}

void TrieDictionary::buscarParaulesSopa(const superSopa& ss) {

    int mida = ss.mida();
    

    for (int i = 0; i < mida; ++i) {
        for (int j = 0; j < mida; ++j) {

            node_trie* n = arrel;
            
            vector<vector<bool>> visit(mida, vector<bool> (mida, false));
            string s(1, ss.getchar(i, j));
            cout << endl << "BEGIN " << s << endl;
            
            int id = 0;
            
            if (buscarChar(s, n)) {
                // mirem les direccions.
                visit[i][j] = true;
                //cout << "cerca cap a les direccions" << endl;
                
                cercaDireccions(ss, visit, i, j, s, id);
            }
        }
    }
}