#include <fstream>
#include <optional>
#include <list>
#include <iostream>
#include <limits>
#include <queue>
#include "Grafi.h"
#include "contenitori.hpp"
using namespace std;


template <typename T>
void esporta_graphviz(const undirected_graph<T>& grafo, const string& nome_file) {
    ofstream file(nome_file);
    
    if (!file.is_open()) {
        cerr << "Errore nell'apertura del file " << nome_file << endl;
        return;
    }
    //serve per non avere archi duplicati
    file << "strict graph G {\n";

    
    for (const auto& arco : grafo.archi) {
        file << "    \"" << arco.uno << "\" -- \"" << arco.due << "\";\n";
    }

    file << "}\n";
    file.close();
    cout << "File Graphviz generato: " << nome_file << endl;
}




int main() {
    undirected_graph<string> g;
    g.nodi = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    
    g.add_edge(undirected_edge<string>(string("A"), string("B")));
    g.add_edge(undirected_edge<string>(string("A"), string("C")));
    g.add_edge(undirected_edge<string>(string("B"), string("D")));
    g.add_edge(undirected_edge<string>(string("B"), string("E")));
    g.add_edge(undirected_edge<string>(string("C"), string("F")));
    g.add_edge(undirected_edge<string>(string("C"), string("G")));
    g.add_edge(undirected_edge<string>(string("D"), string("H")));
    g.add_edge(undirected_edge<string>(string("E"), string("I")));
    g.add_edge(undirected_edge<string>(string("F"), string("J")));
    g.add_edge(undirected_edge<string>(string("G"), string("H")));
    g.add_edge(undirected_edge<string>(string("I"), string("J")));

    cout << "Grafo di test a 10 nodi (A-J) generato correttamente.\n\n";

    
    coda<vector<string>> mia_coda;
    undirected_graph<string> albero_bfs = graph_visit(g, string("A"), mia_coda);
    esporta_graphviz(albero_bfs,"albero_bfs");
    
    cout << "--- 1. BFS (graph_visit con Coda) ---\nArchi generati:\n";
    for(const auto& fine : albero_bfs.archi) {
        cout << fine.uno << " -- " << fine.due<< "\n";
    }

    
    stack<vector<string>> mio_stack;
    undirected_graph<string> albero_dfs = graph_visit(g, string("A"), mio_stack);
    esporta_graphviz(albero_dfs,"albero_dfs");
    
    cout << "\n--- 2. DFS  (graph_visit con Stack) ---\nArchi generati:\n";
    for(const auto& fine : albero_dfs.archi) {
        cout << fine.uno << " -- " << fine.due << "\n";
    }

    map<string, bool> reached_dfs;
    undirected_graph<string> albero_dfs_ricorsiva;
    esporta_graphviz(recursive_dfs(g, string("A"), reached_dfs, albero_dfs_ricorsiva),"albero_dfs_ricorsivo");
    
    
    cout << "\n--- 3. DFS Ricorsiva ---\nArchi generati:\n";
    for(const auto& fine : albero_dfs_ricorsiva.archi) {
        cout << fine.uno << " -- " << fine.due << "\n";
    }

   
    undirected_graph<string> albero_dijkstra = Dijkstra(g, string("A"));
    esporta_graphviz(albero_dijkstra,"albero_dijkstra");
    
    cout << "\n--- 4. Dijkstra (Albero dei cammini minimi) ---\nArchi generati:\n";
    for(const auto& fine : albero_dijkstra.archi) {
        cout << fine.uno << " -- " << fine.due << "\n";
    }

    return 0;
}


