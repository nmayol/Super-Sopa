#include "superSopa.hh"

const vector<pair<int,int>> DIR = {make_pair( 1, 0), make_pair( 1, 1),
                                   make_pair( 0, 1), make_pair(-1, 1),
                                   make_pair(-1, 0), make_pair(-1,-1),
                                   make_pair( 0,-1), make_pair( 1,-1)};

const vector<int> SENTIT = {-1,1};

vector<char> letters = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                         'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                         'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };




superSopa::superSopa(){};



// crea una super sopa on l'atribut sopa té mida nxn
superSopa::superSopa(const int& mida) {
    n = mida;
    so = Sopa(n,vector<char>(n, '#'));
}

void superSopa::imprimirSopa () {
    ofstream fp_out;
    fp_out.open("./Sorted Vector/sopa.txt");
    fp_out << "----------------------" << endl;
    for (int i = 0; i < n; ++i) {
        fp_out << '-' << so[i][0];
        for (int j = 1; j < n; ++j) fp_out << ' ' << so[i][j];
        fp_out << '-' << endl;
    }
    fp_out << "----------------------" << endl;
    fp_out.close();
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
}
/*
void superSopa::costruirSopa(const vector<string>& dicc) {
    int i0, j0, iterador = 0; 
    bool fet = false;

    // pos es un vector que indica a quines posicions hi ha NOMES la paraula amb que es treballa, per tal que no es creui amb ella mateixa.
    vector<vector<bool>> pos(n, vector<bool>(n,false));

    while (iterador != dicc.size()) {
        //cout << dicc[iterador] << ": " << endl; 

        i0 = randomInferiorA(n); j0 = randomInferiorA(n);
        while (not caracterSituable(i0,j0,dicc[iterador][0])) {
            i0 = randomInferiorA(n); j0 = randomInferiorA(n);
        }     
                
        bool afegida = false;
        afegirParaula (dicc[iterador],i0,j0,pos,0, afegida);
        if (afegida) ++iterador;
        else pos[i0][j0] = false;

        vector< vector < bool>> x(n, vector<bool>(n,false));
        pos = x;
        //system("CLS");
        //imprimirSopa();
    }
    omplebuits();

}
*/

bool superSopa::posok(int i, int j) {

    return (i < n and i >= 0 and j < n and j >= 0 and visitat[i][j] == false);
}

/* p -> paraula a colocar dins la sopa, l -> lletres colocades.
   El resultat es cert si hem pogut colocar correctament la paraula, fals altrament.
   FALTA QUE NO ES SOBREPOSI :)
*/
bool superSopa::colocarParaulaRec(const string& p, int l, int i, int j) {

    if (l == p.size()) return true;
    else {
        
        // calculem una direccio aleatoria.
        bool trobada = false;

        while (not trobada) {
            srand(time(NULL));
            int dir = rand() % 8;

            i += DIR[dir].first;
            j += DIR[dir].second;

            if (posok(i,j)) trobada = true;
            else {
                i -= DIR[dir].first;
                j -= DIR[dir].second;
            }
            //cout << trobada << " ja que " << i << ' ' << j << endl;
        }
        //cout << "POSICIO TROBADA: " << i << ' ' << j << ' ' << l << endl;

        if (so[i][j] == '#') {
            so[i][j] = p[l];
            ++l;
            visitat[i][j] = true;
            colocarParaulaRec(p, l, i, j);
        }
        else if (so[i][j] == p[l]) {
            ++l;
            visitat[i][j] = true;
            colocarParaulaRec(p, l, i, j);
        }
        else return false;   
    }
    //return true;
}

void superSopa::construirParaules(const vector<string>& dicc) {

    int paraules = dicc.size();     // paraules dintre diccionari
    int parSopa = 0;                // paraules dintre la SOPA

    srand(time(NULL));
    int index = abs(rand()) % paraules;

    // agafem una paraula al atzar.
    while (parSopa < 4) {

        string p = dicc[index];

        // calculem la posicio on comencem.
        bool start = false;
        int i = 0, j = 0;

        while (not start) {
            srand(time(NULL));
            i = rand() % n;
            j = rand() % n;

            if (so[i][j] == '#' or so[i][j] == p[0]) {
                so[i][j] = p[0];
                start = true;
            }
        }
        visitat = vector<vector<bool>> (n, vector<bool>(n, false));
        if (colocarParaulaRec(p, 1, i, j)) {
            ++parSopa;
            ++index;
            if (index == paraules) index = 0;
            cout << "Posicions inicials de " << p << " : " << i << ' ' << j << endl;
        }
    }
    
    cout << "Total paraules: " << parSopa << endl;

    // acabem de fer la sopa.
    omplebuits();
}

void superSopa::omplebuits() {
    
    auto rng = std::default_random_engine {};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (so[i][j] == '#') {
                std::shuffle(std::begin(letters), std::end(letters), rng);
                so[i][j] = letters[(randomInferiorA(27))];
            }
        }
    }
}
///////////////////////// FUNCIONS SORTED VECTOR ////////////////////////////////
// TODO: no és la definitiva
void superSopa::resoldreVector () {
    SortedVector sv = SortedVector();
    int l = 0 , r = sv.getSize() - 1;
    vector<vector<bool>> pos(n, vector<bool>(n,false));
    sv.setIterador(0);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int l = 0, r = sv.getSize();
           
            buscarParaula(i,j,pos,l,r,sv);

            imprimirSopa();
            sv.imprimirTrobades();
        }
    }
}

// (i,j) es una posicio valida a la sopa
void superSopa:: buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, SortedVector& sv) {
    int direccions_provades = 0, ni, nj, nl, nr;
    pos[i][j] = true;
    
    while (direccions_provades < 8) {
        ni = DIR[direccions_provades].first + i; nj = DIR[direccions_provades].second + j; 
        if (compleixLimits(ni,nj) and not pos[ni][nj]) {
            nl = sv.first_ocurrence(l,r,so[i][j]);
            nr = sv.last_ocurrence(l,r,so[i][j]);
            if (l < r and (nl != -1 and nr != -1)){
                sv.setIterador(sv.getIterador()+1);
                buscarParaula(ni,nj,pos,nl,nr,sv);
                sv.setIterador(sv.getIterador()-1);

            }    
        }
        ++direccions_provades;
    }
    pos[i][j] = false;

}







//////////////////////////////////////////////////////////////////////////////////

void superSopa::resoldreTrie () {}

void superSopa::resoldreBloom () {}

void superSopa::resoldreDHash () {}

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
     
    
    
}

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


int superSopa::randomInferiorA(int x) {
    srand(time(NULL));
    int r = abs(rand()) % x;
    return r;
}