#include <iostream>
using namespace std;

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

int Median(int t[], int p, int r){
    int* a = new int[r-p+1];
    for(int i=p; i<=r; i++){
        a[i-p] = t[i];
    }

    for(int i=1; i<=r-p; i++){
        for(int j=i; j>0 && a[i-1]>a[i]; j--){
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
    Wypisz(m, (s+4)/5);

    int result = Magic(m, (s+4)/5);
    delete[] m;
    return result;
}

int main(){
    int t[] = {8,2,7,5,5,5,5};
    cout << Median(t,0,5) << endl;
    cout << Magic(t, 7);
}
