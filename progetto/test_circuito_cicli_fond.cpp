#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>

#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Eigenvalues>

#include "Grafi.h"
#include "depina.hpp"
#include "leggi_circuito.hpp"
#include "gradiente_coniugato.hpp"
#include "timecounter.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Errore: fornire il file netlist come argomento. (es. ./test_circuito circuito_grande.txt)" << endl;
        return EXIT_FAILURE;
    }
    string nomefile = argv[1];

    map<undirected_edge<int>, string> Nome_res;
    map<undirected_edge<int>, double> resistenze;
    map<undirected_edge<int>, double> generatori;
    undirected_graph<int> grafo;

    if (!leggi_netlist(nomefile, Nome_res, resistenze, generatori, grafo)) {
        cerr << "Errore nella lettura del file netlist." << endl;
        return EXIT_FAILURE;
    }

    
    // (De Pina + Gradiente Coniugato)
    


    vector<Eigen::VectorXd> Matrice_incidenza = trova_cicli_fondamentali(grafo);

    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(resistenze.size(), resistenze.size());
    size_t j = 0;
    for (auto it = resistenze.begin(); it != resistenze.end(); ++it) {
        R(j, j) = it->second;
        j++;
    }

    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(resistenze.size(), Matrice_incidenza.size());
    map<undirected_edge<int>, int> indice_arco_in_matrice_B;
    
    size_t k = 0;
    for (auto it = resistenze.begin(); it != resistenze.end(); ++it) {
        int indice_resistenza = grafo.edge_number(it->first);
        for (size_t i = 0; i < Matrice_incidenza.size(); i++) {
            B(k, i) = Matrice_incidenza[i](indice_resistenza);
        }
        indice_arco_in_matrice_B[it->first] = k;
        k++;
    }

    Eigen::VectorXd v = Eigen::VectorXd::Zero(B.cols());
    for (size_t i = 0; i < Matrice_incidenza.size(); i++) {
        double tensione_maglia = 0.0;
        for (auto it = generatori.begin(); it != generatori.end(); ++it) {
            int indice_gen = grafo.edge_number(it->first);
            tensione_maglia -= (it->second) * Matrice_incidenza[i](indice_gen);
        }
        v(i) = tensione_maglia;
    }

    Eigen::MatrixXd A_sistema = B.transpose() * R * B;

    
    const unsigned int it_max = 10000;
    const double tol = 1.0e-15;
    Eigen::VectorXd x0 = Eigen::VectorXd::Zero(B.cols());

    Eigen::VectorXd correnti = gradiente_coniugato(A_sistema, v, x0, tol, it_max);

    Eigen::VectorXd tensioni_alg = R * B * correnti;


    
    //  Metodo Manuale
    
    // M1: R1+R2+R3 = 10+15+5=30. Condivide R1(10) con M2
    // M2: R4+R5+R1 = 20+25+10=55. Condivide R5(25) con M3
    // M3: R6+R7+R5 = 30+10+25=65. Condivide R7(10) con M4
    // M4: R8+R9+R10+R7 = 40+50+12+10=112.

    // Le maglie attraversano i generatori da + a -, quindi termini noti negativi
    // v_man << -12, -24, -9, -5; 

    // Risolvo analiticamente (Tensioni precalcolate dal sistema matriciale esatto)

    // Calcolo le tensioni manuali su ogni resistore usando V = R * I_netta
    map<string, double> V_attesa;
    V_attesa["R1"]  = 1.03913;  // Condivisa M1-M2
    V_attesa["R2"]  = 9.77940;  // Solo M1
    V_attesa["R3"]  = 3.25980;  // Solo M1
    V_attesa["R4"]  = 15.11740; // Solo M2
    V_attesa["R5"]  = 7.84375;  // Condivisa M2-M3
    V_attesa["R6"]  = 13.26360; // Solo M3
    V_attesa["R7"]  = 3.58000;  // Condivisa M3-M4
    V_attesa["R8"]  = 3.36480;  // Solo M4
    V_attesa["R9"]  = 4.20600;  // Solo M4
    V_attesa["R10"] = 1.00944;  // Solo M4

    bool test_superato = true;
    double tolleranza = 1e-3;

    size_t idx = 0;
    // Iteriamo sull'ordine originale usato per creare R e tensioni_alg
    for (auto const& [arco, valore_R] : resistenze) {
        
        // 1. Recupero il nome del resistore da quell'arco
        string nome_resistore = Nome_res[arco];
        
        // 2. Prendo la tensione attesa dalla mappa
        double tensione_attesa = V_attesa[nome_resistore];
        
        // 3. Prendo il modulo della tensione calcolata dall'algoritmo
        double tensione_calcolata = std::abs(tensioni_alg(idx));

        // Confronto
        if (std::abs(tensione_calcolata - tensione_attesa) > tolleranza) {
            cout << "Errore su " << nome_resistore 
                 << ": attesa = " << tensione_attesa 
                 << ", calcolata = " << tensione_calcolata << "\n";
            test_superato = false;
        }
        idx++;
    }

}