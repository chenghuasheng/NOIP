#include <iostream>
#include <vector>
#include <stack>

using namespace std;
const int MAXN=500000;
char node[MAXN+1];
vector<int> tree[MAXN+1];
int n;
stack<int> st;
long long sum[MAXN+1];//sum[i]表示从1到i节点的路径中总的合法子串数
long long lst[MAXN+1];//lst[i]表示从1到i节点的路径中i节点带来的合法子串数
int parent[MAXN+1];
void dfs(int u){
    int flag;
    int top;
    if (node[u]=='('||st.empty()){
        flag=1;
        lst[u]=0;
        st.push(u);
    }else {
        top=st.top();
        if (node[top]=='('){//有匹配的时候
            flag=2;
            st.pop();
            lst[u]=lst[parent[top]]+1;//当前结点与top匹配，它的带来的合法子串为
            //top的父结点带来的合法子串数加1
        }else {
            flag=1;
            lst[u]=0;
            st.push(u);
        }
    }
    sum[u]=sum[parent[u]]+lst[u];
    //计算子结点
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k];
        parent[v]=u;
        dfs(v);
    }
    //根据情况回溯
    if (flag==1){
        st.pop();
    }else if (flag==2){
        st.push(top);
    }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>node[i];
    for(int i=1;i<n;i++){
        int p;
        cin>>p;
        tree[p].push_back(i+1);
    }
    dfs(1);
    long long ans=1*sum[1];
    for(int i=2;i<=n;i++) ans=ans xor (i*sum[i]);
    cout<<ans;
}