#include <iostream>
using namespace std;
long long n,m,p;
long long k;

int main(){
    cin>>n>>m>>k>>p;
    long long maxxi=min(k/p,m);
    bool can=false;
    long long remain=k-p*maxxi;
    long long remain_maxxi;
    if (n-p==0) {
        if (remain==0){
            remain_maxxi=0;
            can=true;
        }
    }else {
        remain_maxxi=remain/(n-p);
        if (remain%(n-p)!=0) remain_maxxi++;
        if (remain_maxxi<maxxi){
            can=true;
        }
    }
    if (can){
        cout<<"YES"<<endl;
        for(int i=1;i<=p;i++) cout<<maxxi<<" "<<m-maxxi<<endl;
        for(int i=p+1;i<=n;i++){
            long long xi=min(remain_maxxi,remain);
            cout<<xi<<" "<<m-xi<<endl;
            remain-=xi;
        }
    }else {
        cout<<"NO"<<endl;
    }
}