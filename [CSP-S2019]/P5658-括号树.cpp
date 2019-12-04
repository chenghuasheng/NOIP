#include <iostream>
#include <vector>
#include <stack>

using namespace std;
const int MAXN=500000;
char node[MAXN+1];
vector<int> tree[MAXN+1];
int n;
int k[MAXN+1];
int parent[MAXN+1];
void dp(int x){
    int p=parent[x];
    if (node[x]=='(') k[x]=k[p];
    else {
        stack<char> s;
        s.push(node[x]);
        int i=0;
        while(p>0&&!s.empty()){
            char c=s.top();
            if (node[p]=='('&&c==')') {
                i++;
                s.pop();
            }else{
                s.push(node[p]);
            }
            p=parent[p];
        }
        if (k[p]>0) k[x]=k[p]*
    }
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>node[i];
    for(int i=1;i<n;i++){
        int p;
        cin>>p;
        tree[p].push_back(i+1);
        parent[i+1]=p;
    }
}