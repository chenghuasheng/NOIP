#include<iostream>
using namespace std;
int a[31][31];
int n;

void dfs(int x,int y){
    if (a[x][y]==2) a[x][y]=0;
    else return;
    if (x-1>0&&x-1<=n&&a[x-1][y]==2) dfs(x-1,y);
    if (x+1>0&&x+1<=n&&a[x+1][y]==2) dfs(x+1,y);
    if (y-1>0&&y-1<=n&&a[x][y-1]==2) dfs(x,y-1);
    if (y+1>0&&y+1<=n&&a[x][y+1]==2) dfs(x,y+1);
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
            if (a[i][j]==0) a[i][j]=2;
        }
    for(int i=1;i<=n;i++){
        dfs(1,i);
        dfs(n,i);
        dfs(i,1);
        dfs(i,n);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<a[i][j]<<' ';
        cout<<endl;
    }
    system("pause");
}