#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

void CountingSort(int t[], int n, int k){
    int* counters = new int[k];
    int* result = new int[n];

    for(int i=0; i<k; i++) counters[i] = 0;
    for(int i=0; i<n; i++) counters[t[i]]++;
    for(int i=1; i<k; i++) counters[i] += counters[i-1];
    for(int i=n-1; i>=0; i--){
        counters[t[i]]--;
        result[counters[t[i]]] = t[i];
    }
    for(int i=0; i<n; i++){
        t[i] = result[i];
    }
    delete[] counters;
    delete[] result;
}

int main(){
    int t[] = {1,5,2,3,4,6};
    CountingSort(t, 6, 10);
    Wypisz(t, 6);
}
