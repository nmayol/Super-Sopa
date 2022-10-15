#include "diccSortedVector.hh"

const vector<pair<int,int>> DIR = {make_pair( 1, 0), make_pair( 1, 1),
                                   make_pair( 0, 1), make_pair(-1, 1),
                                   make_pair(-1, 0), make_pair(-1,-1),
                                   make_pair( 0,-1), make_pair( 1,-1)};

SortedVector::SortedVector(){}

void SortedVector::afegir(vector<string>& dicc) {
    v = dicc;
    trobades.clear();
    ordenar();
}

/*
void SortedVector::afegir(const string& s) {
    v.push_back(s);
}
*/

void SortedVector::ordenar() {
    mergesort(0,getSize()-1);
}

void SortedVector::imprimirTrobades() {
    ofstream fp_out;
    fp_out.open("./Sorted Vector/out.txt");
    for (std::set<int>::iterator it = trobades.begin(); it != trobades.end(); ++it) fp_out << v[*it] << endl;
    fp_out.close();
}



void SortedVector::mergesort(int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        
        mergesort(l,m);
        mergesort(m+1,r);
        merge(l,r,m);
    }
}

void SortedVector::merge(int l, int r, int m) {
    int n1 = m - l + 1, n2 = r - m;
    vector< string> v1(n1), v2(n2);
    for (int i = 0; i < n1; i++)
        v1[i] = v[l + i];
    for (int j = 0; j < n2; j++)
        v2[j] = v[m + 1 + j];

    int i = 0, j = 0, k = l;



    while (i < n1 and j < n2) {
        if (v1[i] <= v2[j]) {
            v[k] = v1[i];
            ++i;
        } else {
            v[k] = v2[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        v[k] = v1[i];
        ++i; ++k;
    }

    while (j < n2) {
        v[k] = v2[j];
        ++j; ++k;
    }

}






int SortedVector::first_ocurrence(int l, int r, const char& c, const int& iterador) {
    // les lletres anteriors ja han complert la condició 
    if (l > r) return -1;
    int m = (l + r) / 2;
    
    if (v[m].size() > iterador) { 
        if  (v[m][iterador] == c) {
            if (l != m and (m != 0 and v[m-1].size() > iterador and v[m-1][iterador] == c)) 
                return first_ocurrence(l,m-1,c,iterador);
            else {
                if (v[m].size() == (iterador+1)) {
                    trobades.insert(m);
                    ++m;
                }
                return m;
            }
        }
        else if  (v[m][iterador] < c) return first_ocurrence(m+1,r,c,iterador);
        else return first_ocurrence(l,m-1,c,iterador);       
    }
    else return first_ocurrence(l,m-1,c,iterador);

}

int SortedVector::last_ocurrence(int l, int r, const char& c, const int& iterador) {
    // les lletres anteriors ja han complert la condició 
    if (l > r) return -1;
    int m = (l + r) / 2;
   
    if (v[m].size() > iterador) {
        if (v[m][iterador] == c) {
            if (r == m or (m == (v.size() - 1) ) or (c != v[m+1][iterador]) ) return m;
            else return last_ocurrence(m+1,r,c,iterador);
        }
        else if (v[m][iterador] < c) return last_ocurrence(m+1,r,c,iterador);
        else return last_ocurrence(l,m-1,c,iterador);
    }
    else return last_ocurrence(l,m-1,c,iterador);   

}





// (i,j) es una posicio valida a la sopa
void SortedVector:: buscarParaula(int i , int j, vector<vector<bool>>& pos, int l, int r, int iterador, Sopa& s) {
    int direccions_provades = 0, ni, nj, nl, nr;
    pos[i][j] = true;
    
    while (direccions_provades < 8) {
        ni = DIR[direccions_provades].first + i; nj = DIR[direccions_provades].second + j; 
        if (compleixLimits(s,ni,nj,s.size()) and not pos[ni][nj]) {
            nl = first_ocurrence(l,r,s[i][j],iterador);
            nr = last_ocurrence(max(l,nl),r,s[i][j],iterador);
            if ((nl != -1 and nr != -1)){                
                ++iterador;
                buscarParaula(ni,nj,pos,nl,nr,iterador,s);
                --iterador;

            }    
        }
        ++direccions_provades;
    }
    pos[i][j] = false;

}




const int SortedVector::getSize() {
    return v.size();
}

// Retorna true si la posició (i,j) és una posició de la Sopa.
bool SortedVector::compleixLimits(Sopa& s, const int& i,const int& j,const int& n) {
    return(i >= 0 and j >= 0 and i < n and j < n);
}




