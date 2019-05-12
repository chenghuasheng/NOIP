#include<iostream>
using namespace std;

int mi2[16];
int n;

void express(int x){
    for(int k=15;k>=0;k--){
        if (x>=mi2[k]){
            if (k==1) cout<<'2';
            else if (k==0) cout<<"2(0)";
            else {
                cout<<"2(";
                express(k);
                cout<<')';
            }
            x=x-mi2[k];
            if (x>0) cout<<'+';
            else break;
        }
    }
}
int main(){
    mi2[0]=1;
    for(int k=1;k<=15;k++) mi2[k]= mi2[k-1]*2;
    cin>>n;
    express(n);
}