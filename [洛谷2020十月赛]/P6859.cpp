#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN=2000000;
int a[MAXN+1];
struct Node{
    int l,r;
    int sum;
    int cnt1;
};
Node tree[(MAXN+1)*3];
int n,m;
inline int read(){
    int s=1,v=0;
    char c=getchar();
    for(;!isdigit(c);c=getchar()) if (c=='-') s=-1;
    for(;isdigit(c);c=getchar()) v=v*10+(c-'0');
    return v*s;
}
void build(int i,int l,int r){
    tree[i].l=l;
    tree[i].r=r;
    if (l==r) {
        tree[i].sum=a[l];
        if (a[l]==1) tree[i].cnt1=1;
        else tree[i].cnt1=0;
        return;
    }
    int mid=(l+r)/2;
    build(2*i,l,mid);
    build(2*i+1,mid+1,r);
    tree[i].sum=tree[2*i].sum+tree[2*i+1].sum;
    tree[i].cnt1=tree[2*i].cnt1+tree[2*i+1].cnt1;
}
void update(int i,int j,int k){
    if(tree[i].l==tree[i].r){//如果是叶子节点，那么说明找到了
        tree[i].sum=k;
        if (k==1) tree[i].cnt1=1;
        else tree[i].cnt1=0;
        return ;
    }
    if(j<=tree[i*2].r)  update(i*2,j,k);//在哪往哪跑
    else  update(i*2+1,j,k);
    tree[i].sum=tree[i*2].sum+tree[i*2+1].sum;//返回更新
    tree[i].cnt1=tree[2*i].cnt1+tree[2*i+1].cnt1;
    return ;
}
/*int query(int i,int l,int r){
    if (tree[i].l>=l&&tree[i].r<=r) return tree[i].sum;
    if(tree[i].r<l || tree[i].l>r)  return 0;
    int s=0;
    if (tree[2*i].r>=l) s+=query(2*i,l,r);
    if (tree[2*i+1].l<=r) s+=query(2*i+1,l,r);
    return s;
}*/

int find(int i,int s,bool &equal){
    if (tree[i].l==tree[i].r) {
        if (tree[i].sum==s) equal=true;
        else equal=false;
        return tree[i].l;
    }
    if (s<=tree[2*i].sum) find(2*i,s,equal);
    else find(2*i+1,s-tree[2*i].sum,equal);
}
int find_first1(int i,int begin){
    if (tree[i].l==tree[i].r){
        if (tree[i].sum==1) return tree[i].l;
        else return -1;
    }else {
        if (begin>tree[2*i].r) return find_first1(2*i+1,begin);
        else if (tree[2*i].cnt1<=0) return find_first1(2*i+1,tree[2*i+1].l);
        else{
            int t=find_first1(2*i,begin);
            if (t==-1) t=find_first1(2*i+1,tree[2*i+1].l);
            return t;
        }
    }
}
int main(){
    n=read();m=read();
    for(int i=1;i<=n;i++) a[i]=read();
    build(1,1,n);
    bool has=false;
    int left,right;
    for(int i=0;i<m;i++){
        char c = getchar();
		for (;c !='C'&&c!='A';c = getchar());
        switch (c)
        {
            case 'A':
                int s;
                s=read();
                if (s<=0||s>tree[1].sum) puts("none");
                else {
                    int pos=find(1,s,has);
                    if (has) printf("%d %d\n",1,pos);
                    else {
                        int begin,end;
                        int p1=find_first1(1,1);
                        if (p1==-1) puts("none");
                        else {
                            if (p1>pos) printf("%d %d\n",p1-pos+1,p1);
                            else {
                                int p2=find_first1(1,pos+1);
                                if (p2==-1) {
                                  if (p1+pos-1<=n) printf("%d %d\n",p1+1,p1+pos-1);
                                  else puts("none");
                                }else {
                                    if (p1<=p2-pos&&p1+pos-1<=n) printf("%d %d\n",p1+1,p1+pos-1);
                                    else printf("%d %d\n",p2-pos+1,p2);
                                } 
                            }
                        }
                    }
                }
                break;
            case 'C':
                int j,k;
                j=read();k=read();
                if (k!=a[j]){
                    a[j]=k;
                    update(1,j,k);
                }
                break;
        }
    }
}