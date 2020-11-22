#include <cstdio>
#include <vector>
using namespace std;
const long long MOD=998244353;
const int MAXN=100000;
struct Func{
    int t;
    int p,v;
};
long long a[MAXN+1];
Func funcs[MAXN+2];
vector<int> subs[MAXN+2];
int n,m,q;
long long mult[MAXN+2],preMult[MAXN+2];
int deg[MAXN+1];
bool vis[MAXN+2];
void dfs(int i){
    deg[i]++;
    if (funcs[i].t==1) mult[i]=1;
    else if (funcs[i].t==2) mult[i]=funcs[i].v;
    else if (funcs[i].t==3){
        mult[i]=1;
        for(int k=0;k<subs[i].size();k++){
            int j=subs[i][k];
            if (!vis[j]) dfs(j);
            else deg[j]++;
            mult[i]=(mult[i]*mult[j])%MOD;
        }
    }
    vis[i]=true;
}
void dfs2(int i,long long step_mult){
    if (deg[i]>1){
        preMult[i]=(preMult[i]+step_mult)%MOD;
        deg[i]--;
    }else {
        if (funcs[i].t==1) {
            int p=funcs[i].p;
            a[p]=(a[p]+(funcs[i].v*(step_mult+preMult[i])%MOD)%MOD)%MOD;
            preMult[i]=0;
        }else if (funcs[i].t==3){
            step_mult=(step_mult+preMult[i])%MOD;
            for(int k=subs[i].size()-1;k>=0;k--){
                int j=subs[i][k];
                dfs2(j,step_mult);
                step_mult=(step_mult*mult[j])%MOD;  
            }
        }
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
                    subs[i].push_back(g);
                }
                break;
        }
    }

    scanf("%d",&q);
    funcs[m+1].t=3;
    for(int k=0;k<q;k++){
        int f;
        scanf("%d",&f);
        subs[m+1].push_back(f);
    }
    dfs(m+1);
    for(int i=1;i<=n;i++) a[i]=(a[i]*mult[m+1])%MOD;
    dfs2(m+1,1);
    for(int i=1;i<=n;i++) printf("%lld ",a[i]);
}