#include "diccDHashing.hh"


void HashTableDictionary::HashTableDictionary() {
    tablesize = 
}

void HashTableDictionary::afegir (string s) {
    int hashValue = hashFunction(key);
    auto& cell = table[hashValue];//preque no vaig directament a la table?
    auto bItr = begin(cell);
    bool keyExist = false;
    for(;bItr != end(cell); bItr++) {
        if(bItr == key){
            keyExist = true;
            //q faig si ja existeix? 
            break;
        }
    }
    if(!keyExist) {
        cell.emplace_back(key);
    }

}

bool HashTableDictionary::comprovar (string s) {
    return true;  
}

bool HashTableDictionary::isEmpty() {
    int sum;
    for(int i; i = 0; i++) sum+= table[i].size();
    if(sum == 0) return true;
    return false;
    index = hash % tablesize
}

int HashTableDictionary::hashFunction(int key) {
    int hash = 0;
    int index;

    for(int i = 0; i < key.lengh(); i++){
        hash += int(key[i]); 
    }


}

void HashTableDictionary::imprimir() {
    ofstream fp_out;
    fp_out.open("./DHashing/out.txt");
    for(int i = 0; i < hashGroups; i++) {
        auto bItr = table[i].begin();
        for(;bItr != table[i].end(); bItr++) {
            fp_out << bItr << endl;
        }
    }
    fp_out.close();

}



