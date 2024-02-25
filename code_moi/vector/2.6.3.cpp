#include "vector.h"
#include<iostream>
using namespace std;

template <typename T> Rank Vector<T>::uniquify(){
    int oldsize = _size; int i=1;
    while (i<_size)
        _elem[i-1] == _elem[i]?remove(i):i++;
        return oldsize - _size;
 }

int main(){
   // Vector<int>  V;
   return 0;
}