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
    d->value = t[0];
    first = d;

    for(int i=1; i<s; i++){
        d->next = new node;
        d = d->next;
        d->value = t[i];
    }
}

node* Split(node* first){
    node* second = first;
    while((first=first->next)!=nullptr && (first=first->next)!=nullptr){
        second = second->next;
    }
    node* d = second;
    second = second->next;
    d->next = nullptr;
    return second;
}

void Merge(node* &first, node* &second){
    node* d = new node;
    node* h = d;

    while(first!=nullptr && second!=nullptr){
        if(first->value <= second->value){
            d->next = first;
            first = first->next;
        }
        else{
            d->next = second;
            second = second->next;
        }
        d = d->next;
    }
    if(first != nullptr) d->next = first;
    if(second != nullptr) d->next = second;

    first = h->next;
    delete h;
}

void Mergesort(node* &first){
    if(first == nullptr || first->next == nullptr) return;
    node* second = Split(first);

    Mergesort(first);
    Mergesort(second);
    Merge(first, second);
}

int main(){
    int t[] = {5,8,3,5,5,10,9,8,7,7};
    node* a = nullptr;
    IniTab(a, t, 10);
    Mergesort(a);
    Wypisz(a);
}
