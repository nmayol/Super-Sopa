#include "superSopa.hh"

const vector<pair<int,int>> DIR = {{-1, -1}, {-1, 0}, {-1, 1},
                                   {0, -1}, {0, 1},
                                   {1, -1}, {1, 0}, {1, 1}};

const vector<int> SENTIT = {-1,1};

vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

//MÈTODES FINALS (la resta no sé com funcionen i segur que es poden aprofitar
//i barrejar bé, però els definitius haurien de ser aquests)

//constructor buit
superSopa::superSopa(){
    resultat = map<string, int>();
};

void superSopa::generarSopa (const vector<string>& dicc, Sopa& sopa) {
    n = sopa.size();

    int paraules = dicc.size();     // paraules dintre diccionari
    int parSopa = 0;                // paraules dintre la SOPA

    srand(time(NULL));
    int index = abs(rand()) % paraules;
    int indexo = index;

    do {

        string p = dicc[index];

        // calculem la posicio on comencem.
        bool start = false;
        bool end = false;

        srand(time(NULL));
        int i = rand() % n;
        int j = rand() % n;
        int io = i, jo = j;                                                                                                                                                   

        while (not start and not end) {
            
            if (sopa[i][j] == '#' or sopa[i][j] == p[0]) {
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
                cout << p << " : " << i << ' ' << j << endl;
            }
        }
        ++index;
        if (index == paraules) index = 0;
    }
    while (parSopa < 30 and indexo != index);
    
    cout << "Total paraules: " << parSopa << endl;

    // acabem de fer la sopa.
    omplebuits(sopa);
}

bool superSopa::colocarParaulaRec(const string& p, int l, int i, int j, Sopa& sopa) {

    if (l == p.size()) return true;
    else {
        // calculem una direccio aleatoria.
        bool trobada = false;

        srand(time(NULL));
        int dir = rand() % 8;
        int newdir = dir;

        do {

            i += DIR[newdir].first;
            j += DIR[newdir].second;

            if (posok(i,j)) trobada = true;
            else {
                i -= DIR[newdir].first;
                j -= DIR[newdir].second;
                ++newdir;
                if (newdir == 8) newdir = 0;
            }
        } 
        while (not trobada and dir != newdir);
        //cout << "POSICIO TROBADA: " << i << ' ' << j << ' ' << l << endl;

        if (trobada) {
            if (sopa[i][j] == '#') {
                sopa[i][j] = p[l];
                ++l;
                visitat[i][j] = true;
                colocarParaulaRec(p, l, i, j, sopa);
            }
            else if (sopa[i][j] == p[l] and not visitat[i][j]) {
                ++l;
                visitat[i][j] = true;
                colocarParaulaRec(p, l, i, j, sopa);
            }
            else return false;
        }   
        else return false;
    }
}

void superSopa::omplebuits(Sopa& sopa) {
    
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

bool superSopa::posok(int i, int j) {
    return (i < n and i >= 0 and j < n and j >= 0 and visitat[i][j] == false);
}

int superSopa::randomInferiorA(int x) {
    srand(time(NULL));
    int r = abs(rand()) % x;
    return r;
}




map<string, int> superSopa::resoldre (HashTableDictionary& d, HashTableDictionary& pre, Sopa& sopa, int m) {
    maxim = m;
    //maxim = 5;
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

//des de resoldre, cridar-lo des de 0, 0
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


/*

map<string, int> bfs(Sopa& soap, int f, int c) {
    string paraula = 0;
    map<string, int> sol;
    pair<string,pair<int,int>> pos_par;
    queue<pos_par> q;
    q.push({soap[f,c], {f, c}});

    while(not q.empty()) {
        string p = q.front().first;
        act = q.front().second;
        q.pop();
        bool paraula_existeix = false;

        for (int i = 0; i < 8; ++i){
            int x = act.first + DIR.firts[i];
            int y = act.second + DIR.second[i];
            if(paraula_existeix) {
                paraula = sopa[x,y];
                paraula_existeix = false;
            }
			if (x >= 0 and x < n and y >= 0 and y < n) {
                if(paraula.length() > 2) {
                    paraula =+ sopa[act.first][act.second]
                    paraula_existeix = h.comprovar(paraula);
                    if(paraula_existeix) {
                        bool ja_tinc_p = false;
                        for (itr = sol.begin(); itr != sol.end(); ++itr) {
                            if(itr.first == paraula) itr.second++;
                            ja_tinc_p =true;
                        }
                        if(!ja_tinc_p) sol.end().insert(paraula, 0); 
                    }
                    q.push({sopa[x,y], {x,y}});
                }
            }
        }
    }
    return sol;
}


*/

void superSopa::resoldre (SortedVector& d, Sopa& sopa) {
    int l = 0 , r = d.getSize() - 1;
    vector<vector<bool>> pos(n, vector<bool>(n,false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int l = 0, r = d.getSize()-1, iterador = 0;
            d.buscarParaula(i,j,pos,l,r,iterador,sopa);            
        }
    }    
}



map<string, int> superSopa::resoldre (BloomFilterDictionary& d, Sopa& sopa) {

}

void superSopa::resoldre (TrieDictionary& d, Sopa& sopa) {

}



//RESTA DE MÈTODES
// crea una super sopa on l'atribut sopa té mida nxn
/*superSopa::superSopa(const int& mida) {
    n = mida;
    so = Sopa(n,vector<char>(n, '#'));
}*/

/*
void superSopa::llegir() {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) cin >> so[i][j];
    }
}*/

/* p -> paraula a colocar dins la sopa, l -> lletres colocades.
   El resultat es cert si hem pogut colocar correctament la paraula, fals altrament.
*/

/*
void superSopa::construirParaules(const vector<string>& dicc) {

    int paraules = dicc.size();     // paraules dintre diccionari
    int parSopa = 0;                // paraules dintre la SOPA

    srand(time(NULL));
    int index = abs(rand()) % paraules;
    int indexo = index;

    do {

        string p = dicc[index];

        // calculem la posicio on comencem.
        bool start = false;
        bool end = false;

        srand(time(NULL));
        int i = rand() % n;
        int j = rand() % n;
        int io = i, jo = j;

        while (not start and not end) {
            
            if (so[i][j] == '#' or so[i][j] == p[0]) {
                so[i][j] = p[0];
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
            if (colocarParaulaRec(p, 1, i, j)) {
                ++parSopa;
                cout << p << " : " << i << ' ' << j << endl;
            }
        }
        ++index;
        if (index == paraules) index = 0;
    }
    while (parSopa < 30 and indexo != index);
    
    cout << "Total paraules: " << parSopa << endl;

    // acabem de fer la sopa.
    omplebuits();
}*/

//void superSopa::resoldreTrie () {}

/*int superSopa::mida() const {
    return n;
}*/

//void superSopa::resoldreBloom () {}

//void superSopa::resoldreDHash () {}

/*
char superSopa::getchar(int i, int j) const {
    return so[i][j];
}*/

/*
void superSopa::afegirParaula (string s, int i0, int j0, vector<vector<bool>>& pos, int k, bool& afegida) {   
    // Escull una posició random i hi posa la paraula.
    
    if (k >= s.size()) return;
    bool posable = false;
    int ni, nj, direccions_provades = 0, index = randomInferiorA(8), sentit = SENTIT[randomInferiorA(2)];
    pair<int,int> ndir = DIR[index];
    
    while (not posable and direccions_provades < 8) {
        ni = ndir.first + i0; nj = ndir.second + j0;
        index = abs((index + sentit) % 8);
        ndir = DIR[index];
        posable = (caracterSituable(ni,nj,s[k]) and not pos[ni][nj]);
        if (posable) {
            
            pos[ni][nj] = true;   
            if (k == s.size() - 1) {
                afegida = true;
                imprimirParaulaenSopa (pos);
                afegirLletra(ni,nj,s[k]);
                
            }
            else {
                afegirParaula (s,ni,nj,pos,k+1,afegida);
                if (afegida) afegirLletra (ni,nj,s[k]);
                
            }
            pos[ni][nj] = false;
            
        }
        ++direccions_provades;  
    }   
}*/

/*
///////////////////////// FUNCIO BACKTRACKING PEL SORTED VECTOR ////////////////////////////////
void superSopa::resoldre (SortedVector d, Sopa& sopa) {
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


////////////////////////////////////////////////////////////////////////////////////////////////

/*
// Retorna true si ha pogut posar la lletra a la posició (i,j).
void superSopa::afegirLletra (const int& i,const int& j, const char& c) {   
    // Escull una posició so[i][j] i hi posa la lletra.
    so[i][j] = c;

}

// Retorna true si la posició (i,j) és una posició de la Sopa.
bool superSopa::compleixLimits(const int& i,const int& j) {
    return(i >= 0 and j >= 0 and i < n and j < n);
}

// retorna cert si la lletra es vol posar a un lloc dins els limits de la sopa que sigui buit o que tingui la mateixa lletra
bool superSopa::caracterSituable(const int& i,const int& j, const char& c) {
    return (compleixLimits(i,j) and (so[i][j] == ' ' or so[i][j] == c));
}
*/
/*
void superSopa::imprimirSopa () {
    ofstream fp_out;
    fp_out.open("./Sorted Vector/sopa.txt");
    fp_out << "----------------------" << endl;
    for (int i = 0; i < n; ++i) {
        fp_out << so[i][0];
        for (int j = 1; j < n; ++j) fp_out << ' ' << so[i][j];
        fp_out << endl;
    }
    fp_out << "----------------------" << endl;
    fp_out.close();
}

void superSopa::imprimirSopaTerminal () {

    cout << "----------------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << so[i][0];
        for (int j = 1; j < n; ++j) cout << ' ' << so[i][j];
        cout << endl;
    }
    cout << "----------------------" << endl;
}

// he fet aquesta funcio per comprovar que totes les paraules siguin a la sopa
void superSopa::imprimirParaulaenSopa (const vector< vector< bool>>& pos) {
    ofstream fp_out;
    fp_out.open("./Sorted Vector/solucio.txt",ofstream::app);
    fp_out << "----------------------" << endl;
    for (int i = 0; i < n; ++i) {;
        fp_out << '-' << pos[i][0];
        for (int j = 1; j < n; ++j) {
            fp_out << ' ' << pos[i][j];
        }
        fp_out << '-' << endl;
    }
    fp_out << "----------------------" << endl;
    fp_out.close();
}*/