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

void Linkin(node* &p, node* &first, node* &r){
    first->next = r;
    if(p != nullptr){
        node* d = p;
        while(d->next != nullptr) d = d->next;
        d->next = first;
        first = p;
    }
    p = r = nullptr;
}

void Partition(node* &p, node* &first, node* &r){
    node* p_start = nullptr;
    node* r_start = nullptr;

    while(first->next != nullptr){
        if(first->next->value <= first->value){
            if(p_start == nullptr) p_start = p = first->next;
            else{
                p->next = first->next;
                p = p->next;
            }
        }
        else{
            if(r_start == nullptr) r_start = r = first->next;
            else{
                r->next = first->next;
                r = r->next;
            }
        }
        first->next = first->next->next;
    }
    if(p != nullptr) p->next = nullptr;
    if(r != nullptr) r->next = nullptr;

    p = p_start;
    r = r_start;
}

void Quicksort(node* &first){
    if(first == nullptr || first->next == nullptr) return;
    node* p = nullptr;
    node* r = nullptr;
    
    Partition(p, first, r);
    Quicksort(p);
    Quicksort(r);
    Linkin(p, first, r);
}

int main(){
    int t[] = {4,5,4,3,1,9,8,8,7};
    node* a = nullptr;
    IniTab(a, t, 9);
    Wypisz(a);
    Quicksort(a);
    Wypisz(a);
}
