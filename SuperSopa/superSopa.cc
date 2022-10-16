#include "superSopa.hh"

const vector<pair<int,int>> DIR = {{-1, -1}, {-1, 0}, {-1, 1},
                                   {0, -1}, {0, 1},
                                   {1, -1}, {1, 0}, {1, 1}};

const vector<int> SENTIT = {-1,1};

vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

//constructor buit
superSopa::superSopa(){
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

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            string p = "";
            p.push_back(sopa[i][j]);
            visitats = vector<vector<bool>>(n, vector<bool>(n, false));
            visitats[i][j] = true;
            //cout << i << ' ' << j << endl;
            resoldreRecursiu(sopa, pre, d, p, visitats, i, j);
        }
    }
    
    return resultat;
}

bool superSopa::comprovarPosicio (Sopa& sopa, vector<vector<bool>>& v, int i, int j) {
    return i >= 0 and i < sopa.size() and j >= 0 and j < sopa.size() and not v[i][j];
}

void superSopa::resoldreRecursiu (Sopa& sopa, HashTableDictionary& pre, HashTableDictionary& d, string paraula, vector<vector<bool>>& visitats, int i, int j) {
    //paraula correcta?
    //cout << paraula << endl;
    //if (paraula.length() > maxim) return;

    
    
    if (d.comprovar(paraula)) {
        //cout << "Trobat: " << paraula << endl;
        itResultat = resultat.find(paraula);
        if (itResultat != resultat.end()) {
            itResultat->second++;
        } else {
            resultat.insert({paraula, 1});
        }
        return;
    }

    if (paraula.size() > 2 and not pre.comprovar(paraula)) return;

    /*cout << "direccions" << endl;
    for (auto dir : DIR) {
        cout << dir.first << ' ' << dir.second << endl;
    }*/

    for (auto dir : DIR) {
        int i2 = i + dir.first;
        int j2 = j + dir.second;

        //cout << 'o' << endl;
        //cout << dir.first << ' ' << dir.second << endl;
        //cout << i << ' ' << i2 << endl << j << ' ' << j2 << endl;

        if (comprovarPosicio(sopa, visitats, i2, j2)) {
            visitats[i2][j2] = true;
            //string paraula2 = (paraula += sopa[i2][j2]);
            string paraula2 = paraula;
            paraula2.push_back(sopa[i2][j2]);
            resoldreRecursiu(sopa, pre, d, paraula2, visitats, i2, j2);            
            visitats[i2][j2] = false;
        }
    }
}

map<string, int> superSopa::resoldre (SortedVector& d, Sopa& sopa) {
       
}

map<string, int> superSopa::resoldre (BloomFilterDictionary& d, Sopa& sopa) {

}

map<string, int> superSopa::resoldre (TrieDictionary& d, Sopa& sopa) {

}

/*
///////////////////////// FUNCIO BACKTRACKING PEL SORTED VECTOR ////////////////////////////////
void superSopa::resoldre (SortedVector d, Sopa& sopa) {
    int n = sopa.size();
    int l = 0 , r = d.getSize() - 1;
    vector<vector<bool>> pos(n, vector<bool>(n,false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int l = 0, r = d.getSize()-1, iterador = 0;
            buscarParaula(i,j,pos,l,r,d,iterador);            
        }
    }
    d.imprimirTrobades();
}
// (i,j) es una posicio valida a la sopa
void superSopa:: buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, SortedVector & sv, int iterador) {
    int direccions_provades = 0, ni, nj, nl, nr;
    pos[i][j] = true;
    
    while (direccions_provades < 8) {
        ni = DIR[direccions_provades].first + i; nj = DIR[direccions_provades].second + j; 
        if (compleixLimits(ni,nj) and not pos[ni][nj]) {
            nl = sv.first_ocurrence(l,r,so[i][j],iterador);
            nr = sv.last_ocurrence(max(l,nl),r,so[i][j],iterador);
            if ((nl != -1 and nr != -1)){                
                ++iterador;
                buscarParaula(ni,nj,pos,nl,nr,sv,iterador);
                --iterador;
            }    
        }
        ++direccions_provades;
    }
    pos[i][j] = false;
}*/
