#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN=65;
int xiao[MAXN];
int same_len_last_pos[51];
int n;
int sum,maxv;
int ans;
bool used[MAXN];
int start_pos[MAXN];

int first_not_greater_pos(int start ,int end,int len){
    if (start>end) return -1;
    int left=start;
    int right=end;
    while(left<right){
        int mid=(left+right)/2;
        if (xiao[mid]>len) left=mid+1;
        else right=mid;
    }
    if (xiao[left]>len) return -1;
    else return left;
}
void dfs(int next_pos,int left_len,int num){
    if (num==0) {
        cout<<ans;
        exit(0);
    }else {
        if (left_len==0){
            int pos=start_pos[num]+1;
            while(pos<n&&used[pos]) pos++;
            if (num-1>0&&pos>=n) return;
            dfs(pos,ans,num-1);
        }else {
            if (left_len==ans){
                start_pos[num]=next_pos;
                used[next_pos]=true;
                dfs(next_pos+1,left_len-xiao[next_pos],num);
                used[next_pos]=false;
            }else {
                int cur_pos=first_not_greater_pos(next_pos,n-1,left_len);
                if (cur_pos<0) return;
                while(cur_pos<n){
                    while(cur_pos<n&&used[cur_pos]) cur_pos++;
                    if (cur_pos<n){
                        used[cur_pos]=true;
                        dfs(cur_pos+1,left_len-xiao[cur_pos],num);
                        used[cur_pos]=false;
                        cur_pos=same_len_last_pos[xiao[cur_pos]]+1;
                    }
                }
            }
        }
    }
}

int main(){
    cin>>n;
    int k=0;
    for(int i=0;i<n;i++)
    {
        int a;
        cin>>a;
        if (a>50) continue;
        else {
            xiao[k]=a;
            k++;
        }
    }
    n=k;
    sort(xiao,xiao+n,greater<int>());
    maxv=xiao[0];
    for(int i=0;i<n;i++) {
        sum+=xiao[i];
        same_len_last_pos[xiao[i]]=i;
    }
    
    ans=maxv;
    while(ans<=sum/2){
        if (sum%ans==0){
           int num=sum / ans;
            dfs(0,ans,num); 
        }
        ans++;
    }
    cout<<sum; 
}