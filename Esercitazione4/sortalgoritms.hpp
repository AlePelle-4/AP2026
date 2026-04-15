#include <concepts>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
int is_sorted(const vector<T>& vec) {
    for (int i = 0;i < (vec.size()-1);i++) {
        if ( vec[i+1]<vec[i] ) {
            
            return EXIT_FAILURE;
        }
    

    }
    return EXIT_SUCCESS;
}


template <typename T>
vector<T> bubblesort(const vector<T>& vec_const)
    { 
        vector<T> vec = vec_const;
        
        if (vec.size() == 0) {
            return {};
        }
        
        T a = vec[0];
        T b = vec[0];

        for (int k=0; k<(vec.size()-1); k++) {
            for (int j=(vec.size()-1);j>=(k+1); j--) {
                if ( vec[j]<vec[j-1] ) {
                    a=vec[j];
                    b=vec[j-1];
                    vec[j]=b;
                    vec[j-1]=a;
                }
            }
        }
        return vec;
    }

template <typename T>
vector<T> insertionsort(const vector<T>& vec_const)
    { 
        vector<T> vec=vec_const;
        
        
        if (vec.size() == 0) {
            return {};
        }
        
        int i=0;
        T key = vec[0];

        for (int j=1; j<(vec.size()); j++) {
            key=vec[j];
            i=j-1;

            while (i>=0 && vec[i]>key) {
                vec[i+1]=vec[i];
                i=i-1;

            }
            vec[i+1]=key;
        }
        return vec;
    }

template <typename T>
vector<T> selectionsort(const vector<T>& vec_const)
    { 
        vector<T> vec=vec_const;
        
        
        if (vec.size() == 0) {
            return {};
        }
        
        int min=0;
        T a = vec[0];
        T b = vec[0];

        for (int k=0; k<(vec.size()-1); k++) {
            min=k;
            for (int j=(k+1);j<=(vec.size()-1); j++) {
                if ( vec[j]<vec[min] ) {
                    min=j;
                    
                }
            }
            a=vec[k];
            b=vec[min];
            vec[k]=b;
            vec[min]=a;
        }
        return vec;
    }
