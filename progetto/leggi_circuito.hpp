#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "Grafi.h"
#include <map>

using namespace std;

//passiamo il nome file e dei vector vuoti, cosicche verranno riempiti durante la lettura del file
template <typename T>
bool leggi_netlist(const string& nomefile,map<undirected_edge<T>,string>& Nome_res,map<undirected_edge<T>,double>& resistenze,map<undirected_edge<T>,double>& generatori,undirected_graph<T>& grafo) {
    ifstream file(nomefile);

    if(file.is_open()) {
        string nome;
        double valore;
        T nodo1;
        T nodo2;
        // fa si che dopo l'ultima riga non entri per errori e salvi archi non esistenti
        while (!file.eof()) {
            
            
            //prende i vari elementi, spartendo dove sono presenti spazi
            file >> nome >> valore >> nodo1 >> nodo2;
            
            

            undirected_edge<T> arco=undirected_edge<T>(nodo1,nodo2,1.0);
            grafo.add_edge(arco);
            
            if (nome[0]=='R') {
                Nome_res[arco]=nome;
                resistenze[arco]=valore;
            }

            if (nome[0]=='V') {
                
                // Se nodo1 > nodo2, l'arco undirected inverte l'ordine dei nodi, e 
                // il de Pina applicherà un -1. Salvando il valore negativo,
                // i due segni si annulleranno nel main.
                if (nodo1 < nodo2) {
                    generatori[arco] = -valore;
                } else {
                    generatori[arco] = valore; 
                }
           
            }

        }
        return true;
    }
        
    return false;

}