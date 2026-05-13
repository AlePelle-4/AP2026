#include <unordered_map>   
#include <list>     
#include <set>      
#include <map>     
#include <algorithm>
#include <iostream>

using namespace std;


template <typename T>
class undirected_edge {
    public:
        T uno;
        T due;

        
        undirected_edge(T a, T b) {
            uno = min(a,b);
            due = max(a,b);
        }

        
        undirected_edge(const undirected_edge& other) {
            uno = other.uno;
            due = other.due;
        }

        
        T from() {
            return uno;
        }

        
        T to() {
            return due;
        }

        bool operator<(const undirected_edge& arcodue) const {
            undirected_edge arcouno=*this;
        
            if ( arcouno.uno<arcodue.uno ) {
                return true;
            }
            else if (arcouno.uno==arcodue.uno) {
                if (arcouno.due<arcodue.due) {
                    return true;
                }

            else {
                return false;
            }

            }
            else {
                return false;
            }
        }

        bool operator==(const undirected_edge& arcodue) const {
            if (!(*this<arcodue) && !(arcodue<*this)) {
                return true;
            }
            else {
                return false;
            }
        }
};
template <typename T>
std::ostream& operator<<(ostream& os,const undirected_edge<T>& arco) {
            os<<"("<<arco.uno<<","<<arco.due<<")";
            return os;
        }




template <typename T>
class undirected_graph {
    public:
        set<T> nodi;
        list<undirected_edge<T>> archi;
        

        undirected_graph() {};
        
        undirected_graph(set<T> nodes,list<undirected_edge<T>> archs) {
            nodi=nodes;
            archs.sort();
            archi=archs;
        }


        undirected_graph(const undirected_graph& other) {
            nodi= other.nodi;
            archi = other.archi;
        }

        set<undirected_edge<T>> neighbours(T nodo) {
            set<undirected_edge<T>> vicini;
            
            for (auto it=archi.begin();it!=archi.end();++it ) {
                if ((*it).uno==nodo ) {
                    vicini.insert(*it);
                    cout<<(*it);
                }
                if ((*it).due==nodo ) {
                    vicini.insert(*it);
                    cout<<(*it);
                    


                }
            }
            return vicini;

        }
        size_t all_edges(bool stampa) {
            size_t contatore=0;
            for (auto it=archi.begin();it!=archi.end();++it ) {
                contatore++;
                if (stampa==true) {
                    cout<<(*it);
                }      
            }
            return contatore;
        }
        
        void add_edge(undirected_edge<T> arco_new) {
            archi.push_back(arco_new);
            archi.sort();
        }

        void all_nodes() {
            for(auto it=nodi.begin();it!=nodi.end();++it) {
                cout<<(*it)<<" ";
            }
        }

        int edge_number(undirected_edge<T> arco_cercato) {
            

            auto it = find(archi.begin(), archi.end(),arco_cercato);

            if (it != archi.end()) {
                int indice = distance(archi.begin(), it);
                cout << "L'elemento si trova all'indice: " << indice;
                return indice;
            } else {
                cout << "Elemento non trovato.";
                return -1;
            }
                
        }

        void edge_at(size_t numero_cercato) {
            size_t contatore=0;
            for (auto it=archi.begin();it!=archi.end();++it ) {
                if ( contatore==numero_cercato ) {
                    cout<<"Arco: ";
                    cout<<(*it);
                    
                    
                }
                contatore++;
            }
                
        }

        undirected_graph<T> operator-(const undirected_graph& grafo) const {
            undirected_graph<T> differenza;
            differenza.nodi=(*this).nodi;
            for (auto iter=archi.begin();iter!=archi.end();++iter ) {
                auto it = find(grafo.archi.begin(), grafo.archi.end(),*iter);

                if (it == grafo.archi.end()) {
                    differenza.archi.push_back(*iter);      
                }
            } 
            differenza.archi.sort();
            return differenza;
            }


};







            




        

