#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

//mediana malego zbioru
int Median(int t[], int p, int r){
    int* a = new int[r-p+1];
    for(int i=p; i<=r; i++){
        a[i-p] = t[i];
    }
    for(int i=1; i<=r-p; i++){
        for(int j=i; j>0 && a[j-1]>a[j]; j--){
            a[j-1]^=a[j]^=a[j-1]^=a[j];
        }
    }
    int x = a[(r-p)/2];
    delete[] a;
    return x;
}

int Magic(int t[], int s){
    if(s<=5) return Median(t, 0, s-1);
    int i = 4;
    int j = 0;
    int* m = new int[(s+4)/5];

    for(; i<s; i+=5){
        m[j++] = Median(t, i-4, i);
    }
    if(i!=s+4) m[j] = Median(t, i-4, s-1);

    int x = Magic(m, (s+4)/5);
    delete[] m;
    return x;
}

int Partition(int t[], int p, int r){
    int x = Magic(t+p, r-p+1);
    int i = p-1;
    bool test = true;

    for(int j=p; j<r; j++){
        if(test && t[j]==x){
            t[j]^=t[r]^=t[j]^=t[r];
            test = false;
        }
        if(t[j]<x){
            i++;
            if(i!=j) t[i]^=t[j]^=t[i]^=t[j];
        }
    }i++;
    if(i!=r) t[i]^=t[r]^=t[i]^=t[r];
    return i;
}

int Select(int t[], int p, int r, int i){
    if(p==r) return t[p];
    int q = Partition(t, p, r);
    int k = q-p+1;

    if(i==k) return t[q];
    if(i<k) return Select(t, p, q-1, i);
    return Select(t, q+1, r, i-k);
}

int main(){
    int t[] = {3,4,2,1,5,6,10,9,12,11,8,7};
    cout << Select(t,0,12,3);
}
