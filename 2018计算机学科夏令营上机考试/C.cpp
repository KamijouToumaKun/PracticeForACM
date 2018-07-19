#include <queue>
#include <string.h>
#include <stdio.h>
#include <math.h> 
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;
int map[50][50];
int vis[50][50];
int w, h;
int totalindex = 1;
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
	{1,0}, {-1,0}, {0,1}, {0,-1}
};
void mark(int x, int y)
{
	vis[x][y] = 1;
	map[x][y] = totalindex;
	queue<Node> q;
	q.push(Node(x,y));
	Node now, next;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		for (int i=0;i<4;++i)
		{
			next.x = now.x+dir[i][0];
			next.y = now.y+dir[i][1];
			if (next.x<0||next.x>=w||next.y<0||next.y>=h)
				continue;
			if (vis[next.x][next.y]==0 && map[next.x][next.y] < 0)
			{
				vis[next.x][next.y] = 1;
				if (map[next.x][next.y] == -1) 
					map[next.x][next.y] = totalindex;
				q.push(next);
			}
		}
	}
}
int sum[2501];//TODO:clear
void count(int x, int y)
{
	vis[x][y] = 1;
	queue<Node> q;
	q.push(Node(x,y));
	Node now, next;
	int myindex;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		for (int i=0;i<4;++i)
		{
			next.x = now.x+dir[i][0];
			next.y = now.y+dir[i][1];
			if (next.x<0||next.x>=w||next.y<0||next.y>=h)
				continue;
			if (map[next.x][next.y] > 0)
				myindex = map[next.x][next.y];
			else if (vis[next.x][next.y]==0 && map[next.x][next.y] == -2)//count X
			{
				vis[next.x][next.y] = 1;
				q.push(next);
			}
		}
	}
	sum[myindex] ++;
}
void test()
{
	totalindex = 1; 
	char c;
	for (int i=0;i<w;++i)
	{
		getchar();
		for (int j=0;j<h;++j)
		{
			c = getchar();
			if (c == '.')
				map[i][j] = 0;
			else if (c == '*')
				map[i][j] = -1;
			else //X
				map[i][j] = -2;
		}
	}
	for (int i=0;i<w;++i)
		for (int j=0;j<h;++j)
			if (vis[i][j] == 0 && map[i][j]==-1)
			{
				mark(i,j);
				++totalindex;
			}
	for (int i=0;i<w;++i)
		for (int j=0;j<h;++j)
			vis[i][j] = 0;
	for (int i=1;i<=2500;++i)
		sum[i] = 0;//clear
	for (int i=0;i<w;++i)
		for (int j=0;j<h;++j)
			if (vis[i][j] == 0 && map[i][j]==-2)
			{
				count(i,j);
			}
	sort(sum, sum+totalindex);
	for (int i=1;i<totalindex-1;++i)//todo
		cout << sum[i] << " ";
	cout << sum[totalindex-1] << endl; 
}
int main()
{
	int t = 1;
	while (scanf("%d%d", &h, &w), w||h)
	{
		cout << "Throw " << t++ << endl;
		test();
		cout << endl;
	}
	return 0;
}