#include <iostream>
using namespace std;

struct node{
    int value = 0;
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    int left_subtree = 0;
    int right_subtree = 0;
};

struct tree{
    node* root = nullptr;

    ~tree(){
        node* tmp;
        node* x;
        while(true){
            x = root;
            while(true){
                if(x->left != nullptr){
                    x = x->left;
                    continue;
                }
                if(x->right != nullptr){
                    x = x->right;
                    continue;
                }
                break;
            }
            if(x->parent == nullptr){
                delete x;
                break;
            }
            if(x->parent->left == x){
                x->parent->left = nullptr;
                delete x;
            }
            if(x->parent->right == x){
                x->parent->right = nullptr;
                delete x;
            }
        }
    }
};

enum order{PRE, IN, POST};

void WypiszPre(node* first){
    if(first == nullptr) return;
    cout << first->value << ", ";
    WypiszPre(first->left);
    WypiszPre(first->right);
}

void WypiszIn(node* first){
    if(first == nullptr) return;
    WypiszIn(first->left);
    cout << first->value << ", ";
    WypiszIn(first->right);
}

void WypiszPost(node* first){
    if(first == nullptr) return;
    WypiszPost(first->left);
    WypiszPost(first->right);
    cout << first->value << ", ";
}

void Wypisz(tree* tr, order m){
    if(tr == nullptr || tr->root == nullptr){
        cout << "Drzewo nie istnieje.\n\n";
        return;
    }
    cout << "Elementy";
    switch(m){
        case PRE: cout << " (pre-order): "; WypiszPre(tr->root); break;
        case IN: cout << " (in-order): "; WypiszIn(tr->root); break;
        case POST: cout << " (post-order): "; WypiszPost(tr->root); break;
        default: cout << ": error"; break;
    }cout << "\n\n";
}

void Insert(tree* &tr, int val){
    if(tr == nullptr) tr = new tree;
    node* d = nullptr;
    node* x = tr->root;

    while(x != nullptr){
        d = x;
        if(x->value < val) x = x->right;
        else x = x->left;
    }
    node* p = new node;
    p->value = val;
    if(d == nullptr){
        tr->root = p;
        return;
    }
    if(d->value < val){
        d->right = p;
        d->right->parent = d;
        d = d->right;
        while(d->parent != nullptr){
            if(d->parent->right == d){
                d->parent->right_subtree += 1;
            }
            if(d->parent->left == d){
                d->parent->left_subtree += 1;
            }
            d = d->parent;
        }
    }
    else{
        d->left = p;
        d->left->parent = d;
        d = d->left;
        while(d->parent != nullptr){
            if(d->parent->right == d){
                d->parent->right_subtree += 1;
            }
            if(d->parent->left == d){
                d->parent->left_subtree += 1;
            }
            d = d->parent;
        }
    }
}

void IniTab(tree* &tr, int t[], int s){
    for(int i=0; i<s; i++){
        Insert(tr, t[i]);
    }
}

void FindPath(tree* tr, int val){
    if(tr == nullptr || tr->root == nullptr) return;
    node* x = tr->root;
    string path = "root";
    while(x != nullptr){
        if(x->value < val){
            x = x->right;
            path += " > right";
        }
        else if(x->value > val){
            x = x->left;
            path += " > left";
        }
        else{
            cout << val << ": " << path << "\n\n";
            return;
        }
    }
    cout << "Nie odnaleziono sciezki.\n\n";
}

node* Find(tree* tr, int val){
    node* d = tr->root;
    while(d != nullptr){
        if(val > d->value) d = d->right;
        else if(val < d->value) d = d->left;
        else return d;
    }
    return nullptr;
}

node* Max(node* root){
    if(root != nullptr){
        while(root->right != nullptr)
            root = root->right;
    }
    return root;
}

node* Min(node* root){
    if(root != nullptr){
        while(root->left != nullptr)
            root = root->left;
    }
    return root;
}

node* Predecessor(tree* tr, int val){
    node* d = Find(tr, val);
    if(d == nullptr) return nullptr;

    if(d->left != nullptr){
        return Max(d->left);
    }
    while(d->parent != nullptr && d->parent->right != d){
        d = d->parent;
    }
    d = d->parent;
    return d;
}

node* Successor(tree* tr, int val){
    node* d = Find(tr, val);
    if(d == nullptr) return nullptr;

    if(d->right != nullptr){
        return Min(d->left);
    }
    while(d->parent != nullptr && d->parent->left != d){
        d = d->parent;
    }
    d = d->parent;
    return d;
}

node* FindIth(node* first, const int &i){
    static int j;
    if(first == nullptr || j>=i) return nullptr;

    node* d = FindIth(first->left, i);
    if(d != nullptr) return d;

    if(++j == i) return first;

    d = FindIth(first->right, i);
    if(d != nullptr) return d;
}

int WhichTh(node* first, const int &val){
    static int j;
    if(first == nullptr) return -1;

    int d = WhichTh(first->left, val);
    if(d != -1) return d;

    j++;
    if(first->value == val) return j;

    d = WhichTh(first->right, val);
    if(d != -1) return d;

    if(first->value > val) return -1;
    return -1;
}

node* FindIth(tree* tr, int i){
    node* d = tr->root;
    node* x;

    while(d != nullptr){
        if(d->left_subtree+1 == i) return d;
        if(d->left_subtree+1 > i){
            d = d->left;
            continue;
        }
        if(d->left_subtree+1 < i){
            i -= d->left_subtree+1;
            d = d->right;
        }
    }
    return nullptr;
}

int WhichTh(tree* tr, int val){
    node* d = Find(tr, val);
    if(d == nullptr) return 0;
    int licz = d->left_subtree + 1;

    while(d->parent != nullptr){
        if(d->parent->right == d){
            licz += d->parent->left_subtree+1;
        }
        d = d->parent;
    }
    return licz;
}

//nie dziala
void Delete(tree* &tr, int val){
    node* to_del = Find(tr, val);
    if(to_del == nullptr) return;

    node* d = to_del;
    node* x;
    if(to_del->left != nullptr && to_del->right != nullptr){
        d = Successor(tr, to_del->value);
    }
    if(d->left != nullptr) x = d->left;
    else x = d->right;

    if(x != nullptr) x->parent = d->parent;

    if(d->parent == nullptr) tr->root = x;
    else if(d->parent->left == d) d->parent->left = x;
    else d->parent->right = x;

    if(to_del != d) to_del->value = d->value;

    delete d;
}

//nie dziala
node* Remove(tree* &tr, int val, node* to_del = nullptr){
    if(to_del == nullptr) to_del = Find(tr, val);
    if(to_del == nullptr) return nullptr;
    node* d = to_del->parent;
    node* x;

    if(to_del->left != nullptr && to_del->right != nullptr){
        x = Remove(tr, 0, Successor(tr, to_del->value));
        x->left = to_del->left;
        if(x->left != nullptr) x->left->parent = x;
        x->right = to_del->right;
        if(x->right != nullptr) x->right->parent = x;
    }
    else{
        if(to_del->left != nullptr) x = to_del->left;
        else x = to_del->right;
    }
    if(x != nullptr) x->parent = d;

    if(d == nullptr) tr->root = x;
    else if(d->left == to_del) d->left = x;
    else d->right = x;

    return to_del;
}

int main(){
    tree* a = nullptr;
    int t[] = {8, 5, 2, 6, 7, 1, 9, 4, 10, 12};
    IniTab(a, t, 10);
    Wypisz(a, IN);
    FindPath(a, 12);
    cout << WhichTh(a, 7);

    delete a;
}
