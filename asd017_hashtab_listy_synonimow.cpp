#include <iostream>
using namespace std;

struct dataset{
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
        for(int i=0; i<N; i++){
            tmp = first[i];
            if(first[i] != nullptr){
                first[i] = first[i]->next;
            }
            while(tmp != nullptr){
                delete tmp;
                tmp = first[i];
                if(first[i] != nullptr){
                    first[i] = first[i]->next;
                }
            }
        }delete[] first;
    };
};

void Wypisz(hashtab* ht){
    if(ht == nullptr){
        cout << "Nie znaleziono tablicy z haszowaniem.\n\n";
        return;
    }
    node* tmp;
    cout << "> Analiza tablicy z hashowaniem:\n";
    for(int i=0; i<ht->N; i++){
        tmp = ht->first[i];
        cout << "  > Indeks " << i << ": ";
        while(tmp != nullptr){
            cout << "[" << tmp->key << ",";
            cout << tmp->value << "], ";
            tmp = tmp->next;
        }cout << "\n";
    }cout << "\n";
}

int Hashing(const string &key, const int &mod){
    int shortcut = 0;
    for(int i=0; i<key.size(); i++){
        shortcut += 11*key[i];
        shortcut %= mod;
    }
    return shortcut;
}

void Init(hashtab* &ht, int n){
    ht = new hashtab(n);
}

void Insert(hashtab* ht, const string &ke, int val){
    if(ht == nullptr) return;
    int shortcut = Hashing(ke, ht->N);
    node* d = new node;
    d->key = ke;
    d->value = val;
    d->next = ht->first[shortcut];
    ht->first[shortcut] = d;
}

void InsertTab(hashtab* &ht, dataset* data, int n){
    if(ht == nullptr) Init(ht, n);
    for(int i=0; i<n; i++){
        Insert(ht, data[i].key, data[i].value);
    }
}

int Find(hashtab* ht, const string &ke){
    int shortcut = Hashing(ke, ht->N);
    node* d = ht->first[shortcut];
    while(d != nullptr){
        if(d->key == ke) return d->value;
        d = d->next;
    }return -1;
}

void Delete(hashtab* ht, const string &ke){
    int shortcut = Hashing(ke, ht->N);
    node* d = ht->first[shortcut];
    node* tmp;

    if(d != nullptr){
        if(d->key == ke){
            if(d->next == nullptr){
                delete d;
                ht->first[shortcut] = nullptr;
            }
            else{
                tmp = d;
                ht->first[shortcut] = d->next;
                delete tmp;
            }
            return;
        }
        while(d->next != nullptr){
            if(d->next->key == ke){
                tmp = d->next;
                d->next = d->next->next;
                delete tmp;
                return;
            }
            d = d->next;
        }
    }
}

int main(){
    dataset data[] = {{"asaxs",5},{"y7y7y",8},{"nuikn",11},{"bnvgf",2},{"rresz",9}};
    hashtab* a = nullptr;
    Init(a, 5);
    InsertTab(a, data, 5);
    Wypisz(a);

    cout << "Find nuikn: " << Find(a, "nuikn") << "\n\n";
    cout << "Delete asaxs:\n";
    Delete(a, "asaxs");
    Wypisz(a);

    delete a;
}
