#pragma once
#include <optional>
#include <list>
#include <iostream>
#include "Grafi.h"
#include <limits>
#include <queue>
using namespace std;

template <typename T>
class stack {
private:
    list<T> pila;
    typename list<T>::iterator iteratore;
    bool tipo=true;

public:
    stack() {
        iteratore = pila.end();
    }

    bool empty() {
        return pila.empty();
    }

    void put(const T& elemento) {
        pila.push_back(elemento);
        iteratore = --pila.end(); 
    }

    optional<T> get() {
        if (pila.empty()) {
            return nullopt;
        }
        T valore = *iteratore;
        pila.pop_back();
        iteratore = pila.end();
        if (!pila.empty()) {
            iteratore = --pila.end();
        }

        return valore;
    }
};

template <typename T>
class coda {
    private:
        list<T> queue;
        typename list<T>::iterator iteratore;
        bool tipo=false;

    public:
        coda() {
            iteratore = queue.begin();
        }

        bool empty() {
            return queue.empty();
        }

        void put(const T& elemento) {
            queue.push_front(elemento);
            iteratore =queue.begin(); 
        }

    optional<T> get() {
        if (queue.empty()) {
            return nullopt;
        }
        T valore = queue.back(); 
        queue.pop_back();        
        return valore;
    }
        
    };
template <typename T,typename C>
undirected_graph<T> graph_visit(const undirected_graph<T>& grafo, const T& nodo_sorgente, C& contenitore)
{
    //inserisco nel contenitore il nodo da visita e il padre
    contenitore.put(vector<T>{nodo_sorgente, nodo_sorgente});
    undirected_graph<T> albero;
    // me la inizializza a false
    std::map<T,bool> reached;


    while (!(contenitore.empty()))
    {
        
        // essendo che il mio get mi restituisce un oggetto optional, va dereferenziato
        std::vector<T> elemento = *(contenitore.get());

        T nodo_corrente = elemento[1];
        T padre = elemento[0];

        //se già visitato salto
        if(reached[nodo_corrente])
        {
            continue;
        }

        //ora che l'ho estratto lo segno come visitato
        reached[nodo_corrente] = true;

        //se non è il nodo sorgente ho bisogno del padre
        if (nodo_corrente != nodo_sorgente)
        {
            albero.add_edge(undirected_edge<T>(padre, nodo_corrente, 1.0));
        }

        set<T> vicini = grafo.neighbours(nodo_corrente);
        
        for(auto iteratore = vicini.begin(); iteratore != vicini.end(); iteratore++)
        {   
            T nodo_vicino = *iteratore;

            if (!reached[nodo_vicino])//se non esiste ancora mi mette di default il valore false
            {
                //std::cout<<nodo_vicino<<" "<<nodo_corrente<<"\n";
                //salvo da quale nodo ci arrivo
                contenitore.put(vector<T>{nodo_corrente, nodo_vicino});
            }
        }

    }

    return albero;    

}

template <typename T>  
undirected_graph<T> recursive_dfs(undirected_graph<T>& grafo,T u,map<T,bool>& reached,undirected_graph<T>& grafo_dfs) {
    set<T> set_adiacenza=grafo.neighbours(u);
    list<undirected_edge<T>> archi_dfs;
    set<T> nodi_dfs;
    reached[u]=true;
    grafo_dfs.nodi.insert(u);
    for (auto it=set_adiacenza.begin();it!=set_adiacenza.end();++it) {
        if (reached[*it]==false) {
            grafo_dfs.add_edge(undirected_edge<T>(u, *it,1.0));
            recursive_dfs(grafo,*it,reached,grafo_dfs);
            }
        }  
    return grafo_dfs;
}



template <typename T>
undirected_graph<T> Dijkstra(const undirected_graph<T>& grafo,T sorgente) {
    set<T> set_adiacenza;
    list<undirected_edge<T>> archi_dijkstra;
    // coda con priorità, ordinata rispetto alla distanza (sulla punta della pila i + vicini)
    set<pair<double, T>> pq;
    map<T,T> pred;
    map<T,double> dist;
    // la distanza massima tra due nodi se i pesi sono 1 è il numero di nodi piu uno
    double infinito = grafo.nodi.size()+1;
    for (auto it=grafo.nodi.begin();it!=grafo.nodi.end();++it) {
        dist[*it]=infinito;
    }
    pred[sorgente]=sorgente;
    dist[sorgente]=0;
    for (auto it=grafo.nodi.begin();it!=grafo.nodi.end();++it) {
        pq.insert({dist[*it],*it});
    }
    while (pq.empty()!=true) {
        auto [d, u] = *pq.begin(); 
        pq.erase(pq.begin());
        set_adiacenza=grafo.neighbours(u);
        for (auto it=set_adiacenza.begin();it!=set_adiacenza.end();++it) {
            undirected_edge<T> arco=undirected_edge(u,*it,1.0);
            if ( dist[*it]>d+arco.peso) {
                //tolgo la vecchia distanza
                pq.erase({dist[*it],*it});
                dist[*it]=d+arco.peso;
                pred[*it]=u;
                // metto la nuova
                pq.insert({dist[*it],*it});
                

            }
            
        }    
    }
    for (auto it=pred.begin();it!=pred.end();++it) {
        T nodo = it->first;
        T padre = it->second;
        if (nodo!=padre){
            archi_dijkstra.push_back(undirected_edge(nodo,padre,1.0));
        }
        
    }

    return undirected_graph(grafo.nodi,archi_dijkstra);

    
}







