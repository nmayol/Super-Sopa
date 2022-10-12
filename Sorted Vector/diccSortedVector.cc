#include "diccSortedVector.hh"


SortedVector::SortedVector () {
    v = vector< string>(0);
    iterador = 0;
    trobades.clear();
    construirVector();
}

void SortedVector::imprimirTrobades() {
    ofstream fp_out;
    fp_out.open("./Sorted Vector/out.txt");
    for (std::set<int>::iterator it = trobades.begin(); it != trobades.end(); ++it) fp_out << v[*it] << endl;
    fp_out.close();
}


void SortedVector::construirVector() {
    ifstream fp_in;
    string a;
    fp_in.open("./mare-balena-vocabulary-3.txt");
    while (fp_in >> a) v.push_back(a);
    fp_in.close();
}

int SortedVector::first_ocurrence(int l, int r, const char& c) {
    // les lletres anteriors ja han complert la condició 
    if (l > r) return -1;
    int m = (l + r) / 2;
    
    if (v[m].size() > iterador) { 
        if  (v[m][iterador] == c) {
            if (l != m and (m != 0 and v[m-1].size() > iterador and v[m-1][iterador] == c)) 
                return first_ocurrence(l,m-1,c);
            else {
                if (v[m].size() == (iterador+1)) {
                    trobades.insert(m);
                    ++m;
                }
                return m;
            }
        }
        else if  (v[m][iterador] < c) return first_ocurrence(m+1,r,c);
        else return first_ocurrence(l,m-1,c);       
    }
    else return first_ocurrence(l,m-1,c);

}

int SortedVector::last_ocurrence(int l, int r, const char& c) {
    // les lletres anteriors ja han complert la condició 
    if (l > r) return -1;
    int m = (l + r) / 2;
    
    if (v[m].size() > iterador) {
        if (v[m][iterador] == c) {
            if (r == m or (m == (v.size() - 1) ) or (c != v[m+1][iterador]) ) return m;
            else return last_ocurrence(m+1,r,c);
        }
        else if (v[m][iterador] < c) return last_ocurrence(m+1,r,c);
        else return last_ocurrence(l,m-1,c);
    }
    else return last_ocurrence(l,m-1,c);   

}



const int SortedVector::getSize() {
    return v.size();
}


const int SortedVector::getIterador() {
    return iterador;
}

void SortedVector::setIterador(const int& i) {
    iterador = i;
}

