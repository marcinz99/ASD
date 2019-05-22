#include <iostream>
#define hsize(n) n->t[0].a
using namespace std;

struct edge{
    int a;
    int b;
    int cost;
};

struct kopiec{
    edge* t;
    const int N;

    kopiec(int s):N(s){
        t = new edge[s+1];
        t[0].a = 0;
    }
    kopiec(edge[], int);
    void Del(){delete[] t;}
};

kopiec::kopiec(edge e[], int s): N(s) {
    t = new edge[s+1];
    t[0].a = s;
    for(int i=0; i<s; i++){
        t[i+1].a = e[i].a;
        t[i+1].b = e[i].b;
        t[i+1].cost = e[i].cost;
    }
}
int parent(int i){return i/2;}
int left(int i){return 2*i;}
int right(int i){return 2*i+1;}

void Heapify(kopiec* &heap, int i){
    if(i<=0 || i>hsize(heap)) return;
    int minm = i;
    int p = left(i);
    int r = right(i);

    if(p<=hsize(heap) && heap->t[p].cost < heap->t[minm].cost) minm = p;
    if(r<=hsize(heap) && heap->t[r].cost < heap->t[minm].cost) minm = r;
    if(minm != i){
        heap->t[minm].a^=heap->t[i].a^=heap->t[minm].a^=heap->t[i].a;
        heap->t[minm].b^=heap->t[i].b^=heap->t[minm].b^=heap->t[i].b;
        heap->t[minm].cost^=heap->t[i].cost^=heap->t[minm].cost^=heap->t[i].cost;
        Heapify(heap, minm);
    }
}

bool IsEmpty(kopiec* &heap){
    if(hsize(heap)!=0) return false;
    return true;
}

void BuildHeap(kopiec* &heap, edge t[], int s){
    heap = nullptr;
    heap = new kopiec(t, s);
    for(int i=s/2; i>0; i--){
        Heapify(heap, i);
    }
}

edge GetMin(kopiec* &heap){
    if(hsize(heap)==0) return {-1,-1,0};
    edge result = heap->t[1];
    heap->t[1] = heap->t[hsize(heap)];
    hsize(heap)--;
    Heapify(heap, 1);
    return result;
}

void Insert(kopiec* &heap, edge e){
    if(hsize(heap)==heap->N) return;

    hsize(heap)++;
    heap->t[hsize(heap)] = e;
    for(int i=hsize(heap); i>1; i=parent(i)){
        if(heap->t[i].cost < heap->t[parent(i)].cost){
            heap->t[parent(i)].a^=heap->t[i].a^=heap->t[parent(i)].a^=heap->t[i].a;
            heap->t[parent(i)].b^=heap->t[i].b^=heap->t[parent(i)].b^=heap->t[i].b;
            heap->t[parent(i)].cost^=heap->t[i].cost^=heap->t[parent(i)].cost^=heap->t[i].cost;
        }
    }
}

struct kolejka{
    kopiec* kol = nullptr;
    kolejka(int s){
        kol = new kopiec(s);
    }
    void Del(){kol->Del(), delete kol;}
};
bool IsEmpty(kolejka que){return IsEmpty(que.kol);}
void BuildKol(kolejka &que, edge t[], int s){BuildHeap(que.kol, t, s);}
edge GetMin(kolejka &que){return GetMin(que.kol);}
void Insert(kolejka &que, edge a){Insert(que.kol, a);}


struct node{
    int value;
    int trav_cost;
    node* next;
};

struct Graph{
    ///non-directed graph
    node** vertices;
    const int V;
    const int E;

    Graph(int, int, edge[]);
    ~Graph();
};

Graph::Graph(int v, int e, edge t[]):V(v),E(e){
    vertices = new node*[V];
    for(int i=0; i<V; i++) vertices[i] = nullptr;

    for(int i=0; i<e; i++){
        node* m = new node;
        m->value = t[i].b;
        m->trav_cost = t[i].cost;
        m->next = vertices[t[i].a];
        vertices[t[i].a] = m;

        node* n = new node;
        n->value = t[i].a;
        n->trav_cost = t[i].cost;
        n->next = vertices[t[i].b];
        vertices[t[i].b] = n;
    }
}

void Init(Graph* &gr, int V, int E, edge t[]){
    if(gr != nullptr) return;
    gr = new Graph(V, E, t);
}

Graph::~Graph(){
    node* tmp;
    for(int i=0; i<V;){
        tmp = vertices[i];
        if(tmp == nullptr) i++;
        else{
            tmp = vertices[i];
            vertices[i] = vertices[i]->next;
            delete tmp;
        }
    }
    delete[] vertices;
}

void Wypisz(kolejka Q){
    cout << "kopiec:\n";
    for(int i=1; i<=Q.kol->t[0].a; i++){
        cout << Q.kol->t[i].a << " " << Q.kol->t[i].b << " " << Q.kol->t[i].cost << endl;
    }cout << "end\n";
}

enum colors{white, gray, black};

void Prim(Graph* gr, int start=0){
    ///zainicjuj tablice kolorow
    colors* color = new colors[gr->V];
    for(int i=0; i<gr->V; i++){
        color[i] = white;
    }
    ///zainicjuj kolejke priorytetowa
    kolejka Q(gr->E);
    node* tmp;
    ///oznacz aktualny wierzcholek jako przetworzony
    color[start] = black;
    ///wrzuc do kolejki sciezki do sasiadow aktualnego wierzcholka
    ///oznaczaj wierzcholki jako odwiedzone
    tmp = gr->vertices[start];
    while(tmp != nullptr){
        if(color[tmp->value] == white){
            color[tmp->value] = gray;
            Insert(Q, {start, tmp->value, tmp->trav_cost});
        }
        tmp = tmp->next;
    }

    ///zmienne pomocnicze
    int koszt_na_drzewie_rozpinajacym = 0;
    int najkrotszy_z_pozostalych = -((1<<31)+1); //max_int jak cos
    edge x;

    ///dopoki mozna pobrac elementy z kolejki wykonuj co nastepuje
    while(!IsEmpty(Q)){
        //Wypisz(Q); //debug line
        x = GetMin(Q);
        ///jesli pobrany wierzcholek nie domyka cyklu to jest ok
        if(color[x.b] != black){
            ///oznacz jako przetworzony
            color[x.b] = black;
            koszt_na_drzewie_rozpinajacym += x.cost;
            cout << "$ " << x.a << " " << x.b << " " << x.cost << endl;
            ///przejdz po sasiadach nie domykajacych cyklu
            tmp = gr->vertices[x.b];
            while(tmp != nullptr){
                if(color[tmp->value] != black){
                    color[tmp->value] = gray;
                    Insert(Q, {x.b, tmp->value, tmp->trav_cost});
                }
                tmp = tmp->next;
            }
        }
        ///w przeciwnym wypadku sciezka nie moze nalezec do mst
        else{
            if(x.cost < najkrotszy_z_pozostalych){
                najkrotszy_z_pozostalych = x.cost;
            }
        }
    }
    cout << "Koszt na drzewie: " << koszt_na_drzewie_rozpinajacym << endl;
    cout << "Najkrotszy pozostaly: " << najkrotszy_z_pozostalych << endl;
    cout << "Dolna granica (suma): " << najkrotszy_z_pozostalych+koszt_na_drzewie_rozpinajacym << endl;
    ///posprzataj po sobie
    Q.Del();
    delete[] color;
}

int main(){
    Graph* a = nullptr;
    edge t[]={
        {0, 1, 2},
        {0, 4, 4},
        {1, 2, 5},
        {1, 3, 7},
        {2, 3, 3},
        {2, 5, 1},
        {3, 4, 3},
        {4, 5, 6}
    };
    Init(a, 6, 8, t);
    Prim(a);
    delete a;
}
