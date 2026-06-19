#include <vector>
#include <eigen3/Eigen/SVD>
#include <eigen3/Eigen/Dense>
#include <fstream>
#include <string>
#include "Grafi.h"
#include "depina.hpp"
#include "leggi_circuito.hpp"
#include "gradiente_coniugato.hpp"
#include "timecounter.h"
#include <map>
#include <ostream>

using namespace std;


int main() {
    cout<< "Inserire Nome File: ";
    string nomefile;
    cin>> nomefile;

    map<undirected_edge<int>,string> Nome_res;
    map<undirected_edge<int>,double> resistenze;
    map<undirected_edge<int>,double> generatori;
    undirected_graph<int> grafo;

    //chiamo la funzione che legge il file e mette i dati nelle mappe e nel grafo
    if ( leggi_netlist(nomefile,Nome_res,resistenze,generatori,grafo) ) {

        Eigen::MatrixXd R = Eigen::MatrixXd::Zero(resistenze.size(), resistenze.size());
        size_t j=0;
        for (auto it=resistenze.begin();it!=resistenze.end();++it) {
            //Data la mappa che associa a un arco la resistenza che c'è, crea la matrice diagonale corrispondente
            double valore_resistenza=it->second;
            R(j,j)=valore_resistenza;
            j++;
        }
        timecounter tc;


        //otteniamo i vettori C di de Pina, che ci rappresentano i cicli minimi con i loro versi di percorrenza
        //essi tengono conto però anche degli archi sui quali ci sono generatori
        tc.tic();
        vector<Eigen::VectorXd> Matrice_incidenza =de_Pina(grafo);
        double tempo_de_pina=tc.toc();
        
        Eigen::MatrixXd B = Eigen::MatrixXd::Zero(resistenze.size(), Matrice_incidenza.size());
        map<undirected_edge<int>,int> indice_arco_in_matrice_B;
       
        size_t k=0;
        for (auto it=resistenze.begin();it!=resistenze.end();++it) {
            int indice_resistenza=grafo.edge_number(it->first);

            // Andiamo a considerare nella matrice B solo gli archi su cui ci sono resistenze
            // Nei cicli di de Pina ci sono anche gli archi dei generatori (dobbiamo togliere le righe corrispondenti)
            for (size_t i=0;i<Matrice_incidenza.size();i++) {
                Eigen::VectorXd vettore=Matrice_incidenza[i];   
                B(k,i)=vettore(indice_resistenza);
                indice_arco_in_matrice_B[it->first]=k;
            
            }
            k++;
        }
        

        
        Eigen::VectorXd v = Eigen::VectorXd::Zero(B.cols());
        //Per ogni ciclo andiamo a vedere che genenatori ci sono
        for (size_t i = 0; i < Matrice_incidenza.size(); i++) {
            Eigen::VectorXd vettore_ciclo = Matrice_incidenza[i];
            double tensione_maglia = 0.0;
            
            for (auto it = generatori.begin(); it != generatori.end(); ++it) {
                int indice_gen = grafo.edge_number(it->first);
                //Sommo il totale delle tensioni sulla maglia con il segno meno, perche nel file di input 
                // le tensioni sono date da + a -, pertanto dobbiamo invertire i segni
                tensione_maglia += (it->second) * vettore_ciclo(indice_gen);
            }
            v(i) = tensione_maglia;
        }



        //fissiamo i parametri e il vettore inziale per il gradiente coniugato
        const unsigned int it_max = 10000;
        const double tol = 1.0e-15;
        Eigen::VectorXd x0 = Eigen::VectorXd::Zero(B.cols());

        Eigen::MatrixXd A_sistema = B.transpose() * R * B;
        // Calcolo Condizionamento
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver(A_sistema);
        double condizionamento = eigensolver.eigenvalues().maxCoeff() / eigensolver.eigenvalues().minCoeff();
        

        //calcolo il vettore con le correnti di maglia
        tc.tic();
        Eigen::VectorXd correnti=gradiente_coniugato(A_sistema,v,x0,tol,it_max);
        double tempo_ris_sistema=tc.toc();



        Eigen::VectorXd tensioni(resistenze.size());

        //calcolo il vettore con le tensioni ai capi di una resistenza
        tensioni=R*B*correnti;

        for (auto it=resistenze.begin();it!=resistenze.end();++it) {
            undirected_edge<int> arco=it->first;
            // uso V=R*i e calcolo la corrente in una resistenza
            double corr=tensioni(indice_arco_in_matrice_B[arco])/resistenze[arco];
            cout<<Nome_res[arco]<<": V = "<<tensioni(indice_arco_in_matrice_B[arco])<<" volts, I = "<<corr<<" amps.\n";
        }

        cout<<"Informazioni aggiuntive:"<<"\n";
        cout<<"Tempo impiegato a trovare i cicli: "<<tempo_de_pina<<"\n";
        cout<<"Tempo impiegato a risolverer il sistema: "<<tempo_ris_sistema<<"\n";
        cout<<"Condizionamento matrice (B trasposta)*R*B: "<<condizionamento;
    }
}