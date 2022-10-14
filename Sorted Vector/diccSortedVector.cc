#include "diccSortedVector.hh"


SortedVector::SortedVector () {
    v = vector< string>(0);
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
    fp_in.open("./diccionaris/mare-balena-vocabulary-3.txt");
    while (fp_in >> a) 
        v.push_back(a);
    
    fp_in.close();
    mergesort(0,getSize()-1);
    
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



const int SortedVector::getSize() {
    return v.size();
}





