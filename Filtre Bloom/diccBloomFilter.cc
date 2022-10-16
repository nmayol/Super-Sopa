
#include "diccBloomFilter.hh"

BloomFilterDictionary::BloomFilterDictionary () {
    mida = 47925;
    BloomFilter = vector<bool>(mida, false);  
    /*for (int i = 0; i < mida; ++i) {
        BloomFilter[i] = false;
    }*/
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

/*
int main () {
    vector<string> paths = {"../diccionaris/mare-balena-vocabulary-3.txt",
                            "../diccionaris/dracula-vocabulary-4.txt",
                            "../diccionaris/quijote-vocabulary-3.txt"};

    for (string path : paths) {
        cout << "Fitxer: " << path << endl;

        BloomFilterDictionary b;
        vector<string> totes;  

        ifstream fp_in;
        string a;
        fp_in.open(path);
        while (fp_in >> a) {
            totes.push_back(a);
        }
        fp_in.close(); 

        cout << "Mida: " << totes.size() << endl;

        int errors = 0, encerts = 0, comprovacions = 0;
        for (int i = 0; i < totes.size(); ++i) {
            string w = totes[i];
            b.afegir(w);

            for (int j = 0; j < i+1; ++j) {
                ++comprovacions;
                if (not b.comprovar(totes[j])) ++errors;
                else ++encerts;
            }

            for (int j = i+1; j < totes.size(); ++j) {
                ++comprovacions;
                if (b.comprovar(totes[j])) ++errors;
                else ++encerts;
            }
        }

        cout << "Errors totals: " << errors << endl;
        cout << "Encerts totals: " << encerts << endl;
        cout << "Comprovacions: " << comprovacions << endl;
    }    
}
*/