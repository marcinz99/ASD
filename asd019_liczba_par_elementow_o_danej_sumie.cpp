#include <iostream>
using namespace std;

struct node{
    int value = 0;
    int q;
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

int HowMany(hashtab* &ht, int val){
    int shortcut = Hashing(val, ht->N);
    node* d = ht->first[shortcut];

    while(d != nullptr){
        if(d->value == val){
            d->q++;
            return d->q;
        d = d->next;
    }
    return 0;
}

void Add(hashtab* &ht, int val){
    int shortcut = Hashing(val, ht->N);
    node* d = new node;
    d->value = val;
    d->next = ht->first[shortcut];
    d->q = 0;
    ht->first[shortcut] = d;
}

int LiczbaSum(int t[], int n, int x){
    int licz = 0;
    int tmp;
    hashtab* ht = new hashtab(n);

    for(int i=0; i<n; i++){
        licz += tmp = HowMany(ht, t[i]);
        if(tmp == 0) Add(ht, x-t[i]);
    }
    delete ht;
    return licz;
}

int main(){
    int t[] = {1,2,3,4,5,6,7,8};
    cout << "Liczba par o sumie x: " << LiczbaSum(t, 8, 8) << "\n";
}
