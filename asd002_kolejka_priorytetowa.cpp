#include <iostream>
#define hsize(n) n.t[0]
using namespace std;

struct kopiec{
    int* t;
    const int N = 0;
    kopiec(){};
    kopiec(int a[], int s) : N(s){
        t = new int[s+1];
        t[0] = s;
        for(int i=1; i<=s; i++){
            t[i] = a[i-1];
        }
    }
};

struct kolejka{
    kopiec kol;
    kolejka(){};
    kolejka(int t[], int s) : kol(kopiec(t, s)){};
};

int parent(int i){return i/2;}
int left(int i){return 2*i;}
int right(int i){return 2*i+1;}

void Wypisz(kopiec heap){
    cout << "Elementy kopca: ";
    for(int i=1; i<=hsize(heap); i++){
        cout << heap.t[i] << ", ";
    }cout << "\n";
}

void Wypisz(kolejka que){
    cout << "Elementy kopca-kolejki: ";
    for(int i=1; i<=hsize(que.kol); i++){
        cout << que.kol.t[i] << ", ";
    }cout << "\n";
}

void Heapify(kopiec heap, int i){
    if(i<=0 || i>hsize(heap)) return;
    int maxm = i;
    int p = left(i);
    int r = right(i);

    if(p<=hsize(heap) && heap.t[p]>heap.t[maxm]){
        maxm = p;
    }
    if(r<=hsize(heap) && heap.t[r]>heap.t[maxm]){
        maxm = r;
    }
    if(maxm != i){
        heap.t[maxm]^=heap.t[i]^=heap.t[maxm]^=heap.t[i];
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

int GetMax(kopiec heap){
    if(hsize(heap)==0) return -1;
    int result = heap.t[1];

    heap.t[1] = heap.t[hsize(heap)];
    hsize(heap)--;
    Heapify(heap, 1);
    return result;
}

void Put(kopiec heap, int a){
    if(hsize(heap)==heap.N) return;
    hsize(heap)++;
    heap.t[hsize(heap)] = a;

    int i = hsize(heap);
    while(i>1 && heap.t[i]>heap.t[parent(i)]){
        heap.t[i]^=heap.t[parent(i)]^=heap.t[i]^=heap.t[parent(i)];
        i = parent(i);
    }
}

kolejka BuildKol(int t[], int s){
    kolejka que(t, s);
    for(int i=s/2; i>0; i--){
        Heapify(que.kol, i);
    }
    return que;
}
void GetMax(kolejka que){GetMax(que.kol);}
void Put(kolejka que, int a){Put(que.kol, a);}

int main(){
    int t[] = {1,2,3,4,5};
    kopiec heap = BuildHeap(t, 5);
    Wypisz(heap);
    GetMax(heap);
    Wypisz(heap);
    Put(heap, 3);
    Wypisz(heap);
    cout << "\n\n";
    kolejka que = BuildKol(t, 5);
    Wypisz(que);
    GetMax(que);
    Wypisz(que);
    Put(que, 3);
    Wypisz(que);
}
