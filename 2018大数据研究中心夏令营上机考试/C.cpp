#include <stdio.h>
#include <queue>
using namespace std;
struct Node
{
	int x;
	int y;
	int step;
	Node() {}
	Node(int a, int b, int c)
	{
		x = a;
		y = b;
		step = c;
	}
};
const int dir[4][2] = 
{
	{0,1}, {0,-1}, {1,0}, {-1,0}
};
int sx, sy, ex, ey, m, t;
char map[11][11];
int vis[10][10];
void search()
{
	queue<Node> q;
	q.push(Node(sx, sy, 0));
	vis[sx][sy] = 1;
	Node now, next;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		if (now.step >= t)//next还需要一次
		{
			printf("NO\n");
			return;
		}
		for (int i=0;i<4;++i)
		{
			next.x = now.x + dir[i][0];
			next.y = now.y + dir[i][1];
			next.step = now.step + 1;
			if (next.x>=0&&next.x<m&&next.y>=0&&next.y<m&&vis[next.x][next.y]==0)
			{
				if (map[next.x][next.y] == 'E')
				{
					printf("YES\n");
					return;
				}
				else if (map[next.x][next.y] == '.')
				{
					vis[next.x][next.y] = 1;
					q.push(next);
				}
			}
		}
	}
	printf("NO\n");
	return;
}
int main(int argc, char const *argv[])
{
	int k;
	scanf("%d", &k);
	while (k--)
	{
		scanf("%d %d", &m, &t);
		for (int i=0;i<m;++i)
		{
			scanf("%s", map[i]);
			for (int j=0;j<m;++j)
			{
				vis[i][j] = 0;	
				if (map[i][j] == 'S')
				{
					sx = i;
					sy = j;
				}
				else if (map[i][j] == 'E')
				{
					ex = i;
					ey = j;
				}
			}
		}
		search();
	}
	return 0;
}