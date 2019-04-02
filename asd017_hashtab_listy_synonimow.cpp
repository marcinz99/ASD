#include <iostream>
using namespace std;

struct data{
    string key;
    int value;
};

struct node{
    string key;
    int value;
    node* next = nullptr;
};

struct hashtab{
    node** first;
    const int N;

    hashtab():N(0) {};
    hashtab(int n):N(n) {
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
    };
};

void Wypisz(hashtab* ht){
    cout << "Analiza tablicy z haszowaniem:\n";
    if(ht == nullptr){
        cout << "> Nie odnaleziono tablicy\n\n";
        return;
    }
    cout << " () Rozmiar listy synonimow: " << ht->N << "\n";
    node* tmp;
    for(int i=0; i<ht->N; i++){
        if(ht->first[i] != nullptr){
            cout << "> Adres komorki - " << i << ": ";
            tmp = ht->first[i];
            while(tmp != nullptr){
                cout << "[" << tmp->key << ", ";
                cout << tmp->value << "], ";
                tmp = tmp->next;
            }cout << "\n";
        }
    }cout << "\n";
}

void Init(hashtab* &ht, int n){
    if(ht != nullptr) delete ht;
    ht = new hashtab(n);
}

int Hashing(const string &ke, int mod){
    int shortcut = 1000;
    for(int i=0; i<ke.size(); i++){
        shortcut += 11*ke[i];
        shortcut %= mod;
    }
    return shortcut;
}

void Insert(hashtab* ht, const string &ke, const int &val){
    if(ht == nullptr) return;
    int shortcut = Hashing(ke, ht->N);

    node* d = new node;
    d->key = ke;
    d->value = val;
    d->next = ht->first[shortcut];
    ht->first[shortcut] = d;
}

void Insert(hashtab* &ht, node* cell){
    if(ht == nullptr || cell == nullptr) return;
    int shortcut = Hashing(cell->key, ht->N);

    cell->next = ht->first[shortcut];
    ht->first[shortcut] = cell;
}

void Delete(hashtab* &ht, const string &ke){
    if(ht == nullptr) return;
    int shortcut = Hashing(ke, ht->N);

    node* d = ht->first[shortcut];
    if(d == nullptr) return;
    if(d->key == ke){
        ht->first[shortcut] = ht->first[shortcut]->next;
        delete d;
    }
    else{
        while(d->next != nullptr){
            if(d->next->key == ke){
                node* tmp = d->next;
                d->next = d->next->next;
                delete tmp;
                return;
            }
            d = d->next;
        }
    }
}

node* GetOff(hashtab* ht, const string &ke){
    if(ht == nullptr) return nullptr;
    int shortcut = Hashing(ke, ht->N);

    node* d = ht->first[shortcut];
    if(d == nullptr) return nullptr;
    if(d->key == ke){
        ht->first[shortcut] = ht->first[shortcut]->next;
        return d;
    }
    else{
        while(d->next != nullptr){
            if(d->next->key == ke){
                node* tmp = d->next;
                d->next = d->next->next;
                return tmp;
            }
            d = d->next;
        }
    }
    return nullptr;
}

node* Pop(node* &first){
    if(first == nullptr) return nullptr;
    node* tmp = first;
    first = first->next;
    return tmp;
}

int Find(hashtab* ht, const string &ke){
    if(ht == nullptr) return -1;
    int shortcut = Hashing(ke, ht->N);
    node* d = ht->first[shortcut];

    while(d != nullptr){
        if(d->key == ke) return d->value;
        d = d->next;
    }
    return -1;
}

void TabAdd(hashtab* ht, data t[], int n){
    for(int i=0; i<n; i++){
        Insert(ht, t[i].key, t[i].value);
    }
}

void Resize(hashtab* &ht, int n){
    if(ht->N == n) return;
    hashtab* d = new hashtab(n);

    for(int i=0; i<ht->N;){
        if(ht->first[i] != nullptr){
            Insert(d, Pop(ht->first[i]));
        }
        else i++;
    }
    delete ht;
    ht = d;
}

void TabDel(hashtab* ht, string t[], int n){
    for(int i=0; i<n; i++){
        Delete(ht, t[i]);
    }
}

int main(){
    data t[] = {{"cdcdc",45},{"yutyu",14},{"vxdxz",36},{"cioin",51},{"mnvbh",28}};
    hashtab* a = nullptr;
    Init(a, 8);
    TabAdd(a, t, 5);
    Wypisz(a);
    Resize(a, 5);
    Wypisz(a);
    node* z = GetOff(a, "cdcdc");
    Wypisz(a);
    Insert(a, z);
    Wypisz(a);
    string del[] = {"yutyu","mnvbh"};
    TabDel(a, del, 2);
    Wypisz(a);
}
