//#13. 表达式求值 
#include <iostream>
using namespace std;
const int MAXN=50000,key=10000;
struct stack{
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
};
stack s;

int main(){
    int x;
    cin>>x;
    s.push(x);
    char op;
    while(cin>>op){
        cin>>x;
        if (op=='*'){
            int y=s.get_top();
            x=(y*x)%key;
            s.pop();
            s.push(x);
        }else if(op=='+') {
            s.push(x);
        }
    }
    int ret=0;
    while(!s.empty()){
        x=s.get_top();
        ret=(ret+x)%key;
        s.pop();
    }
    cout<<ret;
}