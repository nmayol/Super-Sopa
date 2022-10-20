#include "diccDHashing.hh"

HashTableDictionary::HashTableDictionary (int mida) {
    tableSize = seguentPrimer(mida*2);
    primerPetit = abansPrimer(mida*2);
    hashTable = new string[tableSize];
    maxcolision = 0;
    for (int i=0; i<tableSize; i++)
        hashTable[i] = "nnnn";
}

HashTableDictionary::HashTableDictionary () {
    tableSize = 100;
    primerPetit = 91;
    hashTable = new string[tableSize];
    maxcolision = 0;
    for (int i=0; i<tableSize; i++)
        hashTable[i] = "nnnn";
}

bool HashTableDictionary::esPrimer(int n) {
  bool is_prime = true;

  if (n < 2) return false;

  for (int i = 2; i*i <= n; ++i) {
    if (n % i == 0) {
      return false;
    }
  }

 return true;
}

int HashTableDictionary::seguentPrimer (int n) {
    for (int i = n;;++i) {
        if (esPrimer(i)) return i;
    }
}

int HashTableDictionary::abansPrimer (int n) {
    for (int i = n-1; i > 0; --i) {
        if (esPrimer(i)) return i;
    }
}

int HashTableDictionary::hash1 (string key) {
    int length = key.length();
    int sum = 0;
    for(int i = 1; i <= length; i++) {
        sum += (i*(int)key[i]);
    }
    return (sum % tableSize);
}

int HashTableDictionary::hash2 (string key) {
    int length = key.length();
    int sum = 0;
    for(int i = 0; i < length; i++) {
        sum += (int)key[i];
    }
    return (primerPetit - (sum % primerPetit));
} 

void HashTableDictionary::afegir (string key) { 
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
            if (hashTable[newIndex] == "nnnn") {
                hashTable[newIndex] = key;
                if(i > maxcolision) maxcolision = i;
                found = true;
            }
            i++;
         }
    }
    else hashTable[index] = key;
}

bool HashTableDictionary::comprovar (string s) {
    int index = hash1(s);
    if (hashTable[index] != s) {
        int index2 = hash2(s);
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