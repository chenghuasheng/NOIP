//#13. 表达式求值 
//此程序为通用的表达式求值，能计算多种运算（包含括号）的表达式
#include <iostream>
#include <sstream>
using namespace std;
const int MAXN=1000,key=10000;
struct number_stack{
	long ele[MAXN];
	int top=0;
	void push(long x){
		ele[top]=x;
		top++;
	}
	void pop(){
		top--;
	}
	long get_top(){
		return ele[top-1];
	}
	bool empty(){
		return top==0;
	}
	int size(){
		return top;
	}
};
struct operator_stack{
	char ele[MAXN];
	int top=0;
	void push(char x){
		ele[top]=x;
		top++;
	}
	void pop(){
		top--;
	}
	char get_top(){
		return ele[top-1];
	}
	bool empty(){
		return top==0;
	}
};
number_stack ns;
operator_stack os;
int priority[256];

long str2int(string &s){
	long ret;
	stringstream ss(s);
	ss>>ret;
	return ret;	
}
int main(){
    //在此添加需要用到的运算符的优先级，如果有括号，左括号的优级应该高于其他运算符
    //右括号的优先级低于其他运算符
	priority['#']=-1;
	priority['+']=0;
	priority['*']=1;
	
	string s;
	getline(cin,s);
	s=s+'#';
	int l=s.length();
	string tmp="";

	for(int i=0;i<l;i++){
		char c=s[i];
		if (c>='0'&&c<='9'){
			tmp+=c;
		}else{
			if (tmp!="") {
				ns.push(str2int(tmp));
				tmp="";
			}
			if (c=='+'||c=='*'||c=='#'){
				while (!os.empty()){
					char pre_c=os.get_top();
					if (pre_c=='#') os.pop();
					else if (priority[c]<=priority[pre_c]){
						if (ns.size()<2) {
							return 0;
						}else {
							long a=ns.get_top();
							ns.pop();
							long b=ns.get_top();
							ns.pop();
							long ans;
							switch (pre_c){
								case '+':
									ans=a+b;
									break;
								case '*':
									ans=a*b;
									break;
							}
							ans=ans%key;
							ns.push(ans);
							os.pop();
						}
					}else break;
				}
				os.push(c);
			}else continue;
		}
	}
	cout<<ns.get_top() % key;
}