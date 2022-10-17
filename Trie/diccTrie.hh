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

        /*  Constructora.
            Pre: cert.
            Post: s'ha creat un diccionari trie buit.
        */
        TrieDictionary();

        // MODIFICADORES.

        /*  Afegeix el string c al trie.
            Pre: cert.
            Post: s'ha afegit el string c al diccionari trie.
        */
        void afegir(const string& c);

        /*  Ajunta els prefixos, es a dir, ajunta aquells nodes que no tenen 
            fill dret ni esquerra amb el fill central que tampoc en te.
            Pre: cert.
            Post: l'arbre del p.i te ajuntat tots aquells nodes que compleixen
            la codicio explicada abans.
        */
        void simplificaArbre();

        /*  Buida el map resultat.
            Pre: cert.
            Post: el map results passa a estar buit (si es que no ho estava).
        */
        void buidarResultats();

        // CONSULTORES

        /*  Comprova si la paraula c existeix dintre del diccionari Trie.
            Pre: cert.
            Post: el resultat es cert si existeix una paraula c o una parula
            que comenci per c dintre el diccionari.
        */
        bool comprovar(const string& c);

        //void buscarParaules(const sopa& so, matbool& v);

        /*  Imprimeix una llista amb totes les paraules trobades.
            Pre: cert.
            Post: S'han escrit pel canal estandard de sortida una llista de 
            paraules amb el nombre de vegades trobada a la sopa.
        */
        void imprimirResultats() const;

        /*  Retorna el nombre de paraules trobades a la SuperSopa.
            Pre: cert.
            Post: retorna un nombre natural.
        */
        int midaMap() const;

        // LECTURA I ESCRIPTURA

        /*  Es llegeix una cadena de strings que passaran a formar el trie.
            Pre: hi ha preparats un enter n i n strings al canal estandard
            d'entrada.
            Post: s'ha guardat els n strings en forma de trie. Aquests es 
            troben guardats de manera que cada node esta format per un char.
        */
        void llegirTrie();

        /*  Escriu l'arbre.
            Pre: cert.
            Post: escriu pel canal estandard de sortida el contingut de cada
            node, si aquest es buit imprimeix un 0. 
            Imprimeix en el seguent ordre: (1) arrel (2) esquerre (3) dret.
        */
        void escriure() const;
        
    private:

        /*  La classe Trie presenta la seguent estructura:
                - node_trie: cada node del nostre trie hi guardara un string (info)
                  i tres fills: dret, central i esquerra (dre, cnt i esq
                  respectivament). 
                  Tambe, hi guardara un bool que ens indicara que en aquest node
                  hi ha l'ultim caracter d'una paraula.
                - node arrel: el primer node del nostre arbre.
                - map results: on hi guardarem les paraules que anem trobant a la
                  sopa i les vagades que hi apareixen.

            Aquest arbe, esta pensat per fer cerques. Per tant, segueix la seguent
            condicio:
                - el fill dret es mes petit que el pare.
                - el fill esquerre es mes gran que el pare.
                - el fill central hi guardem el/s seguent/s caracters que formen
                  una paraula seguida amb el pare.

        */
        struct node_trie {

            string info;

            node_trie* esq;
            node_trie* dre;
            node_trie* cnt;

            //int cerca;
            bool finalparaula;
        };

        node_trie* arrel;
        map<string,int> results;

        /*  Especificacio operacions privades.
        */

        /*  Afegeix una paraula al arbre tire.
            Pre: 0 <= i < info.size().
            Post: s'ha afegit el caracter info[i] a l'arbre del p.i.
        */
        void afegirRec(node_trie* &n, const string& info, int i);

        /*  Ajunta aquells nodes que poden anar junts.
            Pre: cert.
            Post: s'han ajuntat els nodes que no presenten fills laterals en
            un sol node.
        */
        void simplificaRec(node_trie* &n);

        //void crear_arrel(const string& info);

        /*  Consulta si el arbre es buit.
            Retorna cert si es buit, fals altrament.
        */
        //bool esbuit() const;

        /*  Escriu pel canal estandard de sortida l'arbre del p.i.
            Pre: cert.
            Post: s'ha escrit l'arbre del p.i.
        */
        void escriureRec(node_trie* n) const;
        
        /*  Mira si la paraula a es troba inclosa a b o al invers.
            Pre: 0 <= i < a.size().
            Post: el resultat es cert si una de les dues paraules es troba 
            inclosa en l'altra, fals altrament.
        */
        bool inclouParaula(const string& a, const string& b, int i, int& k);

        /*  Mira si existeix la paraula par o alguna paraula que comenci de
            la mateixa forma dintre del diccionari trie. 
            Pre: 0 <= i <= par.size().
            Post: mira si existeix la paraula i modifica el bool r, cert si
            la trobada i fals si no hi es.
        */
        void existeixParaula(const string& par, node_trie* n, int i, bool& r);


};      

#endif