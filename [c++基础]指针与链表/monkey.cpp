#include<iostream>
using namespace std;
struct node {
	int id;
	node *next;
};
node *head;
node *cur,*last;
int n,k;
int main(){
	cin>>n>>k;
	head=new(node);
	head->next=NULL;
	last=head;
	for(int i=1;i<=n;i++){
		cur=new(node);
		cur->next=NULL;
		cur->id=i;
		last->next=cur;
		last=cur;
	}
	last->next=head->next;
	last=head;
	cur=head->next;
	int i=0;
	while(cur!=NULL&&cur!=last){
		i++;
		if (i==k){
			cout<<cur->id<<' ';
			last->next=cur->next;
			i=0;
			cur=cur->next;
		}else {
			last=cur;
			cur=last->next;
		}
	}
	cout<<cur->id;
    system("pause");
}