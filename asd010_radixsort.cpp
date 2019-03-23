#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

void SortByPosition(int t[], int n, int q){
    int k = 10;
    int* counters = new int[k];
    int* result = new int[n];

    for(int i=0; i<k; i++) counters[i] = 0;
    for(int i=0; i<n; i++) counters[(t[i]/q)%10]++;
    for(int i=1; i<k; i++) counters[i] += counters[i-1];
    for(int i=n-1; i>=0; i--){
        counters[(t[i]/q)%10]--;
        result[counters[(t[i]/q)%10]] = t[i];
    }
    for(int i=0; i<n; i++) t[i] = result[i];
    delete[] counters;
    delete[] result;
}

void RadixSort(int t[], int s){
    if(s==0) return;
    int maxm = t[0];
    for(int i=1; i<s; i++){
        if(t[i]>maxm) maxm = t[i];
    }
    for(int i=1; maxm>0; i*=10, maxm/=10){
        SortByPosition(t, s, i);
    }
}

int main(){
    int t[] = {5,6,4,1,3,15,2};
    RadixSort(t, 7);
    Wypisz(t, 7);
}
