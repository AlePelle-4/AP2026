#include <vector>
#include <iostream>
#include <optional>
#include <string>
#include "randfiller.h"
#include "sortalgoritms.hpp"
using namespace std;


int main(void)
{
    
    
    randfiller rf;

    vector<int> dim;
    vector<int> vi;
    


    dim.resize(100);
    rf.fill(dim,1,200);
    for (int i=0;i<100;i++) {
        vi.resize(dim[i]);
        rf.fill(vi,-99,99);
        Mergesort(vi,0,dim[i]-1);
        is_sorted(vi);  
        

    }
    
    vector<string> vec_str;
    vec_str.resize(10);
    vec_str={"Savona","Albisola","Celle","Varazze","Cogoleto","Arenzano","Voltri","Pra","Pegli","Sampierdarena"};
    Mergesort(vec_str,0,9);
    is_sorted(vec_str);
    
    




    return 0; 

}