#include <iostream>
using namespace std;

struct edge{
    int a;
    int b;
};

struct node{
    int value;
    node* next;
};

struct Graph{
    ///directed graph
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
        m->next = vertices[t[i].a];
        vertices[t[i].a] = m;
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

enum colors{white, gray, black};

void DFS_Visit(Graph* gr, colors color[], int v){
    color[v] = gray;
    node* tmp = gr->vertices[v];
    cout << v << " ";

    while(tmp != nullptr){
        if(color[tmp->value] == white){
            DFS_Visit(gr, color, tmp->value);
        }
        tmp = tmp->next;
    }
    color[v] = black;
}

void DFS(Graph* gr){
    colors* color = new colors[gr->V];
    for(int i=0; i<gr->V; i++){
        color[i] = white;
    }
    for(int i=0; i<gr->V; i++){
        if(color[i] == white){
            DFS_Visit(gr, color, i);
        }
    }
    cout << endl;
    delete[] color;
}

int main(){
    Graph* a = nullptr;
    edge t[]={
        {0, 1},
        {0, 4},
        {1, 2},
        {1, 3},
        {2, 3},
        {2, 5},
        {3, 4},
        {4, 5}
    };
    Init(a, 6, 8, t);
    DFS(a);

    delete a;
}
