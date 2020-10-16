#include <iostream>
#define ll long long
using namespace std;
const int MAXN=100000;
ll a[MAXN+1];
struct Node{
    int l,r;
    ll sum;
    ll lz;
};
Node tree[(MAXN+1)*2];
void build(int i,int l,int r){
    tree[i].l=l;
    tree[i].r=r;
    if (l==r){
        tree[i].sum=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
    tree[i].sum=tree[i*2].sum+tree[i*2+1].sum;
}
void push_down(int i)
{
    if(tree[i].lz!=0)
    {
        tree[i*2].lz+=tree[i].lz;//左右儿子分别加上父亲的lz
        tree[i*2+1].lz+=tree[i].lz;
        tree[i*2].sum+=tree[i].lz*(tree[i*2].r-tree[i*2].l+1);//左右分别求和加起来
        tree[i*2+1].sum+=tree[i].lz*(tree[i*2+1].r-tree[i*2+1].l+1);
        tree[i].lz=0;//父亲lz归零
    }
    return ;
}
void add(int i,int l,int r,int k){
    if (tree[i].l>=l&&tree[i].r<=r){
        tree[i].sum+=k*(tree[i].r-tree[i].l+1);
        tree[i].lz+=k;
        return;
    }
    push_down(i);
    if (tree[i*2].r>=l) add(i*2,l,r,k);
    if (tree[i*2+1].l<=r) add(i*2+1,l,r,k);
    tree[i].sum=tree[i*2].sum+tree[i*2+1].sum;
}
ll query(int i,int l,int r){
    if (tree[i].l>=l&&tree[i].r<=r) return tree[i].sum;
    push_down(i);
    ll s=0;
    if (tree[i*2].r>=l) s+=query(i*2,l,r);
    if (tree[i*2+1].l<=r) s+=query(i*2+1,l,r);
    return s;
}
int n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int o,x,y,k;
        cin>>o;
        if (o==2){
            cin>>x>>y;
            cout<<query(1,x,y)<<endl;
        }else if (o==1){
            cin>>x>>y>>k;
            add(1,x,y,k);
        }
    }
}