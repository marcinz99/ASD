#include <iostream>
#define hsize(n) (*n).t[0]
using namespace std;

struct kopiec{
    int* t;
    const int N;
    kopiec(): N(0) {};
    kopiec(int a[], int s): N(s) {
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

void Heapify(kopiec* &heap, int i){
    if(i<=0 || i>hsize(heap)) return;
    int maxm = i;
    int p = left(i);
    int r = right(i);

    if(p<=hsize(heap) && heap->t[p]>(heap->t[maxm])) maxm = p;
    if(r<=hsize(heap) && heap->t[r]>(heap->t[maxm])) maxm = r;
    if(maxm != i){
        heap->t[maxm]^=heap->t[i]^=heap->t[maxm]^=heap->t[i];
        Heapify(heap, maxm);
    }
}

void BuildHeap(kopiec* &heap, int t[], int s){
    heap = nullptr;
    heap = new kopiec(t, s);
    for(int i=s/2; i>0; i--){
        Heapify(heap, i);
    }
}

int GetMax(kopiec* &heap){
    if(hsize(heap)==0) return -1;

    int result = heap->t[1];
    heap->t[1] = heap->t[hsize(heap)];
    hsize(heap)--;
    Heapify(heap, 1);
    return result;
}

void Insert(kopiec* &heap, int a){
    if(hsize(heap)==heap->N) return;

    hsize(heap)++;
    heap->t[hsize(heap)] = a;
    for(int i=hsize(heap); i>1; i=parent(i)){
        if(heap->t[i] > heap->t[parent(i)]){
            heap->t[parent(i)]^=heap->t[i]^=heap->t[parent(i)]^=heap->t[i];
        }
    }
}

struct kolejka{
    kopiec* kol = nullptr;
};
void Wypisz(kolejka que){Wypisz(que.kol);}
void BuildKol(kolejka &que, int t[], int s){BuildHeap(que.kol, t, s);}
int GetMax(kolejka &que){return GetMax(que.kol);}
void Insert(kolejka &que, int a){Insert(que.kol, a);}

int main(){
    int t[] = {1,2,3,4,5,6,7,8,9,10};
    kolejka que;
    BuildKol(que, t, 10);
    Wypisz(que);
    cout << "GetMax: " << GetMax(que) << "\n";
    Wypisz(que);
    int a = 8;
    cout << "Insert: " << a << "\n";
    Insert(que, a);
    Wypisz(que);
}
