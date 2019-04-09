#include <iostream>
#include <iomanip>
using namespace std;
const int MAXN=20;

int fz[MAXN][MAXN];
int n;
int main(){
    cin>>n;
    int c=0;
    int x=0;
    int y=n/2;
    do {
        c++;
        fz[x][y]=c;
        int new_x=(x-1+n)%n;
        int new_y=(y+1)%n;
        if (fz[new_x][new_y]>0){
            new_x=(x+1)%n;
            new_y=y;
        }
        x=new_x;
        y=new_y;
    }while(c<n*n);
    
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cout<<setw(5)<<setfill(' ')<<fz[i][j];
        cout<<endl;
    }
    system("pause");
}