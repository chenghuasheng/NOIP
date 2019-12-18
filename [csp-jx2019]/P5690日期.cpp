#include <iostream>
using namespace std;
string s;
int m,d;
int monday[13]={0,31,28,31,30,31,60,31,31,30,31,30,31};
int main(){
    cin>>s;
    m=(s[0]-'0')*10+(s[1]-'0');
    d=(s[3]-'0')*10+(s[4]-'0');
    int tl=s[1]-'0';
    int th=s[0]-'0';
    if (d>31){
        if (m>12) cout<<2;
        else if (m>0) cout<<1;
        else cout<<2;
    }else if (d>28){
        if (m>12) {
            if (d<=monday[tl]) cout<<1;
            else if (tl+10<=12&&d<=monday[tl+10]) cout<<1;
            else if (th*10+1<=12&&d<=monday[th*10+1]) cout<<1;
            else if (th*10+2<=12&&d<=monday[th*10+2]) cout<<1;
            else cout<<2;
        }
        else if (m>0) {
           if (d>monday[m]) cout<<1;
           else cout<<0;
        }
        else cout<<1;

    }else if (d>0){
        if (m>12) cout<<1;
        else if (m>0) cout<<0;
        else cout<<1;
    }else {
        if (m>12) cout<<2;
        else if (m>0) cout<<1;
        else cout<<2;
    }
}