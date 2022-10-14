#include "diccDHashing.hh"


void HashTableDictionary::HashTableDictionary(int mida) {
    {
        tableSize = mida

        hashTable = new int[tableSize];
        curr_size = 0;
        maxcolision = 0;
        for (int i=0; i<tableSize; i++)
            hashTable[i] = "nnnn";
    } 
}
-

bool HashTableDictionary::plena() {
        return (cur_size == tableSize);
    }


int HashTableDictionary::hash1(string key) {
    int length = key.length();
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += (int)key[i];
    }

        return (sum % tableSize);
    }


int HashTableDictionary::hash2(string key) {
    int length = key.length();
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += (int)key[i];
    }
        return (7 - (sum % 7));
}
 

void HashTableDictionary::afegir(string key)
    {
        // si la taula esta plena
        if (plena())
            return;
 
        int index = hash1(key);
 
        // si hi ha colisio
        if (hashTable[index] != "nnnn") {
            // index2 del segon hash
            int index2 = hash2(key);
            int i = 1;
            bool found = false;
            while (!found) {
                // doble hash
                int newIndex = (index + i * index2) % tableSize;
                
                if (hashTable[newIndex] == -1) {
                    hashTable[newIndex] = key;
                    if(i > maxcolision) maxcolision = i;
                    found = true;
                }
                i++;
            }
        }
        else hashTable[index] = key;
        curr_size++;
    }


bool HashTableDictionary::comprovar(string s) {
    int index = hash1(s);
    if (hashTable[index] != s) {
        int index2 = hash2(key);
        int i = 1;
        while (i <= maxcolision) {
            int newIndex = (index + i * index2) % tableSize;
            if (hashTable[newIndex] == s) return true;
            i++;
        }
        return false;
    }
    return true;  
}


void HashTableDictionary::imprimir() {
    ofstream fp_out;
    fp_out.open("./DHashing/out.txt");
    for(int i = 0; i < tableSize; i++) fp_out << hashTable[i] << endl;
    fp_out.close();
}

