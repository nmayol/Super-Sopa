#include "diccBloomFilter.hh"

BloomFilterDictionary::BloomFilterDictionary () {

    for (int i = 0; i < mida; ++i) {
        BloomFilter[i] = false;
    }
}

void BloomFilterDictionary::afegir (const string& s) {
    int a = h1(s);
    //cout << 'a';
    int b = h2(s);
    //cout << 'b';
    int c = h3(s);
    //cout << 'c';
    int d = h4(s);
    //cout << 'd';
    int e = h5(s);
    //cout << 'e';
    int f = h6(s);
    //cout << 'f';
    int g = h7(s);    

    //cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << ' ' << g << endl;
    //cout << "hashos" << endl;
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

//polinòmiques
int BloomFilterDictionary::h1 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        //cout << s[i] << ' ';
        int valor = (int)s[i];
        hash = 11*hash + valor;
    }
    //cout << "ooo" << ' ';
    int res = hash % mida;
    //cout << res << endl;
    return abs(hash % mida);
}

int BloomFilterDictionary::h2 (const string& s) {
    long long int hash = 0;

    for (int i = 0; i < s.size(); ++i) {
        int valor = (int)s[i];
        hash = 31*hash + valor;
        //cout << "o " << hash << endl;
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


int main () {
    BloomFilterDictionary b;

    vector<string> totes = {"espasmodicament"};   //paraules que queden per afegir al diccionari
    

    ifstream fp_in;
    string a;
    fp_in.open("../mare-balena-vocabulary-3.txt");
    while (fp_in >> a) {
        totes.push_back(a);
    }
    fp_in.close();  
    //cout << 'e';
    int errors = 0, encerts = 0, comprovacions = 0;
    for (int i = 0; i < totes.size(); ++i) {
        string w = totes[i];
        cout << w << ": " << endl;
        int e = 0, e2 = 0;
        //cout << 'e';
        b.afegir(w);
        //cout << 'e';
        for (int j = 0; j < i+1; ++j) {
            ++comprovacions;
            if (not b.comprovar(totes[j])) ++e;
            else ++e2;
        }

        for (int j = i+1; j < totes.size(); ++j) {
            ++comprovacions;
            if (b.comprovar(totes[j])) ++e;
            else ++e2;
        }

        cout << "Errors: " << e << " Encerts: " << e2 << endl;
        errors += e;
        encerts += e2;
    }

    cout << "Errors totals: " << errors << endl;
    cout << "Encerts totals: " << encerts << endl;
    cout << "Comprovacions: " << comprovacions << endl;
}