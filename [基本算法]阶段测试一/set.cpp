#include <fstream>
#include <iostream>

using namespace std;
// ifstream fin("set.in");
// ofstream fout("set.out");

const int MAXN=30;
int n,k;
int s[MAXN+1][MAXN+1];

int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) s[i][1]=1;
    for(int i=2;i<=n;i++)
        for(int j=2;j<=i;j++){
            s[i][j]=s[i-1][j-1]+j*s[i-1][j];
        }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++) cout<<s[i][j]<<" ";
        cout<<endl;
    }
    cout<<s[n][k];
    system("pause");
}

