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

void IniTab(node* &first, int t[], int n){
    if(first != nullptr) return;
    node* d = new node;
    d->value = t[0];
    first = d;

    for(int i=1; i<n; i++){
        d->next = new node;
        d = d->next;
        d->value = t[i];
    }
}

bool NotEmpty(node* first){
    return first != nullptr;
}

void Put(node* &first, int val){
    node* d = new node;
    d->value = val;
    d->next = first;
    first = d;
}

void Put(node* &first, node* d){
    d->next = first;
    first = d;
}

int Get(node* &first){
    if(first == nullptr) return -1;
    int x = first->value;
    node* tmp = first;
    first = first->next;
    delete tmp;
    return x;
}

node* GetPtr(node* &first){
    if(first == nullptr) return nullptr;
    node* tmp = first;
    first = first->next;
    return tmp;
}

struct kolejka{
    node* stos = nullptr;
    node* stos_tmp = nullptr;
};

void Wypisz(kolejka* kol){
    Wypisz(kol->stos);
}

void Put(kolejka* &kol, int val){
    while(NotEmpty(kol->stos)){
        Put(kol->stos_tmp, GetPtr(kol->stos));
    }
    Put(kol->stos, val);
    while(NotEmpty(kol->stos_tmp)){
        Put(kol->stos, GetPtr(kol->stos_tmp));
    }
}

int Get(kolejka* &kol){
    return Get(kol->stos);
}

int main(){
    int t[] = {1,2,3,4,5,6};
    kolejka* a = new kolejka;
    IniTab(a->stos, t, 6);
    Wypisz(a->stos);
    Put(a, 7);
    Put(a, 8);
    Wypisz(a);
    cout << "Zdejmij pierwszy: " << Get(a) << "\n";
    Wypisz(a);
}
