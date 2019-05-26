#include <fstream>
#include <cstring>
using namespace std;
ifstream fin("point24.in");
ofstream fout("point24.out");

typedef char String[20];
struct oppath{
    int a,b;
    char op;
};

char chars[4];
int shu[4];
oppath paths[4];
String ans[4] ,buffer;
String minans="ZZZZZ";

void output(){
    for(int i=0;i<4;i++) sprintf(ans[i],"%c",chars[i]);
    for(int i=0;i<3;i++){
        sprintf(buffer,"(%s%c%s)",ans[paths[i].a],paths[i].op,ans[paths[i].b]);
        sprintf(ans[paths[i].a],"%s",buffer);
    }
    if (strcmp(minans,ans[paths[2].a])>0) strcpy(minans,ans[paths[2].a]);
}
void dfs(int dep){
    if (dep>=3){
        int i;
        for(i=0;i<4;i++) if (shu[i]>0) break;
        if (i<4&&shu[i]==24){
            output();
        }
    }else for(int i=0;i<4;i++)
        for(int j=0;j<4;j++){
            if (i!=j&&shu[i]>0&&shu[j]>0){
                int t1=shu[i],t2=shu[j];
                /*  + 运算 */
                shu[i]=shu[i]+shu[j];
                shu[j]=0;
                paths[dep]={i,j,'+'};
                dfs(dep+1);
                shu[i]=t1;shu[j]=t2;

                /*  - 运算 */
                shu[i]=shu[i]-shu[j];
                shu[j]=0;
                paths[dep]={i,j,'-'};
                dfs(dep+1);
                shu[i]=t1;shu[j]=t2;

                /*  * 运算 */
                shu[i]=shu[i]*shu[j];
                shu[j]=0;
                paths[dep]={i,j,'*'};
                dfs(dep+1);
                shu[i]=t1;shu[j]=t2;

                /*  / 运算 */
                if ((shu[i] % shu[j]==0)&&shu[i]>=shu[j]) {
                    shu[i]=shu[i]/shu[j];
                    shu[j]=0;
                    paths[dep]={i,j,'/'};
                    dfs(dep+1);
                    shu[i]=t1;shu[j]=t2;
                }

                /*  & 运算 */
                shu[i]=shu[i]&shu[j];
                shu[j]=0;
                paths[dep]={i,j,'&'};
                dfs(dep+1);
                shu[i]=t1;shu[j]=t2;

                /*  | 运算 */
                shu[i]=shu[i]|shu[j];
                shu[j]=0;
                paths[dep]={i,j,'|'};
                dfs(dep+1);
                shu[i]=t1;shu[j]=t2;

                /*  ^ 运算 */
                shu[i]=shu[i]^shu[j];
                shu[j]=0;
                paths[dep]={i,j,'^'};
                dfs(dep+1);
                shu[i]=t1;shu[j]=t2;
            }
        }
}

int main(){
    for(int i=0;i<4;i++) {
        fin>>chars[i];
        switch (chars[i])
        {
            case 'A':
                shu[i]=1;
                break;
            case 'T':
                shu[i]=10;
                break;
            case 'J':
                shu[i]=11;
                break;
            case 'Q':
                shu[i]=12;
                break;
            case 'K':
                shu[i]=13;
                break;
            default:
                shu[i]=chars[i]-'0';
                break;
        }
    }
    dfs(0);
    fout<<minans;
}