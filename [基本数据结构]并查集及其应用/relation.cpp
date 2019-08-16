//#35. 亲戚
#include <cstdio>
using namespace std;

const int MAXN=20000;
struct union_find_set{
    int father[MAXN+1];
    void make_set(){
        for(int i=1;i<=MAXN;i++) father[i]=i;
    }
    int find_set(int x){
        while(father[x]!=x) x=father[x];
        return x;
    }
    void union_set(int x,int y){
        int hx=find_set(x);
        int hy=find_set(y);
        while(father[y]!=y){
            int p=father[y];
            father[y]=hx;
            y=p;
        }
        father[hy]=hx;
    }
};

union_find_set ufs;
void getd(int &x){
    char c;
    for(c=getc(stdin);c<'0'||c>'9';c=getc(stdin));

    for(x=0;c>='0'&&c<='9';c=getc(stdin))
        x=x*10+c-'0';
}
int n,m,q;
int main(){
    getd(n);getd(m);
    ufs.make_set();
    for(long i=0;i<m;i++){
        int ai,bi;
        getd(ai);getd(bi);
        ufs.union_set(ai,bi);
    }
    getd(q);
    for(long i=0;i<q;i++){
        int ci,di;
        getd(ci);getd(di);
        if (ufs.find_set(ci)==ufs.find_set(di)) printf("Yes\n");
        else printf("No\n");
    }
}
