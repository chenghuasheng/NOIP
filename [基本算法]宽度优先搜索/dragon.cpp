#include <fstream>
#include <vector>

using namespace std;
ifstream fin("dragon.in");
ofstream fout("dragon.out");

struct State{
    int x,y;
    int time;
};
const int MAXElENUM=100000;
struct queue{
    State ele[MAXElENUM];
    int front=0;
    int rear=0;
    void clear(){
        front=0;
        rear=0;
    }
    void push(State s){
        ele[rear]=s;
        rear++;
        rear=rear % MAXElENUM;
    }
    State get_front(){
        return ele[front];
    }
    void pop(){
        front++;
        front=front % MAXElENUM;
    }
    bool empty(){
        return front==rear;
    }
};
int dir_off[8][2]={{-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1}};
const int MAXN=20000;
int n,m;
int x1,y1,x2,y2;
vector<char> map[MAXN+1];
vector<bool> visited[MAXN+1];
queue qe;

bool canKill(int x1,int y1,int x2,int y2){
    for(int d=0;d<8;d++){
        int step=0;
        int newx,newy;
        do {
            step++;
            newx=x1+dir_off[d][0]*step;
            newy=y1+dir_off[d][1]*step;
            if (newx==x2&&newy==y2) return true;
            if (newx<1||newx>n||newy<1||newy>m) break;
        }while(map[newx][newy]!='X');
    }
    return false;
}
void bfs(int x1,int y1,int x2,int y2){
    for(int i=1;i<=n;i++)
    	for(int j=1;j<=m;j++) visited[i][j]=false;
    qe.clear();
    State start={x1,y1,0};
    visited[x1][y1]=true;
    qe.push(start);
    while(!qe.empty()){
        State cur=qe.get_front();
        if (canKill(cur.x,cur.y,x2,y2)){
            fout<<cur.time<<endl;
            return;
        }else {
            for(int d=0;d<4;d++){
                int newx=cur.x+dir_off[d][0];
                int newy=cur.y+dir_off[d][1];
                if (newx<1||newx>n||newy<1||newy>m) continue;
                if (!visited[newx][newy]&&map[newx][newy]=='O'){
                    State next={newx,newy,cur.time+1};
                    qe.push(next);
                    visited[newx][newy]=true;
                }
            }
        }
        qe.pop();
    }
    fout<<"Impossible!"<<endl;
}

int main(){
    fin>>n>>m;
    char ch;
    for(int i=1;i<=n;i++){
        map[i].push_back(' ');
        visited[i].push_back(false);
        for(int j=1;j<=m;j++) {
            fin>>ch;
            map[i].push_back(ch);
            visited[i].push_back(false);
        }
    }
    do {
        fin>>x2>>y2>>x1>>y1;
        if (x1==0&&y1==0&&x2==0&&y2==0) break;
        bfs(x1,y1,x2,y2);
    }while(1);
}