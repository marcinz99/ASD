#include <iostream>
using namespace std;

struct node{
    int value = 0;
    node* next = nullptr;
};

void Wypisz(int t[], int s){
    cout << "Elementy: ";
    for(int i=0; i<s; i++){
        cout << t[i] << ", ";
    }cout << "\n";
}

void Wypisz(node* first){
    cout << "Elementy: ";
    while(first != nullptr){
        cout << first->value << ", ";
        first = first->next;
    }cout << "\n";
}

void IniTab(node* &first, int t[], int s){
    if(first != nullptr || s==0) return;
    node* d = new node;
    d->value = t[0];
    first = d;
    for(int i=1; i<s; i++){
        d->next = new node;
        d = d->next;
        d->value = t[i];
    }
}

void Push(node* &first, int a){
    node* d = new node;
    d->value = a;
    d->next = first;
    first = d;
}

int Pop(node* &first){
    if(first == nullptr) return -1;
    int result = first->value;
    node* d = first->next;
    delete first;
    first = d;
    return result;
}

void SortPush(node* &first, int val){
    node* d = new node;
    d->value = val;

    if(first == nullptr){
        first = d;
        return;
    }
    if(val < (first->value)){
        d->next = first;
        first = d;
        return;
    }

    node* h = first;
    while(h->next != nullptr && h->next->value < val){
        h = h->next;
    }
    d->next = h->next;
    h->next = d;
}

void Insertsort(node* &first){
    node* d = nullptr;
    while(first != nullptr){
        SortPush(d, Pop(first));
    }
    first = d;
}

node* Linkin(node** buckets, int k){
    node* first = nullptr;
    node* d;

    for(int i=0; i<k; i++){
        if(buckets[i] == nullptr) continue;

        if(first == nullptr){
            d = buckets[i];
            first = d;
        }
        else{
            while(d->next != nullptr) d = d->next;
            d->next = buckets[i];
        }
    }
    return first;
}

void Bucketsort(int t[], int s){
    int k = 10;
    node** buckets = new node*[k];
    for(int i=0; i<k; i++) buckets[i] = nullptr;
    int maxm = t[0];
    int minm = t[0];
    for(int i=0; i<s; i++){
        if(t[i]>maxm) maxm = t[i];
        if(t[i]<minm) minm = t[i];
    }
    if(maxm==minm) return;
    int n = maxm-minm+1;

    for(int i=0; i<s; i++){
        SortPush(buckets[k*(t[i]-minm)/n], t[i]);
    }

    node* sorted = Linkin(buckets, k);
    delete[] buckets;

    for(int i=0; i<s; i++){
        t[i] = Pop(sorted);
    }
}

int main(){
    int t[] = {3,3,8,4,5,15,12,13,10,9,17,25};
    Bucketsort(t, 12);
    Wypisz(t, 12);
}
