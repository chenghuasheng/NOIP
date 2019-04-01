#include <iostream>
#include <cmath>
using namespace std;
const float e=0.0001;

int x;
int main(){
    cout<<"Please input a number："<<endl;
    cin>>x;
    float r=x/2;
    while(abs(r*r-x)>e){
        r=(r+x/r)/2;
    }
    cout<<endl;
    cout<<x<<"'s square root is "<<endl;
    cout<<r<<endl;
    system("pause");
}