#include <iostream>
#include <iomanip>

using namespace std;
const int MAXN=20;
int fz[MAXN+2][MAXN+2];
int dir_off[4][2]={{0,1},{-1,0},{0,-1},{1,0}};

int n;
int main(){
    cin>>n;
    for(int i=0;i<n+2;i++) {
            fz[0][i]=-1;
            fz[n+1][i]=-1;
            fz[i][0]=-1;
            fz[i][n+1]=-1;
    }
    int c=0;
    int x=n;
    int y=0;
    int dir=0;
    do {
        int new_x=x+dir_off[dir][0];
        int new_y=y+dir_off[dir][1];
        if (fz[new_x][new_y]==0){
            c++;
            x=new_x;
            y=new_y;
            fz[x][y]=c;
        }else {
            dir=(dir+1)%4;
        }
    }while(c<n*n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout<<setw(5)<<setfill(' ')<<fz[i][j];
        cout<<endl;
    }
}
