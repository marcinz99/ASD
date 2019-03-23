#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

int Merging(int t[], int p, int q, int r){
    int* tp = new int[r-p+1];
    int i = p;
    int j = q+1;
    int k = 0;
    int invs = 0;

    while(i<=q && j<=r){
        if(t[i]<=t[j]) tp[k++] = t[i++];
        else{
            invs += q-i+1;
            tp[k++] = t[j++];
        }
    }
    while(i<=q) tp[k++] = t[i++];
    while(j<=r) tp[k++] = t[j++];

    k = 0;
    while(p<=r){
        t[p++] = tp[k++];
    }
    delete[] tp;
    return invs;
}

int Inversions(int t[], int p, int r){
    if(r<=p) return 0;
    int q = (p+r)/2;
    int invs = 0;
    invs += Inversions(t, p, q);
    invs += Inversions(t, q+1, r);
    invs += Merging(t, p, q, r);
    return invs;
}

void Inwersje(int t[], int s){
    cout << "Liczba inwersji: ";
    cout << Inversions(t, 0, s-1);
    cout << "\n";
}

int main(){
    int t[] = {6,1,4,3,5,2};
    Inwersje(t, 6);
}
