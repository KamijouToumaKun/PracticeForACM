#include <queue>
#include <string.h>
#include <stdio.h>
#include <math.h> 
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
int dis[101], vis[101];
int cost[101][101];
int n, s, e;
int mindis()
{
	int minn = 9999999, index = -1;
	for (int i=1;i<=n;++i)
		if (vis[i]==0 && dis[i]<minn)
		{
			minn = dis[i];
			index = i;
		}
	return index;
}
bool flag = false;
void dijkstra()
{
	for (int i=1;i<=n;++i)
	{
		dis[i] = cost[s][i];
		vis[i] = 0;
	}
	vis[s] = 1;
	int cnt = 1;
	while (cnt < n)
	{
		int node = mindis();
		if (node != -1)
		{ 
			vis[node] = 1;
			cnt ++;
			for (int i=1;i<=n;++i)
				if (vis[i]==0 && dis[i]>dis[node]+cost[node][i]) 
					dis[i] = dis[node]+cost[node][i];
		}
		else
		{
			break;
		}
	}
}
int main()
{
	scanf("%d%d%d", &n, &s, &e);
	int num, dst;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=n;++j)
			cost[i][j] = 9999999; 
	for (int i=1;i<=n;++i)
	{
		scanf("%d", &num);
		for (int j=0;j<num;++j)
		{
			scanf("%d", &dst);
			cost[i][dst] = j==0?0:1;
		}
	}
	if (s == e)
		printf("0");
	else
	{
		dijkstra();
		if (dis[e] >= 99999)
			printf("-1");
		else
			printf("%d", dis[e]);
	} 
	return 0;
}