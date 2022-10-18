#include "diccBloomFilter.hh"

BloomFilterDictionary::BloomFilterDictionary () {
    mida = 47925;
    BloomFilter = vector<bool>(mida, false);   
}

BloomFilterDictionary::BloomFilterDictionary (int n) {
    double p = 0.01; //ratio d'errors
    int mida = ceil((-n * log(p))/(log(2)*log(2)));
    BloomFilter = vector<bool>(mida, false);
}

void BloomFilterDictionary::afegir (const string& s) {
    int a = h1(s); 
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);
    int e = h5(s);
    int f = h6(s);
    int g = h7(s);    

    BloomFilter[a] = true;
    BloomFilter[b] = true;
    BloomFilter[c] = true;
    BloomFilter[d] = true;
    BloomFilter[e] = true;
    BloomFilter[f] = true;    
    BloomFilter[g] = true;
}

bool BloomFilterDictionary::comprovar (const string& s) {
    int a = h1(s);
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);
    int e = h5(s);
    int f = h6(s);
    int g = h7(s);    

    return BloomFilter[a] && BloomFilter[b] && BloomFilter[c] && 
        BloomFilter[d] && BloomFilter[e] && BloomFilter[f] && BloomFilter[g];
}

int BloomFilterDictionary::h1 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 11*hash + valor;
    }

    return abs(hash % mida);
}

int BloomFilterDictionary::h2 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 31*hash + valor;
    }

    return abs(hash % mida);
}

int BloomFilterDictionary::h3 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 83*hash + valor;
    }

    return abs(hash % mida);
}

//altres
int BloomFilterDictionary::h4 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 137*hash + valor;
    }

    return abs(hash % mida);
}

int BloomFilterDictionary::h5 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 16*hash + valor;

        unsigned long int g = hash & 0xF0000000L;
		if (g != 0) hash = pow(hash, g >> 24);
		hash = hash & (~g);
    }

    return abs(hash % mida);
}

int BloomFilterDictionary::h6 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 8*hash + valor;

        unsigned long int g = hash & 0xF0000000L;
		if (g != 0) hash = pow(hash, g >> 24);
		hash = hash & (~g);
    }

    return abs(hash % mida);
}

int BloomFilterDictionary::h7 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 4*hash + valor;

        unsigned long int g = hash & 0xF0000000L;
		if (g != 0) hash = pow(hash, g >> 24);
		hash = hash & (~g);
    }

    return abs(hash % mida);
}