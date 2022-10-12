#ifndef TRIE
#define TRIE

#include <iostream>
#include <string>
using namespace std;

class TrieDictionary {

    public:

        TrieDictionary();

        void afegir_node(const string& c);
        bool cercar_paraula();
        void llegirTrie();
        void escriure();
        void simplificaArbre();
        
    private:

        struct node_trie {

            string info;

            node_trie* esq;
            node_trie* dre;
            node_trie* cnt;

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
};

#endif