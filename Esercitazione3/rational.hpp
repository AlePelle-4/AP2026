#include <concepts>
#include <iostream>
using namespace std;
template<typename I> requires std::integral<I>


class rational
{
I num_;
I den_;

public:
    rational() {
    num_=0;
    den_=1;
    }

    rational(const I& x,const I& y) {
    I num = x;
    I den = y;

    if (den == 0) {
        if (num > 0) {
            num = 1;
        }
        else if (num < 0) {
            num = -1;
        }

    }
    if ((num_ != 0 && den_ != 0)) {
        int mcd1 = mcd(num_, den_);
        num_ = num_ / mcd1;
        den_ = den_ / mcd1;
    }
        
    
    num_=num;
    den_=den;
    
    }


    void print() const {
        if (num_ == 0 && den_ == 0) {
            cout<< "NaN";
        }
        else {
            if ( (den_)==0 ) {
                if (num_ > 0) {
                    cout << "Inf" ;
                }
                else if (num_ < 0) {
                    cout << "-Inf";
                }
            }
            else {
                cout << num_ << "/" << den_;
            }
        }
        cout << "\n";      
    }
    


    int mcd(int a, int b) {
        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a;
    }

    int mcm(int a, int b) {
        return (a * b) / mcd(a, b);
    }

    rational& operator+=(const rational& rat) {
        int num2 = rat.num_;
        int den2 = rat.den_;
        
        if ((num_ == 0 && den_ == 0) || (num2 == 0 && den2 == 0)) {
            num_=0;
            den_=0;
        }
        else {
            if ( (den_*den2)==0 ) {
                rational<int> a(num_*num2,den_*den2);
                num_=a.num_;
                den_=a.den_;
            }
            else {
                int m = mcm(den_, den2);
                num_ = (num_ * (m / den_)) + (num2 * (m / den2));
                den_ = m;
                

                int mcd1 = mcd(num_, den_);
                num_ = num_ / mcd1;
                den_ = den_ / mcd1;
            }
        }

        return *this;

    }
    
    rational operator+(const rational& rat) {
        
        rational a = *this;
        a.operator+=(rat);
        return a;
    
    }

    rational& operator-=(const rational& rat) {
        int num2 = rat.num_;
        int den2 = rat.den_;
        
        if ((num_ == 0 && den_ == 0) || (num2 == 0 && den2 == 0)) {
            num_=0;
            den_=0;
        }
        else {
            if ( (den_*den2)==0 ) {
                rational<int> a(num_*(-num2),den_*den2);
                num_=a.num_;
                den_=a.den_;
            }
            else {
                int m = mcm(den_, den2);
        
                num_ = (num_ * (m / den_)) - (num2 * (m / den2));
                den_ = m;

                int mcd1 = mcd(num_, den_);
                num_ = num_ / mcd1;
                den_ = den_ / mcd1;
            }
        }

        return *this;

    
    }
    
    rational operator-(const rational& rat) {
        
        rational a = *this;
        a.operator-=(rat);
        return a;
    
    }

    rational& operator*=(const rational& rat) {
        int num2 = rat.num_;
        int den2 = rat.den_;
        
        if ((num_ == 0 && den_ == 0) || (num2 == 0 && den2 == 0)) {
            num_=0;
            den_=0;
        }
        else {
            if ( (den_*den2)==0 ) {
                rational<int> a(num_*num2,den_*den2);
                num_=a.num_;
                den_=a.den_;
            }
            else {
                int m = mcm(den_, den2);
        
                num_ *=num2;
                den_ *= den2;

                int mcd1 = mcd(num_, den_);
                num_ = num_ / mcd1;
                den_ = den_ / mcd1;
            }
        }

        return *this;  
        
    }

    rational operator*(const rational& rat) {
        
        rational a = *this;
        a.operator*=(rat);
        return a;
    
    }


    rational& operator/=(const rational& rat) {
        int num2 = rat.den_;
        int den2 = rat.num_;
        
        if ((num_ == 0 && den_ == 0) || (num2 == 0 && den2 == 0)) {
            num_=0;
            den_=0;
        }
        else {
            if ( (den_*den2)==0 ) {
                rational<int> a(num_*num2,den_*den2);
                num_=a.num_;
                den_=a.den_;
            }
            else {
                int m = mcm(den_, den2);
        
                num_ *=num2;
                den_ *= den2;

                int mcd1 = mcd(num_, den_);
                num_ = num_ / mcd1;
                den_ = den_ / mcd1;
            }
        }

        return *this;  
        
    }

    rational operator/(const rational& rat) {
        
        rational a = *this;
        a.operator/=(rat);
        return a;
    
    }

};