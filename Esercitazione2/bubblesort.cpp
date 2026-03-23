#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    static const int N = 10;
    double arr[N] = {0, 0.7, 7, 0.3, 8, 0, 0.5, 5, 3, 5};
    double ausilio1;
    double ausilio2; 

    bool scambio=true;
    while ( scambio==true ) {
    
        scambio=false;
        for (int k = 0; k<=(N-2); k++) {
            
            if ( arr[k]>arr[k+1] ) {
                ausilio1=arr[k];
                ausilio2=arr[k+1];
                arr[k]=ausilio2;
                arr[k+1]=ausilio1;
                scambio=true;
            }
        }
    }
    
    cout << "Array ordinato:" << "\n";
    
    for (int k = 0; k<=(N-1); k++) {
            cout << arr[k] << " ";
    }        
    
}
            