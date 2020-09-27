#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int MAXN=1000000;
long long n;
int c[MAXN+1];

vector<int> tree[MAXN+1];
int deep[MAXN+1];
int f[MAXN+1][21];
long long size[MAXN+1];
struct FenZhi{
    int top;
    int bottom;
};
FenZhi fzs[MAXN+1][2];
int fznum[MAXN+1];

void pre(int u,int fa){
    deep[u]=deep[fa]+1;
    f[u][0]=fa;
    size[u]=1;
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k];
        if (v!=fa){
            pre(v,u);
            size[u]+=size[v];
        }
    }
}
int lca(int x,int y){
    if (deep[x]<deep[y]) swap(x,y);
    for(int i=20;i>=0;i--) 
        if (deep[f[x][i]]>=deep[y]) x=f[x][i];
    if (x==y) return x;
    for(int i=20;i>=0;i--){
        if (f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
int lastson(int x,int y){
    for(int i=20;i>=0;i--) 
        if (deep[f[x][i]]>deep[y]) x=f[x][i];
    return x;
} 
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    
    pre(1,0);
    for(int i=1;i<=20;i++)
        for(int x=1;x<=n;x++)
            f[x][i]=f[f[x][i-1]][i-1];
    
    for(int i=1;i<=n;i++){
        int co=c[i];
        bool isNew=true;
        if (fznum[co]>2) continue;
        for(int j=0;j<fznum[co];j++){
            int bot=fzs[co][j].bottom;
            int top=fzs[co][j].top;
            int ca=lca(bot,i);
            if (ca==bot){
                isNew=false;
                if (top==0) fzs[co][j].top=bot;
                fzs[co][j].bottom=i;
            }else if (ca==i){
                isNew=false;
                if (top==0||deep[i]<deep[top]) fzs[co][j].top=i;
            }
        }
        if (isNew){
            fznum[co]++;
            if (fznum[co]<=2) fzs[co][fznum[co]-1].bottom=i;
        }
    }

    for(int i=1;i<=n;i++) {
        if (fznum[i]>2) cout<<0<<endl;
        else if (fznum[i]==0) printf("%lld\n",n*(n-1)/2);
        else if (fznum[i]==1){
            int bot=fzs[i][0].bottom;
            int top=fzs[i][0].top; 
            if (top==0) {
                long long s=0;
                for(int k1=0;k1<tree[bot].size();k1++){
                    int v1=tree[bot][k1];
                    for(int k2=k1+1;k2<tree[bot].size();k2++){
                        int v2=tree[bot][k2];
                        int t1=(v1==f[bot][0])?(n-size[bot]):size[v1];
                        int t2=(v2==f[bot][0])?(n-size[bot]):size[v2];
                        s+=t1*t2;
                    }
                }
                s+=1*(n-1);
                printf("%lld\n",s);
            }
            else {
                int son=lastson(bot,top);
                printf("%lld\n",size[bot]*(n-size[son]));
            }
        }else if (fznum[i]==2){
            int bot1=fzs[i][0].bottom;
            int bot2=fzs[i][1].bottom;
            printf("%lld\n",size[bot1]*size[bot2]);
        }
    }
}
