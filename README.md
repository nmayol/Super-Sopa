# Super Sopa #
Aquest és el projecte de l'assignatura d'algorismia impartida a la Facultat d'Informàtica de Barcelona el Quatrimestre de Tardor del curs 2022-2023. Els integrants del grup som:
* Aina Gomez
* Paula Muñoz
* Jordi Palomera
* Neus Mayol

## Instruccions per executar els programes ##
1. Descarregar el contingut del repositori.
2. Crear l'executable del programa generador de sopes escrivint al terminal la comanda "make generar.exe".
3. Executar el fitxer generador de sopes escrivint "./generar.exe".
4. Triar el mètode amb el qual es vol resoldre la sopa i generar el seu executable escrivint "make experiment_[vector|trie|hash|filtre].exe" (trieu el que correspongui a l'experiment que voleu).
5. Executar el fitxer creat escrivint "./experiment_[vector|trie|hash|filtre].exe" al terminal.
6. Els resultats es disposaran a la carpeta "./resultats/resultat[Vector|Trie|Filtre|Hash]"

NOTA: Els diccionaris i la sopa són en aquest moment programats per treballar amb <em>quijote-vocabulary-6.txt<\em>. Per canviar de diccionari cal canviar la variable <em>pathDiccionari<\em> als fitxers <em>experiment_....cc<\em> i al fitxer <em>generar.cc<\em>
