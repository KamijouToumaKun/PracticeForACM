#include <stdio.h>
int cost[1001][1001];
int vis[1001], dis[1001];
const int INF = 1<<28;
int n;
int mindistance()
{
	int minn = INF, index = 0;
	for (int i=1;i<=n;++i)
		if (vis[i]==0 && dis[i]<minn)
		{
			minn = dis[i];
			index = i;
		}
	return index;
}
int main(int argc, char const *argv[])
{
	int t;
	scanf("%d%d", &t, &n);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			cost[i][j] = INF;
	int beg, end, val;
	while (t--)
	{
		scanf("%d%d%d", &beg, &end, &val);
		if (val < cost[beg][end]) //卧槽，两点之间可能不止一条路的！
			cost[beg][end] = cost[end][beg] = val;
	}
	for (int i=2;i<=n;++i)
	{
		vis[i] = 0;
		dis[i] = cost[1][i];//初值要注意
	}
	vis[1] = 1;
	dis[1] = 0;
	int cnt = 1;
	while (cnt < n)
	{
		int node = mindistance();
		if (node != 0)
		{
			vis[node] = 1;
			cnt ++;
			for (int i=1;i<=n;++i)
				if (vis[i]==0 && dis[node]+cost[node][i] < dis[i])
					dis[i] = dis[node]+cost[node][i];
		}
		else
			break;
	}
	printf("%d", dis[n]);
	return 0;
}