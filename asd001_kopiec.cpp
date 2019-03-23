#include <iostream>
#define hsize(n) n.t[0]
using namespace std;

struct kopiec{
    int* t;
    kopiec(){};
    kopiec(int a[], int s){
        t = new int[s+1];
        t[0] = s;
        for(int i=1; i<=s; i++){
            t[i] = a[i-1];
        }
    }
};

int parent(int i){return i/2;}
int left(int i){return 2*i;}
int right(int i){return 2*i+1;}

void Wypisz(kopiec heap){
    cout << "Elementy: ";
    for(int i=1; i<=hsize(heap); i++){
        cout << heap.t[i] << ", ";
    }cout << "\n";
}

void Heapify(kopiec heap, int i){
    if(i<=0 || i>hsize(heap)) return;
    int p = left(i);
    int r = right(i);
    int maxm = i;

    if(p<=hsize(heap) && heap.t[p]>heap.t[maxm]){
        maxm = p;
    }
    if(r<=hsize(heap) && heap.t[r]>heap.t[maxm]){
        maxm = r;
    }
    if(maxm!=i){
        heap.t[maxm]^=heap.t[i]^=heap.t[maxm]^=heap.t[i];
        Heapify(heap, maxm);
    }
}

kopiec BuildHeap(int t[], int s){
    kopiec heap = kopiec(t, s);
    for(int i=s/2; i>0; i--){
        Heapify(heap, i);
    }
    return heap;
}

int main(){
    int t[] = {1,2,3,4,5,6,7,8,9,10};
    kopiec heap = BuildHeap(t, 10);
    Wypisz(heap);
}
