#include <iostream>
using namespace std;

int n;

void hanno(int n,char a ,char c,char b){
    if (n==1){
        cout<<a<<"->"<<c<<endl;
    }else {
        hanno(n-1,a,b,c);
        hanno(1,a,c,b);
        hanno(n-1,b,c,a);
    }
}

int main(){
    cin>>n;
    hanno(n,'A','C','B');
}