#include <stdio.h>
#include <math.h>

const int INF = 0x3f3f3f3f;
const int MAXN = 205;
struct Node
{
    double x, y;
}node[MAXN];

int n;
double cost[MAXN][MAXN];

double min(double x, double y)
{
	if (x < y)
		return x;
	else
		return y;
}
/*
Dijkstra 算法伪代码：
S = {}                                       // 已求出到 start 点最短路的点集合，初始为空
d[start] = 0, 其余值为正无穷大
while (|S| < |V|)                            // 数学符号|A|表示集合A的点数
    取出不在S中的最小的d[i]
    for (i相邻的点j，j不属于S)
        d[j] = min(d[j], d[i] + c[i][j])     // 维护距离
    S = S + {i}
*/
double dis[MAXN];
int vis[MAXN];
int mindistance() //在没有走到过的点里，找寻dis最小的点
{
    int minnode = 0, minn = INF;
    for (int i=1;i<=n;++i)
        if (minn > dis[i] && !vis[i])
        {
            minn = dis[i];
            minnode = i;
        }
    return minnode;
}
void dijkstra()
{
	for (int i=1;i<=n;++i) 
	{
  		dis[i] = cost[1][i];				//考虑其他结点到结点1的最短路径
  		vis[i] = 0;
	}
    vis[1] = 1;								//节点1已归入集合S中
    int vnum = 1;							//归入集合S中节点的数量
    while (vnum < n)
    {
        int node = mindistance();
        if (node != 0)
        {
            vnum ++;
            vis[node] = 1;
            for (int i=1;i<=n;++i) //在没有走到过的点中，找到dis最小的点，更新每一个点的dis
                if (dis[i] > dis[node] + cost[node][i] && !vis[i])
                    dis[i] = dis[node] + cost[node][i];
        }
        else //全都走过了：这种情况不会发生吧？
        	break;
    }
}

int main(int argc, char const *argv[])
{
    for (int i=0;i<MAXN;++i)
        for (int j=0;j<MAXN;++j)
            cost[i][j] = INF;
    // node的下标从1开始
    scanf("%lf%lf%lf%lf", &node[1].x, &node[1].y, &node[2].x, &node[2].y);//起点和终点
    n = 3;
    const double wsp = 10 * 1000 / 60;
	const double ssp = 40 * 1000 / 60;
    while (scanf("%lf%lf", &node[n].x, &node[n].y) != -1) //读入每条线的起点
    {
        n++;
        while (scanf("%lf%lf", &node[n].x, &node[n].y), node[n].x!=-1 || node[n].y!=-1 )
        {
        	double x = node[n-1].x - node[n].x;
        	double y = node[n-1].y - node[n].y;
            cost[n][n-1] = cost[n-1][n] = sqrt(x*x+y*y) / ssp;
            n++;//同一条线的地铁站之间连边
        }
    }//不同线上的地铁站之间连边：走路可以到达
    for (int i=1;i<n-1;++i)
    {
        cost[i][i] = 0;
        for (int j=i+1;j<n;++j)
        {
        	double x = node[i].x - node[j].x;
        	double y = node[i].y - node[j].y;
        	double dis = sqrt(x*x+y*y) / wsp;
        	if (dis < cost[i][j])
            	cost[i][j] = cost[j][i] = dis;
        }
    }
    n--; //一共n个顶点
    dijkstra();

    printf("%d", int(dis[2]+0.5)); //四舍五入
    return 0;
}