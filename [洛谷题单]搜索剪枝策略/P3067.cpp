#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int MAXN=20;
const int MAXM=1200000;
struct Node{
    ll val;
    int flag;
    bool operator <(const Node other)const{
        return val<other.val;
    }
};
Node search_results[MAXM];
int search_count;
ll number[MAXN+1];
ll sum;
int n;
int ans;
int mi2[21];

void dfs(int pos,ll val,int flag){
    if (val>sum/2) return;
    if (flag>0) {
        search_results[search_count]={val,flag};
        search_count++;
    }
    for(int i=pos+1;i<=n;i++){
        dfs(i,val+number[i],flag+mi2[i-1]);
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>number[i];
        sum+=number[i];
    }
    mi2[0]=1;
    for(int i=1;i<=20;i++) mi2[i]=2*mi2[i-1];
    dfs(0,0,0);
    sort(search_results,search_results+search_count);
    // int startPos=0;
    // ll curVal=search_results[0].val;
    // for(int i=1;i<search_count;i++){
    //     if (search_results[i].val!=curVal){
    //         startPos=i;
    //         curVal=search_results[i].val;
    //     }else{
    //         for(int j=startPos;j<i;j++){
    //             if ((search_results[j].flag&search_results[i].flag)==0) ans++;
    //         }
    //     }
    // }
    for(int i=0;i<search_count;i++)
        for(int j=i+1;j<search_count;j++){
            if (search_results[j].val>search_results[i].val) break;
            if ((search_results[j].val==search_results[i].val)&&(search_results[j].flag&search_results[i].flag)==0) ans++;
        }
    cout<<ans;
}