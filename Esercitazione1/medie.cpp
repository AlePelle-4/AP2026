#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]) {
    if ( argc<2 ) {
        cerr << "Errore, manca l'input \n";
    }
    
    else { 
        string filename=argv[1];
        ifstream ifs(filename);
        if ( ifs.is_open() ) {
            while( !ifs.eof() ) {
                string città;
                double temp1, temp2, temp3, temp4;
                
                ifs >> città >> temp1 >> temp2 >> temp3 >> temp4;
                double media=(temp1+temp2+temp3+temp4)/4;
                cout << città << " " << media << "\n";
                }
            }
        else {
            cerr << "Errore lettura file \n";
        }
    }
}



            
