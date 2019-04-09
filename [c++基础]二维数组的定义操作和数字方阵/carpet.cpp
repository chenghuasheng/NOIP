#include <iostream>
using namespace std;
const int MAXN=10000;
int carpets[MAXN+1][4];
int n;
int x,y;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=0;j<4;j++) cin>>carpets[i][j];
    }
    cin>>x>>y;
    int find=-1;
    for(int i=n;i>0;i--){
        if (x>=carpets[i][0]&&x<=carpets[i][0]+carpets[i][2]&&
            y>=carpets[i][1]&&y<=carpets[i][1]+carpets[i][3]){
                find=i;
                break;
            }
    }
    cout<<find;
}