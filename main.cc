

#include "./SuperSopa/superSopa.hh"
#include <algorithm>
using namespace std;

int main () {
    // n es la mida de la sopa
    int n; cin >> n;
    superSopa s = superSopa(n);

    // poso aixo per provar
    
    vector <string> dic = {"a", "eee", "pol", "super", "sopa", "esternoclidomastoidal"};
    std::sort(dic.begin(), dic.end(), []
    (const std::string& first, const std::string& second){
        return first.size() > second.size();
    });


    s.costruirSopa(dic);
    //s.llegirDiccionari(dic);
    s.imprimirSopa();
    
}