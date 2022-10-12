#include "diccBloomFilter.hh"

BloomFilterDictionary::BloomFilterDictionary () {

    for (int i = 0; i < mida; ++i) {
        BloomFilter[i] = false;
    }
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

    cout << s << endl;
    cout << a << ' ' << b << ' ' << c << endl;
}

bool BloomFilterDictionary::comprovar (const string& s) {
    int a = h1(s);
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);
    int e = h5(s);
    int f = h6(s);
    int g = h7(s);    

    return BloomFilter[a] and BloomFilter[b] and BloomFilter[c] and 
        BloomFilter[d] and BloomFilter[e] and BloomFilter[f] and BloomFilter[g];
}

void BloomFilterDictionary::imprimir () {
    for (int i = 0; i < mida; ++i) {
        cout << BloomFilter[i] << ' ';
    }
    cout << endl;
}

//83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 
//151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199

int BloomFilterDictionary::h1 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor;
        hash = hash % mida;
    }

    return hash;
}

int BloomFilterDictionary::h2 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor%83;
        hash = hash;// % mida;
    }

    return hash % mida;
}

int BloomFilterDictionary::h3 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor%89;
        hash = hash;// % mida;
    }

    return hash % mida;
}

int BloomFilterDictionary::h4 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor%131;
        hash = hash;// % mida;
    }

    return hash % mida;
}

int BloomFilterDictionary::h5 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor%193;
        hash = hash;// % mida;
    }

    return hash % mida;
}

int BloomFilterDictionary::h6 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor%197;
        hash = hash;// % mida;
    }

    return hash % mida;
}

int BloomFilterDictionary::h7 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = hash + valor%199;
        hash = hash;// % mida;
    }

    return hash % mida;
}

int main () {
    BloomFilterDictionary b;

    vector<string> 
    b.afegir("hola");
    b.imprimir();
    b.afegir("bon");
    b.imprimir();
    b.afegir("dia");
    b.imprimir();
    b.afegir("mec");
    b.imprimir();
    //cout << b.comprovar("hola") << ' ' << b.comprovar("adeu");
}