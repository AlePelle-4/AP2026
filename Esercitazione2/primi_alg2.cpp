#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int main()
{
    static const int N = 10;
    double arr[N] = {0, 0.7, 7, 0.3, 8, 0, 0.5, 5, 3, 5};
    double media = 0.0;
    int i = 0;
    double minimo=arr[0];
    double massimo=arr[0];


    for (int k = 1; k<=9; k++) {
        minimo=min(arr[k],minimo);
        massimo=max(arr[k],massimo);
    }




    while ( i<10 ) {
        media=media+arr[i];
        i=i+1;
    }
    
    media=media/N;
    double deviazione_std = 0.0;
    for (int k = 0; k<=9; k++) {
        deviazione_std=deviazione_std+ ((arr[k]-media)*(arr[k]-media));
    }

    deviazione_std=sqrt(deviazione_std/N);
    

    cout << "la media è" << media << "\n";
    cout << "la deviazione standard  è" << deviazione_std << "\n";
    cout << "la media è" << media << "\n";





}




    