#include <iostream>
#include <vector>
using namespace std;
const int MAXN=100000;
int n,m,p;
int a[MAXN+1];
struct Tag{
    char op;
    int num;
};
struct Node{
    int l,r;
    int sum;
    vector<Tag> lazy_tags;
};
Node tree[(MAXN+1)*2];
void build(int i,int l,int r){
    tree[i].l=l;
    tree[i].r=r;
    if (l==r) {
        tree[i].sum=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(i*2,l,mid);
    build(i*2+1,mid+1,r);
    
}
int main(){
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++) cin>>a[i];

}