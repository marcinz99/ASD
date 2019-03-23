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

int left(int i){return 2*i;}
int right(int i){return 2*i+1;}
int parent(int i){return i/2;}

void Wypisz(kopiec heap){
    cout << "Elementy: ";
    for(int i=1; i<=hsize(heap); i++){
        cout << heap.t[i] << ", ";
    }cout << "\n";
}

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

void Heapify(kopiec heap, int i){
    if(i<=0 || i>hsize(heap)) return;
    int p = left(i);
    int r = right(i);
    int maxm = i;

    if(p<=hsize(heap) && heap.t[p]>heap.t[maxm]) maxm = p;
    if(r<=hsize(heap) && heap.t[r]>heap.t[maxm]) maxm = r;
    if(maxm!=i){
        heap.t[i]^=heap.t[maxm]^=heap.t[i]^=heap.t[maxm];
        Heapify(heap, maxm);
    }
}

kopiec BuildHeap(int t[], int s){
    kopiec heap(t, s);
    for(int i=s/2; i>0; i--){
        Heapify(heap, i);
    }
    return heap;
}

void Heapsort(int t[], int s){
    kopiec heap = BuildHeap(t, s);

    for(int i=hsize(heap); i>1; i--){
        heap.t[1]^=heap.t[i]^=heap.t[1]^=heap.t[i];
        hsize(heap)--;
        Heapify(heap, 1);
    }
    for(int i=0; i<s; i++){
        t[i] = heap.t[i+1];
    }
}

int main(){
    int t[] = {1,3,2,4,5};
    Heapsort(t, 5);
    Wypisz(t, 5);
}
