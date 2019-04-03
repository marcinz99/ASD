#include <iostream>
using namespace std;

struct node{
    int value = 0;
    int q = 1;
    node* next = nullptr;
};

struct hashtab{
    node** first;
    const int N;

    hashtab():N(0) {};
    hashtab(int n):N(n){
        first = new node*[n];
        for(int i=0; i<n; i++){
            first[i] = nullptr;
        }
    };
    ~hashtab(){
        node* tmp;
        for(int i=0; i<N;){
            if(first[i] != nullptr){
                tmp = first[i];
                first[i] = first[i]->next;
                delete tmp;
            }
            else i++;
        }
        delete[] first;
    }
};

int Hashing(int a, int mod){
    return a%mod;
}

void Add(hashtab* &ht, int val){
    int shortcut = Hashing(val, ht->N);
    node* d = new node;
    d->value = val;
    d->next = ht->first[shortcut];
    ht->first[shortcut] = d;
}

node* FindCell(hashtab* &ht, int val){
    int shortcut = Hashing(val, ht->N);
    node* d = ht->first[shortcut];

    while(d != nullptr){
        if(d->value == val) return d;
        d = d->next;
    }
    return nullptr;
}

int LiczbaSum(int t[], int n, int x){
    int licz = 0;
    node* tmp;
    hashtab* ht = new hashtab(n);

    for(int i=0; i<n; i++){
        if((tmp = FindCell(ht, x-t[i])) != nullptr){
            licz += tmp->q;
        }
        if((tmp = FindCell(ht, t[i])) != nullptr){
            tmp->q++;
        }
        else Add(ht, t[i]);
    }
    delete ht;
    return licz;
}

int main(){
    int t[] = {1,2,3,1,5,6,7,8,7};
    cout << "Liczba par o sumie x: " << LiczbaSum(t, 9, 8) << "\n";
}
