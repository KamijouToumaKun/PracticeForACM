#include <queue>
#include <stdio.h>
using namespace std;
int adj[21][21];
struct Node
{
	int country;
	int step;
	Node(int c, int s)
	{
		country = c;
		step = s;
	}
};
void search(int beg, int end)
{
	int vis[21] = {0};
	queue<Node> q;
	Node now(beg, 0);
	q.push(now);
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		vis[now.country] = 1;
		for (int i=1;i<=20;++i)
		{
			if (((i<now.country && adj[i][now.country]==1) || (i>now.country && adj[now.country][i]==1))
				&& vis[i] == 0)
			{
				if (i == end)
				{
					printf("%d to %d: %d\n", beg, end, now.step+1);
					return;
				}
				vis[i] = 1;
				q.push(Node(i, now.step+1));
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	int num, neighbor, t = 0;
	while (true)
	{
		t++;
		for (int i=1;i<=19;++i)
		{
			for (int j=1;j<=20;++j)
				adj[i][j] = 0; //清零。第一次的时候清零对象错了……
			if (scanf("%d", &num) == -1) //输入结束
				return 0;
			for (int j=0;j<num;++j)
			{
				scanf("%d", &neighbor);
				adj[i][neighbor] = 1;
			}
		}
		printf("Test Set #%d\n", t);
		scanf("%d", &num);
		int beg, end;
		for (int i=0;i<num;++i)
		{
			scanf("%d %d", &beg, &end);
			search(beg, end);
		}
		printf("\n"); //每组数据最后都有一个空行
	}
	return 0;
}