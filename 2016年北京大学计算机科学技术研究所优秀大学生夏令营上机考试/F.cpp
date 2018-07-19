#include <stdio.h>
#include <queue>
using namespace std;
int b = 0, w = 0;
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
int dir[4][2] =
{
	{0, 1}, {0, -1}, {1, 0}, {-1, 0}
};
char map[100][100];
int vis[100][100];
void search(int sx, int sy, int n)
{
	queue<Node> q;
	q.push(Node(sx, sy));
	vis[sx][sy] = 1;
	int count = 1;
	bool flag; //记录这是哪一方的地盘
	Node now, next;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		for (int i=0;i<4;++i)
		{
			next.x = now.x + dir[i][0];
			next.y = now.y + dir[i][1];
			if (next.x>=0 && next.x<n && next.y>=0 && next.y<n)
			{
				if (map[next.x][next.y] == 'B') //记录这是哪一方的地盘
					flag = true;
				else if (map[next.x][next.y] == 'W')
					flag = false;
				else //是空处
				{
					if (vis[next.x][next.y] == 0)
					{
						vis[next.x][next.y] = 1;
						count ++;
						q.push(next);
					}
				}
			}
		}
	}
	if (flag == true)
		b += count;
	else
		w += count;
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	for (int i=0;i<n;++i)
	{
		getchar();
		for (int j=0;j<n;++j)
			map[i][j] = getchar();
	}
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
		{
			if (map[i][j] == '.')
			{
				if (vis[i][j] == 0)
					search(i, j, n);
			}
			else if (map[i][j] == 'B')
				b++;
			else
				w++;
		}
	printf("%d %d", b, w);
	return 0;
}
/*
4
..BW
...B
B...
.B..
*/