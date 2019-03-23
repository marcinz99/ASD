#include <iostream>
using namespace std;

struct node{
    int value = 0;
    node* next = nullptr;
};

void Wypisz(node* first){
    cout << "Elementy listy: ";
    while(first != nullptr){
        cout << first->value << ", ";
        first = first->next;
    }cout << "\n";
}

void IniTab(node* &first, int t[], int s){
    if(first != nullptr || s<=0) return;

    node* d = new node;
    first = d;
    d->value = t[0];

    for(int i=1; i<s; i++){
        d->next = new node;
        d = d->next;
        d->value = t[i];
    }
}

node* Split(node* first){
    int x = first->value;
    node* second = first;

    while((first=first->next) != nullptr && (first=first->next) != nullptr){
        second = second->next;
    }
    first = second;
    second = second->next;
    first->next = nullptr;
    return second;
}

void Merge(node* &p, node* &r){
    node* d = new node;
    node* h = d;

    while(p != nullptr && r != nullptr){
        d->next = new node;
        d = d->next;

        if(p->value < r->value){
            d->value = p->value;
            p = p->next;
        }
        else{
            d->value = r->value;
            r = r->next;
        }
    }
    if(p != nullptr) d->next = p;
    if(r != nullptr) d->next = r;
    p = h->next;
    delete h;
}

void MergeSort(node* &first){
    if(first == nullptr || first->next == nullptr) return;
    node* second = Split(first);

    MergeSort(first);
    MergeSort(second);
    Merge(first, second);
}

int main(){
    int t[] = {6,2,3,4,5,1,7,8};
    node* a = nullptr;
    IniTab(a, t, 8);
    MergeSort(a);
    Wypisz(a);
}
