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
    //cout << "posem paraules:" << endl;
    int paraules = dicc.size();     // paraules dintre diccionari
    int parSopa = 0;                // paraules dintre la SOPA

    srand(time(NULL));

    for(int k = 0; k < dicc.size(); ++k) {
        string p = dicc[k];
        cout << p << endl;
        // calculem la posicio on comencem.
        bool start = false;
        bool end = false;

        srand(time(NULL));
        int i = rand() % n;
        int j = rand() % n;
        int io = i, jo = j;                                                                                                                                                   

        while (not start and not end) {            
            if (sopa[i][j] == '#' or sopa[i][j] == p[0]) {
                cout << "primer if " << p << endl;
                sopa[i][j] = p[0];
                start = true;
            }
            else {
                ++j;
                if (j == n) {j = 0; ++i;}
                if (i == n) {i = 0;}
                if (i == io and j == jo) end = true;
            }
        }
        if (start) {
            visitat = vector<vector<bool>> (n, vector<bool>(n, false));
            if (colocarParaulaRec(p, 1, i, j, sopa)) {
                ++parSopa;
                //cout << p << " : " << i << ' ' << j << endl;
            }
        }
        if (end) cout << "No s'ha pogut colocar la paraula: " << p << endl;
    }    
    
    cout << "Total paraules: " << parSopa << endl;

    // acabem de fer la sopa.
    omplebuits(sopa);
}

bool superSopa::colocarParaulaRec(const string& p, int l, int i, int j, Sopa& sopa) {
    int n = sopa.size();
    if (l == p.size()) return true;
    else {
        // calculem una direccio aleatoria.
        bool trobada = false;

        srand(time(NULL));
        int dir = rand() % 8;
        int newdir = dir;

        int i2, j2;

        do {
            i2 = i + DIR[newdir].first;
            j2 = j + DIR[newdir].second;

            if (posok(n, i2, j2)) trobada = true;
            else {
                ++newdir;
                if (newdir == 8) newdir = 0;
            }
        } 
        while (not trobada and dir != newdir);
        //cout << "POSICIO TROBADA: " << i << ' ' << j << ' ' << l << endl;

        if (trobada) {
            if (sopa[i2][j2] == '#') {
                sopa[i2][j2] = p[l];
                ++l;
                visitat[i2][j2] = true;
                colocarParaulaRec(p, l, i2, j2, sopa);
            }
            else if (sopa[i2][j2] == p[l] and not visitat[i2][j2]) {
                ++l;
                visitat[i2][j2] = true;
                colocarParaulaRec(p, l, i2, j2, sopa);
            }
            else return false;
        }   
        else return false;
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
    return (i < n and i >= 0 and j < n and j >= 0 and visitat[i][j] == false);
}

int superSopa::randomInferiorA(int x) {
    srand(time(NULL));
    int r = abs(rand()) % x;
    return r;
}

map<string, int> superSopa::resoldre (HashTableDictionary& d, HashTableDictionary& pre, Sopa& sopa) {
    int n = sopa.size();
    vector<vector<bool>> visitats;
    resultat.clear();

    d_hash = d;
    pre_hash = pre;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string p = "";
            p.push_back(sopa[i][j]);
            visitats = vector<vector<bool>>(n, vector<bool>(n, false));
            visitats[i][j] = true;
            //cout << i << ' ' << j << endl;
            resoldreRecursiuHash(sopa, p, i, j);            
        }
    }
    
    return resultat;
}

bool superSopa::comprovarPosicio (Sopa& sopa, int i, int j) {
    return i >= 0 and i < sopa.size() and j >= 0 and j < sopa.size() and not visitats[i][j];
}

void superSopa::resoldreRecursiuHash (Sopa& sopa, string paraula, int i, int j) {
    //cout << paraula << endl;
    
    if (d_hash.comprovar(paraula)) {
        //cout << "Trobat: " << paraula << endl;
        itResultat = resultat.find(paraula);
        if (itResultat != resultat.end()) {
            itResultat->second++;
        } else {
            resultat.insert({paraula, 1});
        }
    }

    if (not pre_hash.comprovar(paraula)) return;    

    for (auto dir : DIR) {
        int i2 = i + dir.first;
        int j2 = j + dir.second;        

        if (comprovarPosicio(sopa, i2, j2)) {
            visitats[i2][j2] = true;
            string paraula2 = paraula;
            paraula2.push_back(sopa[i2][j2]);
            resoldreRecursiuHash(sopa, paraula2, i2, j2);            
            visitats[i2][j2] = false;
        }
    }
}

/*map<string, int> superSopa::resoldre (SortedVector& d, Sopa& sopa) {
       
}*/

map<string,int> superSopa::resoldre (SortedVector& d, Sopa& sopa) {
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

map<string, int> superSopa::resoldre (BloomFilterDictionary& d, Sopa& sopa) {

}

map<string, int>  superSopa::resoldre (TrieDictionary& d, Sopa& sopa) {

}


