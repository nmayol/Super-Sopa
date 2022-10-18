#include "superSopa.hh"

const vector<pair<int,int>> DIR = {{-1, -1}, {-1, 0}, {-1, 1},
                                   {0, -1}, {0, 1},
                                   {1, -1}, {1, 0}, {1, 1}};

const vector<int> SENTIT = {-1,1};

vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

//constructor buit
superSopa::superSopa() {    
    resultat = map<string, int>();
};

void superSopa::generarSopa (const vector<string>& dicc, Sopa& sopa) {
    int n = sopa.size();
    visitat = vector<vector<bool>> (n, vector<bool>(n, false));
    int paraules = dicc.size();     // paraules dintre diccionari
    int parSopa = 0;                // paraules dintre la SOPA

    srand(time(NULL));

    for(int k = 0; k < 20; ++k) {
        string p = dicc[k]; // paraula a colocar
        bool colocada = false;
        bool end = false;
        int provades = 0;
        bool ja = false;
        // generem rand posicio inicial
        srand(time(NULL)); 
        int i = rand() % n;
        int j = rand() % n;
        int i1 = i;
        int j1 = j;
        while(!colocada and provades < (n*n) ) {
            // calculem la posicio on comencem.
            bool start = false;
            ++j;
            if(j == n) {
                j = 0;
                ++i;
            }
            if(i == n) i = 0;
            //if(i == i1 and j == j1) ja = true;
            int io = i, jo = j;
             
            while (not start and not end) {            
                if (sopa[i][j] == '#' or (sopa[i][j] == p[0] and n < 6)) {  // comprovem si es una posicio valida, 
                    sopa[i][j] = p[0];                          // buida o amb la mateixa lletra q volem posar(la primera)
                    visitat[i][j] = true;                       // marquem com a visitada
                    start = true;                               // podem començar a colocar la resta de lletres
                }
                else {
                    ++j;                                        // anem a la seguent pos de la dreta(columna++)
                    if (j == n) {j = 0; ++i;}                   // arribem a lultima columna, anem a la seguent fila primera columna
                    if (i == n) {i = 0;}                        // areibem a lultima fila, tornem a la primera fila
                    if (i == io and j == jo) end = true;        // arribem a la primera pos q haviem comprovat, no hiha mes pos valides
                }
            }
            if (start) { // si trobem posicio valida per começar a colocar
                if (colocarParaulaRec(p, 1, i, j, sopa)) { // coloquem lletres restants
                    colocada =  true;
                    ++parSopa;
                }
            }
            ++provades;
        } 
        if (!colocada) cout << "No s'ha pogut colocar la paraula: " << p << endl;
           
    }
    cout << "Total paraules: " << parSopa << endl;

    // acabem de fer la sopa.
    omplebuits(sopa);
}

bool superSopa::colocarParaulaRec(const string& p, int l, int i, int j, Sopa& sopa) {
    int n = sopa.size();
    if (l == p.size()) return true; // si ja hem fet totes les lletres
    else {
        // calculem una direccio aleatoria.
        bool trobada = false;

        srand(time(NULL));      //random direccio
        int dir = rand() % 8;
        int newdir = dir;       //dir original per saber si ja hem provat totes
        int i2, j2;

        do {

            i2 = i + DIR[newdir].first;
            j2 = j + DIR[newdir].second;

            if (posok(n, i2, j2) and (sopa[i2][j2] == '#' or not visitat[i2][j2] or sopa[i2][j2] == p[l])) { 
                trobada = true;
                visitat[i2][j2] = true;
            }
            else {  // provem una nova direccio
                ++newdir;   
                if(newdir == 8) newdir = 0;
            }
            
        }  
        while (not trobada and newdir != dir);
        if (trobada) {
            if (sopa[i2][j2] == '#') {
                sopa[i2][j2] = p[l];
                ++l;
                visitat[i2][j2] = true;
                colocarParaulaRec(p, l, i2, j2, sopa);
            }
            else if (sopa[i2][j2] == p[l]) {
                ++l;
                visitat[i2][j2] = true;
                colocarParaulaRec(p, l, i2, j2, sopa);
            }
            else {
                //cout << "error de trobada " << p << endl;
                return false;
            }
        }   
        else {
            //cout << "error de dir " << p << endl;
            return false;
            }
    }
}

void superSopa::omplebuits(Sopa& sopa) {
    int n = sopa.size();
    auto rng = std::default_random_engine {};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (sopa[i][j] == '#') {
                std::shuffle(std::begin(letters), std::end(letters), rng);
                sopa[i][j] = letters[(randomInferiorA(27))];
            }
        }
    }
}

bool superSopa::posok(int n, int i, int j) {
    return (i < n and i >= 0 and j < n and j >= 0 /*and visitat[i][j] == false*/);
}

int superSopa::randomInferiorA(int x) {
    srand(time(NULL));
    int r = abs(rand()) % x;
    return r;
}

/*void superSopa::resoldre (map<string, int>& res, HashTableDictionary& d, HashTableDictionary& pre, Sopa& so) {
    n = sopa.size();
    sopa = so;
    d_hash = d;
    pre_hash = pre;
    resultat.clear();
    vector<vector<bool>> v = vector<vector<bool>>(n, vector<bool>(n, false));
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            //cout << i << ' ' << j << endl;
            string primer(1, sopa[i][j]);
            bool existeix = false;

            //existeix = pre.comprovar(primer);
            //existeixParaula(primer, arrel, 0, existeix);
            //cout << existeix << endl;

            //if (existeix) {
                //calculaDireccions(d, pre, sopa, v, primer, i,j);
            //}
            calculaDireccions(v, primer, i, j);
            //cout << "fi" << endl;
        }
    }

    res = resultat;
}*/

bool posok2(int i, int j, int n, const vector<vector<bool>>& v) {
    return (i >= 0 and i < n and j >= 0 and j < n and not v[i][j]);
}
/*
void superSopa::calculaDireccions(matbool& v, const string& par, int i, int j) {

    v[i][j] = true;
    //string par(1, so[i][j]);

    for (int k = 0; k < DIR.size(); ++k) {

        int di = i + DIR[k].first;
        int dj = j + DIR[k].second;

        if (posok2(di, dj, sopa.size(), v)) {
            //cout << "v " << di << ' ' << dj << endl;
            string seg(1, sopa[di][dj]);
            string suma = par + seg;
            //cout << '1';
            if (d_hash.comprovar(suma)) {
                itResultat = resultat.find(suma);
                if (itResultat != resultat.end()) {
                    itResultat->second++;
                } else {
                    resultat.insert({suma, 1});
                }
                //cout << "Trobat: " << suma << endl;
            }
            //cout << '2';
            bool existeix = false;
            //existeixParaula(suma, arrel, 0, existeix);
            existeix = pre_hash.comprovar(suma);
            //cout << '3';
            if (existeix) {
                calculaDireccions(v, suma, di, dj);
            }
            //cout << '4';
        }
    }
    v[i][j] = false;
}*/

void superSopa::resoldre (map<string, int>& res, HashTableDictionary& d, HashTableDictionary& pre, Sopa& so) {
    n = sopa.size();
    sopa = so;
    d_hash = d;
    pre_hash = pre;
    vector<vector<bool>> visitats;
    resultat.clear();    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string p = "";
            p.push_back(sopa[i][j]);
            visitats = vector<vector<bool>>(n, vector<bool>(n, false));
            visitats[i][j] = true;
            //cout << i << ' ' << j << endl;
            resoldreRecursiuHash(visitats, p, i, j);            
        }
    }
    
    res = resultat;
}
bool superSopa::comprovarPosicio (int i, int j, matbool& v) {
    return i >= 0 and i < sopa.size() and j >= 0 and j < sopa.size() and not v[i][j];
}

void superSopa::resoldreRecursiuHash (matbool& v, string paraula, int i, int j) {
    //cout << paraula << endl;    
    
    for (auto dir : DIR) {
        int i2 = i + dir.first;
        int j2 = j + dir.second;

        if (comprovarPosicio(i2, j2, v)) {           
            string paraula2 = paraula;
            paraula2.push_back(sopa[i2][j2]);

            if (d_hash.comprovar(paraula2)) {
                itResultat = resultat.find(paraula2);
                if (itResultat != resultat.end()) {
                    itResultat->second++;
                } else {
                    resultat.insert({paraula2, 1});
                }
            }
            if (pre_hash.comprovar(paraula2)) {
                v[i2][j2] = true;
                resoldreRecursiuHash(v, paraula2, i2, j2);            
                v[i2][j2] = false;
            }
        }
    }
} 

map<string,int> superSopa::resoldre (SortedVector& d, Sopa& sopa) {
    d.netejaTrobades();
    int l = 0 , r = d.getSize() - 1;
    int n = sopa.size();
    vector<vector<bool>> pos(n, vector<bool>(n,false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int l = 0, r = d.getSize()-1, iterador = 0;
            d.buscarParaula(i,j,pos,l,r,iterador,sopa);            
        }
    }
    return d.getTrobades();
    
}

void superSopa::resoldre (map<string, int>& res, BloomFilterDictionary& d, BloomFilterDictionary& pre, Sopa& so) {
    n = sopa.size();
    sopa = so;
    d_filtre = d;
    pre_filtre = pre;
    vector<vector<bool>> visitats;
    resultat.clear();    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string p = "";
            p.push_back(sopa[i][j]);
            visitats = vector<vector<bool>>(n, vector<bool>(n, false));
            visitats[i][j] = true;
            //cout << i << ' ' << j << endl;
            resoldreRecursiuFiltre(visitats, p, i, j);            
        }
    }
    
    res = resultat;
}

void superSopa::resoldreRecursiuFiltre (matbool& v, string paraula, int i, int j) {
    for (auto dir : DIR) {
        int i2 = i + dir.first;
        int j2 = j + dir.second;

        if (comprovarPosicio(i2, j2, v)) {           
            string paraula2 = paraula;
            paraula2.push_back(sopa[i2][j2]);

            if (d_filtre.comprovar(paraula2)) {
                itResultat = resultat.find(paraula2);
                if (itResultat != resultat.end()) {
                    itResultat->second++;
                } else {
                    resultat.insert({paraula2, 1});
                }
            }
            if (pre_filtre.comprovar(paraula2)) {
                v[i2][j2] = true;
                resoldreRecursiuFiltre(v, paraula2, i2, j2);            
                v[i2][j2] = false;
            }
        }
    }
}

void superSopa::calculaDireccions(TrieDictionary& d, const Sopa& so, matbool& v, const string& par, int i, int j) {


    v[i][j] = true;
    //string par(1, so[i][j]);

    for (int k = 0; k < DIR.size(); ++k) {

        int di = i + DIR[k].first;
        int dj = j + DIR[k].second;

        if (posok2(di, dj, so.size(), v)) {
            
            string seg(1, so[di][dj]);
            string suma = par + seg;
            
            if (d.comprovar(suma)) {
                calculaDireccions(d, so, v, suma, di, dj);
            }
        }
    }
    v[i][j] = false;
}

void superSopa::resoldre (TrieDictionary& d, Sopa& sopa) {
    
    int n = sopa.size();
    matbool vis(n, vector<bool>(n, false));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {

            string primer(1, sopa[i][j]);
            if (d.comprovar(primer)) calculaDireccions(d, sopa, vis, primer, i, j);
        }
    }
}
