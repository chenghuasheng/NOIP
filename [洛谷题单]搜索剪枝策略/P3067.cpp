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
bool has[MAXM];
int search_count;
ll number[MAXN+1];
ll sum;
int n;
int ans;

void dfs(int pos,ll val,int flag){
    if (val>sum/2) return;
    if (flag>0) search_results[search_count++]={val,flag};
    for(int i=pos+1;i<=n;i++){
        dfs(i,val+number[i],flag+(1<<(i-1)));
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>number[i];
        sum+=number[i];
    }
    dfs(0,0,0);
    sort(search_results,search_results+search_count);
    int startPos=0;
    ll curVal=search_results[0].val;
    for(int i=1;i<search_count;i++){
        if (search_results[i].val!=curVal){
            startPos=i;
            curVal=search_results[i].val;
        }else{
            for(int j=startPos;j<i;j++){
                if ((search_results[j].flag&search_results[i].flag)==0) {
                    int flag=search_results[j].flag|search_results[i].flag;
                    if (!has[flag]){
                        ans++;
                        has[flag]=true;
                    }
                }
            }
        }
    }  
    cout<<ans;
}