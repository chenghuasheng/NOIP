#include<iostream>
#include <string>
using namespace std;

string s,s1;
char reverse[16]={'F','E','D','C','B','A','9','8','7','6','5'
,'4','3','2','1','0'};

int main(){
    cin>>s;
    s1="#";
    for(int i=1;i<s.length();i++){
        char c=s[i];
        int val;
        if (c>='0'&&c<='9') val=c-'0';
        else val=c-'A'+10;
        s1+=reverse[val];
    }
    cout<<s1;
}