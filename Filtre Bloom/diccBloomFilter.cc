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

    //cout << s << endl;
    //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << ' ' << g << endl;
}

bool BloomFilterDictionary::comprovar (const string& s) {
    int a = h1(s);
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);
    int e = h5(s);
    int f = h6(s);
    int g = h7(s);    

    //cout << s << endl;
    //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << ' ' << g << endl;

    return BloomFilter[a] and BloomFilter[b] and BloomFilter[c] and 
        BloomFilter[d] and BloomFilter[e] and BloomFilter[f] and BloomFilter[g];
}

void BloomFilterDictionary::imprimir () {
    for (int i = 0; i < mida; ++i) {
        cout << BloomFilter[i] << ' ';
    }
    cout << endl;
}

//polinòmiques
int BloomFilterDictionary::h1 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 11*hash + valor;
    }

    return hash % mida;
}

int BloomFilterDictionary::h2 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 31*hash + valor;
    }

    return hash % mida;
}

int BloomFilterDictionary::h3 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 83*hash + valor;
    }

    return hash % mida;
}

//altres
int BloomFilterDictionary::h4 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 137*hash + valor;
    }

    return hash % mida;
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

    return hash % mida;
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

    return hash % mida;
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

    return hash % mida;
}




int main () {
    BloomFilterDictionary b;

    vector<string> paraules = {"hola", "adeu", "mec", "avui", "dema"};

    for (int i  = 0; i < paraules.size(); ++i) {
        b.afegir(paraules[i]);
    } 
    //b.imprimir();
    cout << endl;
    vector<string> comprovar = {"hol", "hola", "adu", "adeu", "adue", "esteve"};
    for (int i  = 0; i < comprovar.size(); ++i) {
        cout << comprovar[i] << ' ' << b.comprovar(comprovar[i]) << endl;
    } 
    //cout << b.comprovar("hola") << ' ' << b.comprovar("adeu");
}