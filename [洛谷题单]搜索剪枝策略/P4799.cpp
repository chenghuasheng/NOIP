#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=40;
const long MAXK=1200000;
ll values[MAXK];
int vcount;
int n;
ll m;
ll price[MAXN+1];
ll ans=0;
void lsearch(int pos,ll val){
    if (val>0&&val<=m){
        ans++;
        values[vcount]=val;
        vcount++;
    }
    if (val>m) return;
    for(int i=pos+1;i<=n/2;i++){
        if (val+price[i]>m) break;
        lsearch(i,val+price[i]);
    }
}
void rsearch(int pos,ll val){
    if (val>0&&val<=m){
        ans++;
        int i=upper_bound(values,values+vcount,m-val)-values;
        if (i>=0) ans+=i;
    }
    if (val>m) return;
    for(int i=pos+1;i<=n;i++){
        if (val+price[i]>m) break;
        rsearch(i,val+price[i]);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>price[i];
    sort(price,price+n+1);
    lsearch(0,0);
    sort(values,values+vcount);
    rsearch(n/2,0);
    ans++;
    cout<<ans;
}