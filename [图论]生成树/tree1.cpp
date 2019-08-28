//#1048. 「一本通 3.1 练习 4」Tree
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("tree.in");
ofstream fout("tree.in");
const int MAXV=50000;
struct edge{
    int u,v,w,col;
    bool operator<(const edge other)const{
        return w==other.w?col<other.col:w<other.w;
    }
};
vector<edge> edges;
//并查集
struct node{
    int head,next,last,length;
};
struct union_find_set{
    node ele[MAXV+1];
    void make_set(){
        for(int i=0;i<MAXV;i++) ele[i]={i,-1,i,1};
    }
    void union_set(int x,int y){
        int hx=find_set(x);
        int hy=find_set(y);
        if (hx!=hy){
            if (ele[hx].length<ele[hy].length) add_to(hx,hy);
            else add_to(hy,hx);
        }
    }
    int find_set(int x){
        return ele[x].head;
    }
    void add_to(int head_from,int head_to){
        ele[ele[head_to].last].next=head_from;
        ele[head_to].last=ele[head_from].last;
        ele[head_to].length+=ele[head_from].length;
        int cur=head_from;
        while(cur!=-1){
            ele[cur].head=head_to;
            cur=ele[cur].next;
        }
    }
};
union_find_set ufs;
int v,e,need;
int edge_num;
int min_sum;
int ans;

int check(int x){
    for(int i=0;i<edge_num;i++) 
        if (!edges[i].col) edges[i].w+=x;
    sort(edges.begin(),edges.begin()+edge_num);
    ufs.make_set();
    int cnt=0,cnt_b=0;
    min_sum=0;
    for(int i=0;i<edge_num;i++){
        int ru=ufs.find_set(edges[i].u);
        int rv=ufs.find_set(edges[i].v);
        if (ru!=rv){
            cnt++;
            ufs.union_set(ru,rv);
            min_sum+=edges[i].w;
            if (!edges[i].col) cnt_b++;
        }
        if (cnt>=v-1) break;
    }
    min_sum-=cnt_b*x;
    for(int i=0;i<edge_num;i++) 
        if (!edges[i].col) edges[i].w-=x;
    return cnt_b;
}
int main(){
    fin>>v>>e>>need;
    for(int i=1;i<=e;i++){
        int s,t,c,col;
        fin>>s>>t>>c>>col;
        edges.push_back({s,t,c,col});
    }
    edge_num=edges.size();
    int left=-100,right=100;
    while(left<=right){
        int mid=(left+right)/2;
        int cnt_b=check(mid);
        if (cnt_b>=need){
            left=mid+1;
            ans=min_sum;
        }else {
            right=mid-1;
        }
    }
    fout<<ans;
}