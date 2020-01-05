#include <iostream>
#include <algorithm>

using namespace std;
const int MAXN=300000;
int a[MAXN+1],b[MAXN+1];
int n,m;
struct Edge{
    int weight;
    char flag;
    bool operator <(const Edge other) const{
        return weight<other.weight;
    }
};
Edge edges[MAXN*2];
int alreadyX=0;
int alreadyY=0;
long long already=0;

long long ans=0;
int main(){
    cin>>n>>m;
    int k=0;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        edges[k]={a[i],'h'};
        k++;
    }
    for(int j=1;j<=m;j++) {
        cin>>b[j];
        edges[k]={b[j],'v'};
        k++;
    }
    sort(edges,edges+n+m);
    for(int k=0;k<n+m;k++){
        switch (edges[k].flag)
        {
            case 'h':
                ans+=1LL*edges[k].weight*(m-1);
                already+=m-1;
                if (alreadyX&&alreadyY) {
                    ans-=1LL*edges[k].weight*(alreadyY-1);
                    already-=alreadyY-1;
                }
                alreadyX++;
                break;
            case 'v':
                ans+=1LL*edges[k].weight*(n-1);
                already+=n-1;
                if (alreadyY&&alreadyX) {
                    ans-=1LL*edges[k].weight*(alreadyX-1);
                    already-=alreadyX-1;
                }
                alreadyY++;
                break;
        }
        if (already==1LL*n*m-1) break;
    }
    cout<<ans;
}