#include "diccSortedVector.hh"


SortedVector::SortedVector () {
    v = vector< string>(0);
    iterador = 0;
    trobades.clear();
    construirVector();
}




void SortedVector::construirVector() {
    ifstream fp_in;
    string a;
    fp_in.open("./mare-balena-vocabulary-3.txt");
    while (fp_in >> a) v.push_back(a);
    fp_in.close();
}

// TODO: la intencio es fer una c. dicotomica amb div divisions (? nose)
/*
 * Retorna uns valors de l i r tals que el prefix sigui igual al demanat
 * Pre : tots els caracters trobats anteriors frmen part d'un grup de paraules del diccionari entre v[l] i v[r]
*/
int SortedVector::first_ocurrence(int l, int r, const char& c) {
    // les lletres anteriors ja han complert la condició 
    if (l > r) return -1;
    if (v[l].size() == iterador) {
        trobades.insert(l);
        ofstream fp_out;
        fp_out.open("./Sorted Vector/out.txt", fstream::app);
        fp_out << v[l] << endl;
        fp_out.close();
        
        ++l;
    }

    int m = (l + r) / 2;

    if (v[m].size() > iterador) {
        if (v[m][iterador] == c) {
            if ((m != 0 and v[m-1].size() > iterador) or l != m) {
                if (c != v[m-1][iterador]) return m;
                else return first_ocurrence(l,m-1,c);
            }
            else return m;
        }
        else if (v[m][iterador] < c) return first_ocurrence(m+1,r,c);
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
            if ((m != v.size() - 1 and v[m+1].size() > iterador) or r != m) {
                if (c != v[m+1][iterador]) return m;
                else return last_ocurrence(m+1,r,c);
            }
            else return m;
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

/* CASOS
 * - paraula dins paraula 
 * - paraula mes llarga 
 * - paraula no existeix
 * -
*/

bool SortedVector::comprovar (string s) {
    
    return true;
     
}