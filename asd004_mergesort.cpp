#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

void Merge(int t[], int p, int q, int r){
    int* tp = new int[r-p+1];
    int i = p;
    int j = q+1;
    int k = 0;

    while(i<=q && j<=r){
        if(t[i]<t[j]) tp[k++] = t[i++];
        else tp[k++] = t[j++];
    }
    while(i<=q) tp[k++] = t[i++];
    while(j<=r) tp[k++] = t[j++];

    k = 0;
    while(p<=r){
        t[p++] = tp[k++];
    }
    delete[] tp;
}

void MergeSort(int t[], int p, int r){
    if(p>=r) return;

    int q = (p+r)/2;
    MergeSort(t, p, q);
    MergeSort(t, q+1, r);
    Merge(t, p, q, r);
}

int main(){
    int t[] = {1,2,3,5,6,3,3};
    MergeSort(t,0,6);
    Wypisz(t, 7);
}
