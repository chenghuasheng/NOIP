#include <iostream>
#include <iomanip>

using namespace std;

const int MAXN=20;
int fz[MAXN][MAXN];
int n;

int main(){
    cin>>n;
    int c=0;
    bool dir=1;
    for(int b=n-1;b>=-(n-1);b--){
        switch (dir){
            case 0:
                for(int x=0;x<n;x++){
                    int y=x+b;
                    if (y>=0&&y<n){
                        c++;
                        fz[x][y]=c;
                    }
                }
                break;
            case 1:
                for(int x=n-1;x>=0;x--){
                    int y=x+b;
                    if (y>=0&&y<n){
                        c++;
                        fz[x][y]=c;
                    }
                }
                break;
        }
        dir=1-dir;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<setw(5)<<setfill(' ')<<fz[i][j];
        }
        cout<<endl;
    }
    system("pause");
}