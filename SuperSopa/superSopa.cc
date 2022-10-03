#include "superSopa.hh"

const vector<pair<int,int>> DIR = {make_pair( 1, 0), make_pair( 1, 1),
                                   make_pair( 0, 1), make_pair(-1, 1),
                                   make_pair(-1, 0), make_pair(-1,-1),
                                   make_pair( 0,-1), make_pair( 1,-1)};

const vector<int> SENTIT = {-1,1};

vector<char> letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };




superSopa::superSopa(){};

// crea una super sopa on l'atribut sopa té mida nxn
superSopa::superSopa(const int& mida) {
    n = mida;
    vector< vector< char> > ns (n,vector<char>(n, ' '));
    so = ns;
}
void superSopa::llegirDiccionari (vector<string>& v) {
    int m = v.size();
    for (int i = 0; i < m; ++i) {

    }
}

void superSopa::imprimirSopa () {
    cout << "----------------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << '-' << so[i][0];
        for (int j = 1; j < n; ++j) cout << ' ' << so[i][j];
        cout << '-' << endl;
    }
    cout << "----------------------" << endl;
}

// he fet aquesta funcio per comprovar que totes les paraules siguin a la sopa
void superSopa::imprimirParaulaenSopa (const vector< vector< bool>>& pos) {
    cout << "----------------------" << endl;
    for (int i = 0; i < n; ++i) {
        cout << '-' << pos[i][0];
        for (int j = 1; j < n; ++j) cout << ' ' << pos[i][j];
        cout << '-' << endl;
    }
    cout << "----------------------" << endl;
}

void superSopa::costruirSopa(const vector<string>& dicc) {
    int i0, j0, iterador = 0; bool fet = false;
    // pos es un vector que indica a quines posicions hi ha NOMES la paraula amb que es treballa, per tal que no es creui amb ella mateixa.
    vector<vector<bool>> pos(n, vector<bool>(n,false));
    while (iterador != dicc.size()) {
        
        i0 = randomInferiorA(n); j0 = randomInferiorA(n);
        while (not caracterSituable(i0,j0,dicc[iterador][0])) {
            i0 = randomInferiorA(n); j0 = randomInferiorA(n);
        }     
        

        pos[i0][j0] = true;
        afegirLletra(i0,j0,dicc[iterador][0]);
        if (afegirParaula (dicc[iterador],i0,j0,pos,1)) {
            ++iterador;
           
        }
        else {
            afegirLletra(i0,j0,' ');
            pos[i0][j0] = false;
        }
        
        vector< vector < bool>> x(n, vector<bool>(n,false));
        pos = x;

    }
    //omplebuits();
}

void superSopa::omplebuits() {
    
    auto rng = std::default_random_engine {};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (so[i][j] == ' ') {
                std::shuffle(std::begin(letters), std::end(letters), rng);
                for (int k =0; k < n; ++k) cout << letters[k] << ' ';
                cout << endl;
                so[i][j] = 'a' + letters[(randomInferiorA(27))];
            }
        }
    }
}

void superSopa::resoldreVector () {}

void superSopa::resoldreTrie () {}

void superSopa::resoldreBloom () {}

void superSopa::resoldreDHash () {}






bool superSopa::afegirParaula (string s, int i0, int j0, vector<vector<bool>> pos, int k) {   
    // Escull una posició random i hi posa la paraula.
    if (k == s.size()) {
        cout << s << endl;
        imprimirParaulaenSopa(pos);
        return true;
    }
    bool posable = false;
    int ni, nj, direccions_provades = 0, index = randomInferiorA(8), sentit = SENTIT[randomInferiorA(2)];
    pair<int,int> ndir = DIR[index];
    
    while (not posable and direccions_provades < 8 ) {
        ni = ndir.first + i0; nj = ndir.second + j0;
        
        posable = (caracterSituable(ni,nj,s[k]) and not pos[ni][nj]);
        if (posable) {
            pos[ni][nj] = true;   
            afegirLletra (ni,nj,s[k]);         
            return (afegirParaula (s,ni,nj,pos,k+1));
            afegirLletra (ni,nj,' ');
            pos[ni][nj] = false;
        }
        ++direccions_provades;
        index = abs((index + sentit) % 8);
        ndir = DIR[index];
        
    }
    
    if (not posable) {
        //cout << "no he pogut posar la " << s[k] << " de " << s << endl;
        if ((caracterSituable(ni,nj,s[k]))) {
            afegirLletra (ni,nj,' ');
            pos[ni][nj] = false;
        }
    }


    
}

// Retorna true si ha pogut posar la lletra a la posició (i,j).
void superSopa::afegirLletra (const int& i,const int& j, const char& c) {   
    // Escull una posició so[i][j] i hi posa la lletra.
    so[i][j] = c;
    system("CLS");
    imprimirSopa();
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