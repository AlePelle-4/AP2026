#include "Grafi.h"
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <string>
#include "randfiller.hpp"


template <typename T>
set<T> Set_di_nodi_int(const int numeronodi) {
    set<T> insieme;
    for(int i=1;i<=numeronodi;i++) {
        insieme.insert(i);
    }
    return insieme;
}

template <typename T>
list<undirected_edge<T>> list_di_archi_random(const vector<T>& vec_uno,const vector<T>& vec_due) {
    list<undirected_edge<T>> lista;

    for(size_t i=0;i<vec_uno.size();i++) {
        if (vec_uno[i]!=vec_due[i]) {
            lista.push_back(undirected_edge(vec_uno[i],vec_due[i]));
        }
    }
    return lista;
}

int main(void)
{
    randfiller rf;
    int num_nodi=20;
    int num_archi=40;
    vector<int> vi_uno;
    vector<int> vi_due;
    vi_uno.resize(num_archi);
    vi_due.resize(num_archi);
    rf.fill(vi_uno,1,num_nodi);
    rf.fill(vi_due,1,num_nodi);
    list<undirected_edge<int>> archi;
    archi=list_di_archi_random(vi_uno,vi_due);
     set<int> nodi;
    nodi=Set_di_nodi_int<int>(num_nodi);
    
    undirected_graph<int> grafo(nodi,archi);

    

    size_t n_archi_grafo = grafo.all_edges(true);
    if (n_archi_grafo != archi.size()) {
        cerr << "All_edges è un fallito";
        return EXIT_FAILURE;
    };

    if (!archi.empty()) {
        undirected_edge<int> primo = *(archi.begin());
        int nodo_a = primo.uno;
        set<undirected_edge<int>> vicini_a = grafo.neighbours(nodo_a);
        
        if (vicini_a.find(primo) == vicini_a.end()) {
            cerr << "Neigbours ha fallito";
            return EXIT_FAILURE;
        }
    }

    if (!archi.empty()) {
        int indice = grafo.edge_number(archi.back());
        if (indice < 0) {
            cerr << "Edge Number fallito";
            return EXIT_FAILURE;
        }
    }

    if (n_archi_grafo > 0) {
        undirected_graph<int> g_sottraendo;
        g_sottraendo.add_edge(*(archi.begin()));
        
        undirected_graph<int> risultato = grafo - g_sottraendo;
        if (risultato.all_edges(false) != (n_archi_grafo - 1)) {
            cerr << "Sottrazione fallita";
            return EXIT_FAILURE;
        }
    }
    cout << "Test passati, daje!";
    
    return EXIT_SUCCESS;
}