#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}}; /*     右左上下 */
char map[77][77];
bool vis[77][77];
int x1,y1,x2,y2,w,h;
struct Node
{
    int x,y,step,dir;   /*  x,y代表方向，step走了几步，dir = （0初始状态，1直走，2横走)*/
};
int bfs()
{
    memset(vis,0,sizeof(vis));
    queue<Node>q;
    Node s,e;
    s.x = x1;
    s.y = y1;
    s.step = 0;
    s.dir = 0;
    vis[s.x][s.y] = 1;
    q.push(s);
    while(!q.empty())
    {
        s = q.front();
        q.pop();
        for(int i=0;i<4;i++)
        {
            e.x = s.x + dir[i][0];
            e.y = s.y + dir[i][1];
            if(e.x == s.x)  e.dir = 2;      /*  横   */
            else e.dir = 1;     /*  竖   */
            if(e.x>=0&&e.x<=h+1&&e.y>=0&&e.y<=w+1&&!vis[e.x][e.y])
            {
                
                if(s.dir == 0) e.step = 1;
                else 
                {
                    if(s.dir == e.dir) e.step = s.step;
                    else e.step = s.step + 1 ;
                }
                if(e.x == x2&&e.y==y2)      return e.step;
                if(map[e.x][e.y] ==' ')  
                {       
                    vis[e.x][e.y] = 1;
                    q.push(e);
                }
            }
        }
    }
    return false;   
}
 
int main()
{
    int i,j,cnt=1,Step;
    while(cin>>w>>h&&(w||h))
    {
        memset(map,' ',sizeof(map));
        for(i=1;i<=h;i++)
        {   
            getchar();
            for(j=1;j<=w;j++)
            map[i][j] = getchar();
        }
        printf("Board #%d:\n",cnt++); 
        int count = 1;
        while(cin>>y1>>x1>>y2>>x2)
        {
            if(x1+y1+x2+y2==0) break;
            printf("Pair %d: ",count++);
            Step = bfs();
            if(!Step)
                printf("impossible.\n");
            else printf("%d segments.\n",Step);
        }
        printf("\n");
    }
    return  0;
}