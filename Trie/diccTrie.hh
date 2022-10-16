#ifndef TRIE
#define TRIE

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

typedef vector<vector<bool>> matbool;
typedef vector<vector<char>> sopa;

class TrieDictionary {

    public:

        TrieDictionary();

        void afegir(const string& c);
        bool cercar_paraula();

        /*  Llegueix el diccionari i, a mesura que el va lleguint, el 
            guarda a un trie.
        */
        void llegirTrie();

        void escriure();

        /*  Simplifica el trie ja llegit. Ajunta els prefixos, es a dir,
            ajunta aquells nodes que no tenen fills i poden ajuntar-se.
        */
        void simplificaArbre();

        bool comprovar(const string& c);

        void buscarParaules(const sopa& so, matbool& v);
        void imprimirResultats() const;
        int midaMap() const;
        void buidarResultats();
        
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
        map<string,int> results;

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
        
        void calculaDireccions(const sopa& so, matbool& v, const string& par, int i, int j);
        bool posok(int i, int j, int n, const vector<vector<bool>>& v);
        bool inclouParaula(const string& a, const string& b, int i, int& k);
        void existeixParaula(const string& par, node_trie* n, int i, bool& r);


};      

#endif