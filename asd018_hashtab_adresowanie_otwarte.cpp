#include <iostream>
using namespace std;

struct dataset{
    string key;
    int value;
};

struct cell{
    string key;
    int value;
    bool occupied = false;
    bool deleted = false;
};

int Multiplier(int n){
    auto nwd = [](int a, int b)mutable->int{
        while(b != 0){
            a %= b;
            if(b>a) a^=b^=a^=b;
        }return a;
    };
    int i = 2;
    while(nwd(i,n)!=1) i++;
    return i;
}

struct hashtab{
    cell* data;
    const int N;
    const int C;
    int q;

    hashtab():N(0),C(0) {};
    hashtab(int n):N(n),C(Multiplier(n)) {
        data = new cell[n];
        q = 0;
    };
    ~hashtab(){
        delete[] data;
    }
};

void Wypisz(hashtab* ht){
    if(ht == nullptr){
        cout << "> Nie odnaleziono tablicy z haszowaniem.\n\n";
        return;
    }
    cout << "> Analiza tablicy z haszowaniem:\n";
    cout << "  # Rozmiar calkowity:    " << ht->N << "\n";
    cout << "  # Liczba elementow:     " << ht->q << "\n";
    cout << "  # Iterator haszujacy:   " << ht->C << "\n";
    for(int i=0; i<ht->N; i++){
        if(ht->data[i].occupied == true){
            cout << " @_" << i << " [";
            cout << ht->data[i].key << ", ";
            cout << ht->data[i].value << "]\n";
        }
    }cout << "\n";
}

int Hashing(const string &key, const int &mod){
    int shortcut = 1000;
    for(int i=0; i<key.size(); i++){
        shortcut += 11*key[i];
        shortcut %= mod;
    }
    return shortcut;
}

void Init(hashtab* &ht, int n){
    if(ht != nullptr) delete ht;
    ht = new hashtab(n);
}

void Resize(hashtab*&);

void Insert(hashtab* &ht, const string &ke, int val){
    if(ht == nullptr) return;
    if((float)ht->q/ht->N >= 0.8) Resize(ht);

    int shortcut = Hashing(ke, ht->N);
    while(ht->data[shortcut].occupied){
        shortcut += ht->C;
        shortcut %= ht->N;
    }
    ht->data[shortcut].key = ke;
    ht->data[shortcut].value = val;
    ht->data[shortcut].occupied = true;
    ht->data[shortcut].deleted = false;
    ht->q++;
}

void Resize(hashtab* &ht){
    hashtab* d = new hashtab(2*ht->N);
    for(int i=0; i<ht->N; i++){
        if(ht->data[i].occupied){
            Insert(d, ht->data[i].key, ht->data[i].value);
        }
    }
    delete ht;
    ht = d;
}

void IniTab(hashtab* &ht, dataset data[], int n){
    if(ht == nullptr) ht = new hashtab(2*n);
    for(int i=0; i<n; i++){
        Insert(ht, data[i].key, data[i].value);
    }
}

int Find(hashtab* ht, const string &ke){
    if(ht == nullptr) return -1;
    int shortcut = Hashing(ke, ht->N);
    while(ht->data[shortcut].occupied || ht->data[shortcut].deleted){
        if(ht->data[shortcut].key==ke && ht->data[shortcut].occupied){
            return ht->data[shortcut].value;
        }
        shortcut += ht->C;
        shortcut %= ht->N;
    }
    return -1;
}

void Delete(hashtab* ht, const string &ke){
    if(ht == nullptr) return;
    int shortcut = Hashing(ke, ht->N);
    while(ht->data[shortcut].occupied || ht->data[shortcut].deleted){
        if(ht->data[shortcut].key==ke && ht->data[shortcut].occupied){
            ht->data[shortcut].occupied = false;
            ht->data[shortcut].deleted = true;
            ht->q--;
            return;
        }
        shortcut += ht->C;
        shortcut %= ht->N;
    }
    return;
}

int main(){
    hashtab* a = nullptr;
    dataset data[] = {{"ashuyghdf", 5},{"asuiujkhf", 5},{"ttuygvtff", 8},{"ttuyguuhuhf", 8},{"xzxSssf", 15},{"tyfytftyf", 8}};
    IniTab(a, data, 6);
    Wypisz(a);
    cout << "Find xzxSssf: " << Find(a, "xzxSssf") << "\n";
    cout << "Delete xzxSssf\n";
    Delete(a, "xzxSssf");
    Wypisz(a);
    delete a;
}
