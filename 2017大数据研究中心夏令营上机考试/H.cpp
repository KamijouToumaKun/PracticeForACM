#include <stdio.h>
const int INF = 1<<28;
int n, m, x;
int cost1[1001][1001], cost2[1001][1001];
int dis1[1001], vis1[1001];
int dis2[1001], vis2[1001];
//多维数组也可以作为函数的参数。在函数定义时对形参数组可以指定每一维的长度，也可省去第一维的长度。
int mindistance(int dis[], int vis[])
{
	int minn = INF, index = -1;
	for (int i=1;i<=n;++i)
		if (vis[i] == 0 && dis[i] < minn)
		{
			minn = dis[i];
			index = i;
		}
	return index;
}
void dijkstra(int dis[], int vis[], int cost[][1001])
{
	for (int i=1;i<=n;++i)
	{
		dis[i] = cost[x][i];//初值不要搞错，注意不是INF
		vis[i] = 0;
	}
	dis[x] = 0;
	vis[x] = 1;
	int cnt = 1, node;
	while (cnt < n)
	{
		node = mindistance(dis, vis);
		vis[node] = 1;
		cnt ++;
		for (int i=1;i<=n;++i)
			if (vis[i] == 0 && dis[node]+cost[node][i]<dis[i])
				dis[i] = dis[node] + cost[node][i];
	}
}
int main(int argc, char const *argv[])
{
	scanf("%d%d%d", &n, &m, &x);
	int beg, end, val;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			cost1[i][j] = cost2[i][j] = INF;
	for (int i=1;i<=m;++i)
	{
		scanf("%d%d%d", &beg, &end, &val);
		if (val < cost1[beg][end])
		{
			cost1[beg][end] = val;
			cost2[end][beg] = val;
		}
	}
	dijkstra(dis1, vis1, cost1);
	dijkstra(dis2, vis2, cost2);
	int maxn = 0;
	for (int i=1;i<=n;++i)
		if (dis1[i] + dis2[i] > maxn)
			maxn = dis1[i] + dis2[i];
	printf("%d", maxn);
	return 0;
}