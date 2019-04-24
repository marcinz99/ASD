#include <iostream>
using namespace std;

const int N = 3;

struct node{
    int n;
    int key[N];
    node** child[N+1];
    bool leaf;
};

bool is_b_tree(node* p){
    if(!leaf_consistency(p)) return false;
    for(int i=0; i<=p->n; i++){
        if(!is_b_tree(p->child[i])) return false;
    }
    return true;
}

bool leaf_consistency(node* p){
    bool p = false; //leaf
    bool q = false; //not leaf
    for(int i=0; i<=p->n; i++){
        if(p->child[i] == nullptr) continue;
        if(p->child[i]->leaf) p = true;
        if(p->child[i]->leaf) q = true;
    }
    if(p && q) return false;
    return true;
}

void inOrderTrav(node* root, int n, int &h){
    if(root->leaf){
        ¯\_(ツ)_/¯
    }

    inOrderTrav(root->child[0]);
    for(int i=0; i<=n; i++){
        process(key[i]);
        inOrderTrav(root->child[0]);
    }
}


int main(){

}
