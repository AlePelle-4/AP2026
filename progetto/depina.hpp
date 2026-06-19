#pragma once
#include <list>
#include <iostream>
#include "Grafi.h"
#include "contenitori.hpp"
#include <limits>
#include <queue>
#include <vector>
#include <type_traits>
#include <utility>

using namespace std;


template <typename T>
undirected_graph<T> crea_cografo(const undirected_graph<T>& grafo) 
        {
            if(grafo.nodi.empty())
            {
                return undirected_graph<T>();
            }
            
            //Creo una stack, quella della mia classe, non quella std
            ::stack<vector<T>> pila;
            T nodo_sorgente = *grafo.nodi.begin();
            undirected_graph<T> T_dfs = graph_visit(grafo, nodo_sorgente,pila);
            undirected_graph<T> co_grafo = (grafo) - T_dfs;

            return co_grafo;
        }


int prodotto_scalare(const vector<bool>& s, const vector<bool>& p) {
    int prod = 0;
    
    for (size_t i = 0; i < s.size(); i++) {
        
        // Se entrambi sono 1, aggiungo 1
        if (s[i] && p[i]) {
            prod++;
        }
    }
    
    // Alla fine prendo il modulo due
    return prod % 2;
}

vector<bool> differenza_simmetrica(const vector<bool>& s,const vector<bool>& p) {
    vector<bool> diff;
    diff.resize(s.size());
    for (size_t i = 0; i< s.size(); i++)
    {
        if (s[i]!=p[i]) {
            diff[i]=true;
        }
        else {
            diff[i]=false;
        }

    }
    return diff;
    
}

template <typename T>
bool trova_percorso(const undirected_graph<T>& grafo,T u,T v,list<T>& path,map<T,bool>& reached) {
    reached[u]=true;
    
    
    path.push_back(u);
    if (u==v) {
        return true;
    }
    set<T> vicini = grafo.neighbours(u);
    for(auto it = vicini.begin(); it != vicini.end(); it++) {
        if (reached[*it]!=true) {
            if (trova_percorso(grafo,*it,v,path,reached)==true) {
                return true;
            }

        }
    }
    path.pop_back();
    return false;
}



template <typename T>
vector<Eigen::VectorXd> trova_cicli_fondamentali(const undirected_graph<T>& grafo) {
    ::stack<vector<T>> pila;

    T nodo_sorgente = *grafo.nodi.begin();
    undirected_graph<T> T_dfs = graph_visit(grafo, nodo_sorgente, pila);
    undirected_graph<T> co_grafo = (grafo) - T_dfs;
    vector<Eigen::VectorXd> cicli;

    // Per ogni arco (u, v) nel coalbero, chiudo il ciclo guardando se c'è un cammino tra u e v nell'albero dfs
    //infatti, nell'albero dfs non c'è l'arco (u,v
    // per questo motivo, ogni ciclo trovato è generato da un diverso arco del cografo, pertanto i cicli saranno linearmente indipendenti
   // essi formeranno una base
    for (auto it = co_grafo.archi.begin(); it != co_grafo.archi.end(); ++it) {
        T u = (*it).uno;
        T v = (*it).due;
        // Trovo il percorso tra u e v in T_dfs

        list<T> path;
        map<T, bool> reached;  
        if (trova_percorso(T_dfs, u, v, path, reached)) {

            

            // Ottengo il vettore orientato per il cammino nell'albero
            Eigen::VectorXd C_or = crea_vettore_C_orientato(grafo, path);

            // Aggiungo l'arco di chiusura del coalbero (u, v)

            undirected_edge<T> arco_chiusura(u, v, 1.0);
            int indice_arco = grafo.edge_number(arco_chiusura);

            if (indice_arco != -1) {
                // Poiché il percorso nel path va da u a v, 
                // e noi dobbiamo tornare da v a u (per chiudere il ciclo),
                // stiamo percorrendo l'arco di chiusura nella direzione v -> u.
                // l'arco è salvato come (u, v)  
                C_or(indice_arco) = -1;

                

            }

            cicli.push_back(C_or);

        }

    }



    return cicli;

}




template <typename T>
list<vector<bool>> crea_vettori_S(const undirected_graph<T>& grafo) {
    undirected_graph<T> cografo=crea_cografo(grafo);
    size_t m=grafo.archi.size();
    
    list<vector<bool>> S;

    for(auto it = cografo.archi.begin(); it != cografo.archi.end(); it++) {
        //mi mette gli elementi di S_i di default a false
        vector<bool> S_i;
        S_i.resize(m);
        // Considero l'i-esimo arco nel cografo (a meno di errori, tipo che non lo trovi), nell'i-esimo vettore S,
        // metto a 1 l'elemento nella posizione che l'arco considerato ricopre negli archi del grafo principale
        int indice =grafo.edge_number(*it);
        if (indice!=-1) {
            S_i[indice]=true;
        }
        S.push_back(S_i);
    }
    return S;
}
 
    
template <typename T>
undirected_graph<pair<T,bool>> crea_grafo_liftato(const undirected_graph<T>& grafo,const vector<bool>& s) {
    set<pair<T,bool>> nodi_con_segno;
    list<undirected_edge<pair<T,bool>>> archi_liftati;
    for (auto it=grafo.nodi.begin();it!=grafo.nodi.end();it++) {
        pair<T,bool> nodo_positivo={*it,true};
        pair<T,bool> nodo_negativo={*it,false};
        // duplico i nodi originali, li creo sia con segno positivo che negativo
        
        nodi_con_segno.insert(nodo_positivo);
        nodi_con_segno.insert(nodo_negativo);
    }
    
    size_t indice_arco = 0;
    for (auto it=grafo.archi.begin();it!=grafo.archi.end();it++) {
        if (s[indice_arco]==true) {
            // Se l'arco è attivo in S, aggiungiamo gli archi che collegano il piano positivo con 
            // quello negativo, e viceversa
            
            archi_liftati.push_back(undirected_edge<pair<T,bool>>({(*it).uno,true},{(*it).due,false},1.0));
            archi_liftati.push_back(undirected_edge<pair<T,bool>>({(*it).uno,false},{(*it).due,true},1.0));
            
        } 
        else {
             // altrimenti, mettiamo solo gli archi, uno nel piano positivo e uno in quello negativo
            
            archi_liftati.push_back(undirected_edge<pair<T,bool>>({(*it).uno,true},{(*it).due,true},1.0));
            archi_liftati.push_back(undirected_edge<pair<T,bool>>({(*it).uno,false},{(*it).due,false},1.0));
        }

        indice_arco++;

    }
    return undirected_graph(nodi_con_segno,archi_liftati);
    
}


template <typename T>
vector<bool> crea_vettore_C(const undirected_graph<T>& grafo, const list<pair<T,bool>>& path) {
    
    vector<bool> C(grafo.archi.size(), false);

    //se il percorso non ha almeno 2 nodi, non ci sono archi
    if (path.size() < 2) {
        return C;
    }

    auto it = path.begin();
    pair<T,bool> precedente = *it;
    it++; 

    for (; it != path.end(); it++) {
        
        pair<T,bool> corrente = *it;
        
        // Creo l'arco senza segni
        undirected_edge<T> arco(precedente.first, corrente.first, 1.00);
        
        int indice =grafo.edge_number(arco);
        
        // Applico il modulo 2 (negazione logica)
        if (indice != -1) {
            C[indice] = !C[indice];    
        }
        precedente = corrente; 
    }
    
    return C;
}


template <typename T>
Eigen::VectorXd crea_vettore_C_orientato(const undirected_graph<T>& grafo, const list<T>& path) {
    
    // inizializzato tutto a 0
    Eigen::VectorXd C_or(grafo.archi.size());
    C_or.setZero();

    if (path.size() < 2) {
        return C_or;
    }

    auto it = path.begin();
    T precedente = *it;
    it++; 

    for (; it != path.end(); it++) {
        
        T corrente = *it;
        
        // Creo l'arco per trovare la sua posizione nel grafo
        undirected_edge<T> arco(precedente, corrente, 1.00);
        int indice = grafo.edge_number(arco);
        
        if (indice != -1) {
            if (precedente < corrente) {
                // Vado dal minore al maggiore
                C_or(indice) = 1;
            } 
            else if (precedente > corrente) {
                // Vado dal maggiore al minore
                C_or(indice) = -1;
            }
        }
        
        precedente = corrente; 
    }
    
    return C_or;
}



template <typename T>
Eigen::VectorXd crea_vettore_C_orientato_liftato(
    const undirected_graph<T>& grafo, 
    const list<pair<T,bool>>& path, 
    const vector<bool>& C_non_orientato)
{
    // inizializzato tutto a 0
    Eigen::VectorXd C_or(grafo.archi.size());
    C_or.setZero();

    if (path.size() < 2) {
        return C_or;
    }

    //prendo il primo
    auto it = path.begin();
    pair<T,bool> precedente = *it;
    it++; 

    for (; it != path.end(); it++) {
        
        pair<T,bool> corrente = *it;
        
        // Creo l'arco per trovare la sua posizione nel grafo
        undirected_edge<T> arco(precedente.first, corrente.first, 1.00);
        int indice = grafo.edge_number(arco);
        
        if (indice != -1) {
           
            // Controlla se l'arco appartiene al ciclo sul grafo non liftato. 
            // non è detto che tutti gli archi che percorro nel grafo liftati vadano nel ciclo
            // (ad esempio se passo un numero pari di volte per un nodo,alcuni archi non compariranno nel non lifato)
            if (C_non_orientato[indice] == true) {
                
                if (precedente.first < corrente.first) {
                    C_or(indice) = 1; 
                } 
                else if (precedente.first > corrente.first) {
                    C_or(indice) = -1; 
                }
            }
        }
        
        precedente = corrente; 
    }
    
    return C_or;
}

template <typename T>
pair<vector<bool>,Eigen::VectorXd> vettore_C_minimo(const undirected_graph<T>& grafo,const vector<bool>& s) {
    undirected_graph<pair<T,bool>> grafo_liftato=crea_grafo_liftato(grafo,s);
    int Lungh_minima=grafo.archi.size()+1;
    vector<bool> C_minimo;
    Eigen::VectorXd C_orientato_minimo;
    for (auto it=grafo.nodi.begin();it!=grafo.nodi.end();it++) {
        T v=*it;
        
        coda<std::vector<std::pair<int, bool>>> queue;
        
        //Essendo i pesi degli archi=1, non conviene usare il Dijkstra (O(m log n) se Priority queue implementeto con heap)
        // (estrarre il minimo O(log n),decrease-key O(log n))

        //usiamo pertanto l'albero BFS, che dalla sorgente mi trova il percorso + corto verso un nodo u (se il grafo non è pesato)
        undirected_graph<std::pair<T,bool>> Albero_BFS = graph_visit(grafo_liftato, std::pair<T,bool>{v, true}, queue);
        list<pair<T,bool>> percorso;
        map<pair<T,bool>,bool> reached;
        
        // Controlla se c'è un percorso tra v+ e v- e lo inserisce in percorso
        if (trova_percorso(Albero_BFS, {v, true}, {v, false}, percorso, reached)) {
            vector<bool> C = crea_vettore_C(grafo, percorso);
            int lunghezza_C = count(C.begin(), C.end(), true);
            
            if (lunghezza_C < Lungh_minima ) { 
                Lungh_minima = lunghezza_C;
                C_minimo = C;
                C_orientato_minimo=crea_vettore_C_orientato_liftato(grafo, percorso,C_minimo);
            }
        }
    }
    return {C_minimo,C_orientato_minimo};
}


template <typename T>
vector<Eigen::VectorXd> de_Pina(const undirected_graph<T>& grafo) {
    list<vector<bool>> vettori_S=crea_vettori_S(grafo);
    vector<Eigen::VectorXd> B;
    for (auto it=vettori_S.begin();it!=vettori_S.end();it++) {
        auto [C_i,C_i_con_segno]=vettore_C_minimo(grafo,*it);
        B.push_back(C_i_con_segno);
        for (auto iteratore=next(it);iteratore!=vettori_S.end();++iteratore) {
            if (prodotto_scalare(C_i,*iteratore)==1) {
                *iteratore=differenza_simmetrica(*iteratore,*it);
            }
        }
    }

    return B;
}


