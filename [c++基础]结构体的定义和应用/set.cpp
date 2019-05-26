#include<iostream>
#include<cstring>

using namespace std;

struct Set{
    bool flag[26]={false};
    bool has(char c) const {
        if (flag[c-'a']) return true;
        else return false;
    }
    void add(char c){
        flag[c-'a']=true;
    }
    void input(char s[]){
        memset(flag,0,sizeof(flag));
        int len=strlen(s);
        for(int i=0;i<len;i++) add(s[i]);
    }

    Set operator +(Set const other)const{
        Set st;
        for(int i=0;i<26;i++){
            char c='a'+i;
            if (has(c)||other.has(c)) st.add(c);
        }
        return st;
    }
    Set operator -(Set const other)const{
        Set st;
        for(int i=0;i<26;i++) {
            char c='a'+i;
            if (has(c)&&!other.has(c)) st.add(c);
        }
        return st;
    }
    Set operator *(Set const other)const{
        Set st;
        for(int i=0;i<26;i++) {
            char c='a'+i;
            if (has(c)&&other.has(c)) st.add(c);
        }
        return st;
    }
    void output(){
        for(int i=0;i<26;i++){
            char c='a'+i;
            if (has(c)) cout<<c;
        }
        cout<<endl;
    }
};
Set s1,s2;
int n;
char str1[30],str2[30],op;

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>str1>>op>>str2;
        s1.input(str1);
        s2.input(str2);
        switch(op){
            case '+':
                (s1+s2).output();
                break;
            case '-':
                (s1-s2).output();
                break;
            case '*':
                (s1*s2).output();
                break;
        }
    }
    system("pause");
}