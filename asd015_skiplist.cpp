#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct SLnode{
    int value;
    SLnode** next;
};

struct skiplist{
    SLnode* first = nullptr;
    int max_lvl = 0;
};

void Wypisz(skiplist* slist){
    cout << "Elementy: ";
    if(slist == nullptr){
        cout << "\n";
        return;
    }
    SLnode* iter = slist->first->next[0];
    while(iter != nullptr){
        cout << iter->value << ", ";
        iter = iter->next[0];
    }cout << "\n";
}

void WypiszFull(skiplist* slist){

}

int Random(){
    int result = 0;
    while(rand()&1) result++;
    return result;
}

void IniTab_LVL_0(skiplist* &slist, int t[], int s){
    if(slist != nullptr || s==0) return;
    slist = new skiplist;
    slist->max_lvl = 0;
    slist->first = new SLnode;

    slist->first->value = -1;
    slist->first->next = new SLnode*[1];
    slist->first->next[0] = nullptr;

    SLnode* d = slist->first;

    for(int i=0; i<s; i++){
        d->next[0] = new SLnode;
        d = d->next[0];
        d->value = t[i];
        d->next = new SLnode*[1];
        d->next[0] = nullptr;
    }
}

void Insert(skiplist* &slist, int val){
    if(slist == nullptr){
        slist = new skiplist;
        slist->max_lvl = 0;
        slist->first = new SLnode;

        slist->first->value = -1;
        slist->first->next = new SLnode*[1];

        slist->first->next[0] = new SLnode;
        slist->first->next[0]->value = val;
        slist->first->next[0]->next = new SLnode*[1];
        slist->first->next[0]->next[0] = nullptr;
        return;
    }
    int level = slist->max_lvl;
    SLnode* current = slist->first;

    SLnode** from = new SLnode*[level+2];
    SLnode** to = new SLnode*[level+2];

    while(true){
        if(current->next[level] != nullptr && current->next[level]->value <= val){
            current = current->next[level];
            continue;
        }
        if(level > 0){
            if(current->next[level] == nullptr || current->next[level]->value > val){
                from[level] = current;
                to[level] = current->next[level];
                level -= 1;
                current -= 1;
            }
            continue;
        }
        break;
    }

    from[0] = current;
    to[0] = current->next[0];

    int k = Random();
    if(k > slist->max_lvl){
        k = slist->max_lvl+1;
        slist->max_lvl = k;

        SLnode* new_first = new SLnode;
        new_first->next = new SLnode*[k+1];
        new_first->value = slist->first->value;

        for(int i=0; i<=k-1; i++){
            new_first->next[i] = slist->first->next[i];
        }new_first->next[k] = nullptr;

        slist->first = new_first;
        from[slist->max_lvl] = slist->first;
        to[slist->max_lvl] = nullptr;
    }

    SLnode* inserted = new SLnode;
    inserted->value = val;
    inserted->next = new SLnode*[k+1];

    for(int i=0; i<=k; i++){
        from[i]->next[i] = inserted;
        inserted->next[i] = to[i];
    }

    delete[] from;
    delete[] to;
}

int main(){
    srand(time(0));
    int t[] = {1,2,3,5,7};
    skiplist* a = nullptr;
    IniTab_LVL_0(a, t, 5);
    Wypisz(a);
    Insert(a, 8);
    Wypisz(a);
}
