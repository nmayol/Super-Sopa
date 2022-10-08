#include "diccSortedVector.hh"

SortedVector::SortedVector (const vector<string>& vs) {
    v = vs;
    std::sort(v.begin(), v.end(), []
    (const std::string& first, const std::string& second){
        return first.size() > second.size();
    });
}

/*
void SortedVector::OrdenarVector() {
    
}
*/

void SortedVector::afegir (string s) {
    
}

void SortedVector::resoldre() {
    
    
}

bool SortedVector::comprovar (string s) {
    return true;  
}