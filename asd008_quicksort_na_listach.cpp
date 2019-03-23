#include <iostream>
using namespace std;

struct node{
    int value = 0;
    node* next = nullptr;
};

void Wypisz(node* first){
    cout << "Elementy: ";
    while(first != nullptr){
        cout << first->value << ", ";
        first = first->next;
    }cout << "\n";
}

void IniTab(node* &first, int t[], int s){
    if(first != nullptr) return;
    node* d = new node;
    first = d;
    d->value = t[0];
    for(int i=1; i<s; i++){
        d->next = new node;
        d = d->next;
        d->value = t[i];
    }
}

void Linkin(node* &p, node* &q, node* &r){
    q->next = r;
    if(p != nullptr){
        node* d = p;
        while(d->next != nullptr){
            d = d->next;
        }
        d->next = q;
        q = p;
    }
    p = nullptr;
    r = nullptr;
}

void Partition(node* &first, node* &p, node* &r){
    node* p_start = nullptr;
    node* r_start = nullptr;

    while(first->next != nullptr){
        if(first->next->value < (first->value)){
            if(p == nullptr){
                p = first->next;
                p->value = first->next->value;
                p_start = p;
            }
            else{
                p->next = first->next;
                p = p->next;
                p->value = first->next->value;
            }
        }
        else{
            if(r == nullptr){
                r = first->next;
                r->value = first->next->value;
                r_start = r;
            }
            else{
                r->next = first->next;
                r = r->next;
                r->value = first->next->value;
            }
        }
        first->next = first->next->next;
    }
    if(p != nullptr){
        p->next = nullptr;
        p = p_start;
    }
    if(r != nullptr){
        r->next = nullptr;
        r = r_start;
    }
}

void Quicksort(node* &first){
    if(first == nullptr || first->next == nullptr) return;
    node* p = nullptr;
    node* r = nullptr;

    Partition(first, p, r);
    Quicksort(p);
    Quicksort(r);
    Linkin(p,first,r);
}

int main(){
    int t[] = {7,6,4,1,3,3,2,10,9,8,5,5};
    node* a = nullptr;
    IniTab(a, t, 12);
    Quicksort(a);
    Wypisz(a);
}
