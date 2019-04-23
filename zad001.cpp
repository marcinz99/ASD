#include <iostream>
using namespace std;

const int N = 4;

struct uf{
    int** t;

    uf(int);
    ~uf();
};

uf::uf(int n){
    t = new int*[n];
    for(int i=0; i<n; i++){
        t[i] = new int[n];
        for(int j=0; j<n; j++){
            t[i][j] = -1;
        }
    }
}

uf::~uf(){
    for(int i=0; i<N; i++){
        delete[] t[i];
    }
    delete[] t;
}

int adr(int a, int b){
    return a*N+b;
}

int abs(uf* a, int m){
    return -(a->t[m/N][m%N]+1);
}

int Find(uf* a, int m){
    int x;
    int y = m;
    while(true){
        x = y;
        y = a->t[x/N][x%N];
        if(y < 0) return x;
    }
}

void Union(uf* a, int m, int n){
    int parent = Find(a, n);
    a->t[m/N][m%N] = parent;
    a->t[parent/N][parent%N]--;
}

int Moves(bool tab[N][N], int x, int y){
    uf* a = nullptr;
    a = new uf(N);
    int K = N*N;

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(!tab[i][j]) a->t[i][j] = K;
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(a->t[i][j] == K) continue;
            if(i>0 && a->t[i-1][j] != K)
                if(Find(a, adr(i, j))!=Find(a, adr(i-1, j))){
                    Union(a, adr(i, j), adr(i-1, j));
            }
            if(j>0 && a->t[i][j-1] != K)
               if(Find(a, adr(i, j))!=Find(a, adr(i, j-1))){
                    Union(a, adr(i, j), adr(i, j-1));
            }
        }
    }
    int result;
    if(a->t[x][y] == K) result = -1;
    else result = abs(a, Find(a, x*N+y));
    delete a;

    return result;
}

int main(){
    bool t[4][4]={{1,0,1,1},
                  {1,0,1,1},
                  {1,0,1,1},
                  {1,0,1,0}
    };
    cout << Moves(t, 3, 2);
}
