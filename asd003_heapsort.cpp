#include <iostream>
#define hsize(n) (*n).t[0]
using namespace std;

struct kopiec{
    int* t;
    kopiec(){};
    kopiec(int a[], int s){
        t = new int[s+1];
        t[0] = s;
        for(int i=0; i<s; i++){
            t[i+1] = a[i];
        }
    };
};

int parent(int i){return i/2;}
int left(int i){return 2*i;}
int right(int i){return 2*i+1;}

void Wypisz(kopiec* heap){
    cout << "Elementy: ";
    for(int i=1; i<=hsize(heap); i++){
        cout << heap->t[i] << ", ";
    }cout << "\n";
}

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

void Heapify(kopiec* &heap, int i){
    if(i<=0 || i>hsize(heap)) return;
    int maxm = i;
    int p = left(i);
    int r = right(i);

    if(p<=hsize(heap) && heap->t[p] > heap->t[maxm]) maxm = p;
    if(r<=hsize(heap) && heap->t[r] > heap->t[maxm]) maxm = r;
    if(i != maxm){
        heap->t[maxm]^=heap->t[i]^=heap->t[maxm]^=heap->t[i];
        Heapify(heap, maxm);
    }
}

void BuildHeap(kopiec* &heap, int t[], int s){
    if(heap != nullptr) heap = nullptr;
    heap = new kopiec(t, s);

    for(int i=s/2; i>0; i--){
        Heapify(heap, i);
    }
}

void Heapsort(int t[], int s){
    if(s==0) return;
    kopiec* heap = nullptr;
    BuildHeap(heap, t, s);

    int i = 0;
    while(hsize(heap)>0){
        t[i++] = heap->t[1];
        heap->t[1]^=heap->t[hsize(heap)]^=heap->t[1]^=heap->t[hsize(heap)];
        hsize(heap)--;
        Heapify(heap, 1);
    }
}

int main(){
    int t[] = {1,2,3,4,5,9,8,6,7};
    kopiec* heap = nullptr;
    Heapsort(t, 9);
    Wypisz(t, 9);
}
