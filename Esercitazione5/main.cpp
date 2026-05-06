#include <optional>
#include <vector>
#include <thread>
#include <chrono>
#include "sortalgoritms.hpp"
#include "timecounter.h"
#include "randfiller.h"
#include <fstream>
using namespace std;


int main(void)
{
    
    
    randfiller rf;
    timecounter tc; /* instantiate the timecounter */

    vector<vector<int>> vec;
    vector<double> tempi(6);
    vector<int> vi;
    ofstream out("tempi_medi.txt");
    for (int dim=1;dim<=300;dim++) {
        vec.clear();
        vec.resize(dim);
        

        for (int i = 0;i<dim ;i++) {
            
            vec[i].resize(i+1);
            rf.fill(vec[i],-99,99);
        }
        
        tc.tic();      
        for (int i = 0;i<dim ;i++) {
            vi=vec[i];
            bubblesort(vi);
        }
        double avg_time_bub = tc.toc()/(dim);

        tc.tic(); 

        for (int i = 0;i<dim ;i++) {
            vi=vec[i];
            insertionsort(vi);
        }
        double avg_time_ins = tc.toc()/(dim);

        tc.tic(); 

        for (int i = 0;i<dim ;i++) {
            vi=vec[i];
            selectionsort(vi);
        }
        double avg_time_sel = tc.toc()/(dim);
        
        tc.tic(); 

        for (int i = 0;i<dim ;i++) {
            vi=vec[i];
            int r=vi.size()-1;
            Mergesort(vi,0,r);
        }
        double avg_time_merge = tc.toc()/(dim);

        
        tc.tic(); 

        for (int i = 0;i<dim ;i++) {
            vi=vec[i];
            int r=vi.size()-1;
            Quicksort(vec[i],0,r);
        }
        double avg_time_quick = tc.toc()/(dim);
        
        tc.tic(); 
        
        for (int i = 0;i<dim ;i++) {
            vi=vec[i];
            sort(vi.begin(), vi.end());
        }
        double avg_time_std = tc.toc()/(dim);

            
        tempi={avg_time_std,avg_time_bub,avg_time_ins,avg_time_sel,avg_time_merge,avg_time_quick};
        Mergesort(tempi,0,5);   
        out << dim << ",";
        out << avg_time_std << ",";
        out << avg_time_bub << ",";
        out << avg_time_ins << ",";
        out << avg_time_sel << ",";
        out << avg_time_merge << ",";
        out << avg_time_quick << "\n";
        cout <<"Dimensione: "<<dim<<" Migliore: "<<tempi[0]<<"\n";
            
    }

}







