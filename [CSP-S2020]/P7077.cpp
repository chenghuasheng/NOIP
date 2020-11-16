#include <cstdio>
#include <vector>
using namespace std;
//ifstream cin("P7077_2.in");
//ofstream cout("P7077_2_.out");
const long long MOD=998244353;
const int MAXN=100000;
struct Func{
    int t;
    int p,v;
    vector<int> subs;
};
int a[MAXN+1];
Func funcs[MAXN+1];
int runs[MAXN+1];
int n,m,q;
struct Node{
    int l,r;
    long long lz=1;
    long long val;
};
Node tree[MAXN*4];
void build(int i,int l,int r){
    tree[i].l=l;
    tree[i].r=r;
    if (l==r){
        tree[i].val=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(2*i,l,mid);
    build(2*i+1,mid+1,r);
}
void mult(int i,int v){
    tree[i].lz=(tree[i].lz*v)%MOD;
}
void push_down(int i){
    if (tree[i].lz>1) {
        if (tree[i].l==tree[i].r) {
            tree[i].val=(tree[i].val*tree[i].lz)%MOD;
            tree[i].lz=1;
            return ;
        }
        tree[2*i].lz=(tree[2*i].lz*tree[i].lz)%MOD;
        tree[2*i+1].lz=(tree[2*i+1].lz*tree[i].lz)%MOD;
        tree[i].lz=1;
    }
}
void update(int i,int p,int v){
    push_down(i);
    if (tree[i].l==tree[i].r){
        tree[i].val=(tree[i].val+v)%MOD;
        return;
    }
    if (p<=tree[2*i].r) update(2*i,p,v);
    else update(2*i+1,p,v);
}
long long get(int i,int p){
    push_down(i);
    if (tree[i].l==tree[i].r){
        return tree[i].val;
    }
    if (p<=tree[2*i].r) return get(2*i,p);
    else return get(2*i+1,p);
}
void dofunc(int i){
    switch (funcs[i].t)
    {
        case 1:
            update(1,funcs[i].p,funcs[i].v);
            break;
        case 2:
            mult(1,funcs[i].v);
            break;
        case 3:
            int s=funcs[i].subs.size();
            for(int k=0;k<s;k++){
               int g=funcs[i].subs[k];
               dofunc(g); 
            }
            break;
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int t,p,v,c;
        scanf("%d",&t);
        switch (t)
        {
            case 1:
                scanf("%d %d",&p,&v);
                funcs[i]={t,p,v};
                break;
            case 2:
                scanf("%d",&v);
                funcs[i]={t,0,v};
                break;
            case 3:
                scanf("%d",&c);
                funcs[i]={t,0,0};
                for(int k=0;k<c;k++) {
                    int g;
                    scanf("%d",&g);
                    funcs[i].subs.push_back(g);
                }
                break;
        }
    }

    build(1,1,n);
    scanf("%d",&q);
    for(int k=0;k<q;k++){
        int f;
        scanf("%d",&f);
        dofunc(f);
    }
    for(int i=1;i<=n;i++) printf("%lld ",get(1,i));
}
