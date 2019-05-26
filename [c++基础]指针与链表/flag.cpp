#include<iostream>
using namespace std;
struct node
{
    int id;
    node *prev,*next;
};

int n,m;
node *head;
node *last;
node *cur;

int main(){
    cin>>n>>m;
    head=new(node);
    head->next=NULL;
    head->prev=NULL;
    last=head;
    for(int i=1;i<=n;i++){
        cur=new(node);
        cur->id=i;
        cur->next=NULL;
        cur->prev=NULL;
        last->next=cur;
        cur->prev=last;
        last=cur;
    }
    node *p=head->next;

    int i=0;
    int d=0;
    while(p!=NULL&&p!=head){
        i++;
        if (i==m){
            if (p->prev!=NULL) p->prev->next=p->next;
            if (p->next!=NULL) p->next->prev=p->prev;
            i=0;
        }
        if (d==0){
            if (p->next==NULL){
                d=1;
                p=p->prev;
            }else p=p->next;
        }else {
            if (p->prev==head){
                d=0;
                p=p->next;
            }else p=p->prev;
        }
    }
    cout<<head->next->id;
}

