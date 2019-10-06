#include <iostream>
#include <queue>
#include <climits>
using namespace std;

struct edge{
    int a;
    int b;
    int weight;
};

struct node{
    int id;
    int weight;
    node* next;
};

struct Graph{
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
        m->id = t[i].b;
        m->weight = t[i].weight;
        m->next = vertices[t[i].a];
        vertices[t[i].a] = m;
    }
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

void Init(Graph* &gr, int V, int E, edge t[]){
    if(gr != nullptr) return;
    gr = new Graph(V, E, t);
}

enum colors{white, gray, black};

void FordFulkerson(Graph* gr, int s=-1, int t=-1){
    ///cf - siec residualna
    int** cf = new int*[gr->V];
    if(s == -1) s = 0;
    if(t == -1) t = gr->V - 1;
    int max_flow = 0;

    ///lambda szukajaca sciezki rozszerzajacej poprzez BFS
    auto FindExtendingPath = [gr, cf, s, t](){
        node* ext = nullptr;
        int* parent = new int[gr->V];
        colors* color = new colors[gr->V];
        for(int i=0; i<gr->V; i++){
            color[i] = white;
            parent[i] = -1;
        }

        queue<pair<node*, int>> Q;
        Q.push({gr->vertices[s], s});
        color[s] = gray;

        while(!Q.empty()){
            pair<node*, int> u = Q.front();
            Q.pop();
            for(int i=0; i<gr->V; i++){
                if(cf[u.second][i]!=-1 && color[i]==white && cf[u.second][i]>0){
                    color[i] = gray;
                    parent[i] = u.second;
                    Q.push({gr->vertices[i], i});
                }
            }color[u.second] = black;
        }
        for(int p=t; p!=-1; p=parent[p]){
            node* x = new node;
            x->id = p;
            x->next = ext;
            ext = x;
        }if(ext->next == nullptr) ext = nullptr;

        delete[] color;
        delete[] parent;
        return ext;
    };

    ///inicjalizacja sieci residualnej
    /// -1 - nie nalezy do sieci
    /// weight - krawedz nalezaca do sieci pierwotnej
    /// 0 - krawedz zwrotna
    for(int i=0; i<gr->V; i++){
        cf[i] = new int[gr->V];
        for(int j=0; j<gr->V; j++) cf[i][j] = -1;
    }
    for(int i=0; i<gr->V; i++){
        node* tmp = gr->vertices[i];
        while(tmp != nullptr){
            cf[i][tmp->id] = tmp->weight;
            cf[tmp->id][i] = 0;
            tmp = tmp->next;
        }
    }

    ///wlasciwy algorytm forda-fulkersona
    while(true){
        node* path = FindExtendingPath();
        if(path == nullptr) break;
        int current_flow = INT_MAX;

        int x = -1, y = path->id;
        for(node* d=path->next; d!=nullptr; d=d->next){
            x = y;
            y = d->id;
            if(cf[x][y] < current_flow) current_flow = cf[x][y];
        }
        max_flow += current_flow;

        x = -1; y = path->id;
        for(node* d=path->next; d!=nullptr; d=d->next){
            x = y;
            y = d->id;
            cf[x][y] -= current_flow;
            cf[y][x] += current_flow;
        }
        cout << "Sciezka powiekszajaca: ";
        for(; path!=nullptr; path=path->next){
            cout << path->id << " ";
        }
        cout << "\nPrzeplyw: " << max_flow << "\n";
    }
    cout << "\nPrzeplyw maksymalny: " << max_flow << "\n\n";

    ///sprzatanko
    for(int i=0; i<gr->V; i++){
        delete[] cf[i];
    }delete[] cf;
}

int main(){
    Graph* a = nullptr;
    ///graf jak na wykladzie S-0, A-1, ..., E-5, T-6
    edge t[]={
        {0, 1, 4},
        {0, 3, 3},
        {0, 5, 3},
        {1, 2, 4},
        {1, 4, 2},
        {2, 4, 2},
        {2, 6, 5},
        {3, 2, 2},
        {3, 5, 1},
        {4, 6, 3},
        {5, 4, 2}
    };
    Init(a, 7, 11, t);
    FordFulkerson(a);

    delete a;
}
