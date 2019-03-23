#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

int Partition1(int t[], int p, int r){
    int x = t[r];
    int i = p-1;

    for(int j=p; j<r; j++){
        if(t[j]<x){
            i++;
            if(i!=j) t[i]^=t[j]^=t[i]^=t[j];
        }
    }
    i++;
    if(i!=r) t[r]^=t[i]^=t[r]^=t[i];
    return i;
}

void Quicksort1(int t[], int p, int r){
    if(p<r){
        int q = Partition1(t, p, r);
        Quicksort1(t, p, q-1);
        Quicksort1(t, q+1, r);
    }
}

int Partition2(int t[], int p, int r){
    int x = t[p];
    while(true){
        while(t[p]<x) p++;
        while(t[r]>x) r--;
        if(p<r){
            t[p]^=t[r]^=t[p]^=t[r];
            p++; r--;
        }
        else return r;
    }
}

void Quicksort2(int t[], int p, int r){
    if(p<r){
        int q = Partition2(t, p, r);
        Quicksort2(t, p, q);
        Quicksort2(t, q+1, r);
    }
}

int main(){
    int t[] = {2,4,1,5,2,2};
    Quicksort2(t,0,5);
    Wypisz(t,6);
}
