#ifndef TRIE
#define TRIE

#include <iostream>
#include <string>
#include "../SuperSopa/superSopa.hh"
using namespace std;

class TrieDictionary {

    public:

        TrieDictionary();

        void afegir_node(const string& c);
        bool cercar_paraula();
        void llegirTrie();
        void escriure();
        void simplificaArbre();

        void buscarParaulesSopa(const superSopa& ss);
        bool existeixParaula(const string& c);
        
    private:

        struct node_trie {

            string info;

            node_trie* esq;
            node_trie* dre;
            node_trie* cnt;

            int cerca;
            bool finalparaula;
        };

        node_trie* arrel;

        /* Especificacio operacions privades.
        */
        void afegirRec(node_trie* &n, const string& info, int i);

        void crear_arrel(const string& info);

        /*  Consulta si el arbre es buit.
            Retorna cert si es buit, fals altrament.
        */
        bool esbuit() const;

        void escriureRec(node_trie* n);
        void simplificaRec(node_trie* &n);

        void cercaDireccions(const superSopa& ss, vector<vector<bool>>& v, int i, int j, const string& par, int ind);
        bool buscarChar(const string& c, node_trie* n);
        bool posok(int i, int j, int n, const vector<vector<bool>>& v);
        bool busquemParaula(const string& c, node_trie* n, int i, bool& b);
        
};

#endif