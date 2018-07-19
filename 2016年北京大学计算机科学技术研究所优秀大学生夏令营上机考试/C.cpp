#include <stdio.h>
#include <queue>
using namespace std;
int map[1000][1000], vis[1000][1000];
struct Node
{
	int x;
	int y;
	Node() {}
	Node(int a, int b)
	{
		x = a;
		y = b;
	}
};
const int dir[4][2] = 
{
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};
void search(int sx, int sy)
{
	int count = 0;
	queue<Node> q;
	q.push(Node(sx, sy));
	vis[sx][sy] = 1;
	count = 1;
	Node now, next;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		for (int i=0;i<4;++i)
		{
			next.x = now.x + dir[i][0];
			next.y = now.y + dir[i][1];
			if (map[next.x][next.y] != 0 && vis[next.x][next.y] == 0) //外面有一圈0，不会越界
			{
				vis[next.x][next.y] = 1;
				count ++;
				q.push(next);
			}
		}
	}
	printf("%d", count);
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			scanf("%d", &map[i][j]);
	for (int i=0;i<n;++i)
	{
		int start, end;
		for (start=0;start<n;++start)
			if (map[i][start] == 0)
				break;
		for (end=n-1;end>=0;--end)
			if (map[i][end] == 0)
				break;
		if (start >= end)
			continue;
		int j;
		for (j=start;j<=end;++j)
			if (map[i][j] != 0)
				break;
		if (j < end) //找到第一个肿瘤内部的点
		{
			search(i, j);
			break;
		}
	}
	return 0;
}
/*
5
1	1	1	1	1
0	0	0	1	1
0	1	0	0	1
0	1	1	0	1
0	0	0	0	1
*/