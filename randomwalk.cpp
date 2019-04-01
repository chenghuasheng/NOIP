#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

struct Offset{
    int x,y;
};
struct Position{
    int x,y;
    void Add(Offset off){
        x+=off.x;
        y+=off.y;
    }
};

default_random_engine e; 
uniform_int_distribution<unsigned> u(0, 3); //随机数分布对象 
int c[4];
Offset direct_offset[4]={{1,0},{0,1},{-1,0},{0,-1}};
int n;
int main(){
    string ans="";
    do {
        Position pos={0,0};
        cout<<"the start position is : "<<pos.x<<' '<<pos.y<<endl;
        e.seed(time(NULL)) ;
        cout<<"please input the step:"<<endl;
        cin>>n;
        fill(c,c+4,0);
        for(int i=0;i<n;i++){
            int d=u(e);
            c[d]++;
            pos.Add(direct_offset[d]);
        }

        cout<<"the last position is : "<<pos.x<<' '<<pos.y<<endl;
        cout<<endl;
        for(int i=0;i<4;i++){
            cout<<i<<" "<<c[i]<<endl;
        }
        cout<<endl;
        cout<<"do again?(y or n)"<<endl;
        cin>>ans;
    }while (ans=="y"||ans=="yse");

    system("pause");
}