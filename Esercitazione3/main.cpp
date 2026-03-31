#include "rational.hpp"
#include <iostream>

using namespace std;


int main(void)
{
    cout << "questo programma svolge operazioni tra razionali" << "\n";
    int num1;
    int num2;
    int den1;
    int den2;
    cout << "inserisci numeratore uno" << "\n";
    cin >> num1;
    cout << "inserisci denominatore uno" << "\n";
    cin >> den1;
    rational<int> a(num1,den1);
    cout << "inserisci numeratore due" << "\n";
    cin >> num2;
    cout << "inserisci denominatore due" << "\n";
    cin >> den2;
    rational<int> b(num2,den2);
    rational<int> c;
    c=a.operator+(b);
    
    cout << "somma: " ;
    c.print();
    c=a.operator-(b);
    
    cout << "differenza: " ;
    c.print();

    c=a.operator*(b);
    
    cout << "prodotto: " ;
    c.print();

    c=a.operator/(b);
    
    cout << "rapporto: " ;
    c.print();
}




    