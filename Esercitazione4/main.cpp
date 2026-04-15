#include <optional>
#include <vector>
#include <thread>
#include <chrono>
#include "sortalgoritms.hpp"
#include "timecounter.h"
#include "randfiller.h"
using namespace std;


int main(void)
{
    
    
    randfiller rf;
    timecounter tc; /* instantiate the timecounter */

    vector<int> vi;
    
    vector<int> dim = {4,8,16,32,64,128,256,512,1024,2048,4096,8192};
    for (int i = 0;i<=11;i++) {
        vi.resize(dim[i]);
        rf.fill(vi,-99,99);
        tc.tic();      /* start it */
        bubblesort(vi);
        double time_bub = tc.toc();
        tc.tic();
        sort(vi.begin(), vi.end());
        double time_std= tc.toc();
        tc.tic();      /* start it */
        insertionsort(vi);
        double time_ins = tc.toc();
        

        tc.tic();      /* start it */
        selectionsort(vi);
        double time_sel = tc.toc();

        cout<<"Standard: "<< time_std<<"\n";
        cout<<"Bubble: "<< time_bub<<"\n";
        cout<<"Insertion: "<< time_ins<<"\n";
        cout<<"Selection: "<< time_sel<<"\n";




        



       
    }



}



