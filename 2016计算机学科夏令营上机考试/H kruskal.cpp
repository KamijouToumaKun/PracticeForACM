#include <stdio.h>
#include <algorithm>
using namespace std;
struct Edge
{
	int beg;
	int end;
	int w;
	Edge() {}
	Edge(int a, int b, int c)
	{
		beg = a;
		end = b;
		w = c;
	}
};
bool cmp(const Edge &a, const Edge &b)
{
	return a.w < b.w;
}
int f[450];
int findf(int x)
{
	if (x == f[x]) return x;
	int tmp = f[x];
	f[x] = findf(f[x]);
	return f[x];
}
int main(int argc, char const *argv[])
{
	int n, val, num;
	char beg[2], end[2];
	Edge edge[450];
	int top;
	while (scanf("%d", &n), n)
	{
		top = 0;
		for (int t=0;t<n-1;++t)
		{
			scanf("%s %d", beg, &num);
			for (int i=0;i<num;++i)
			{
				scanf("%s %d", end, &val);
				edge[top].beg = beg[0]-'A';
				edge[top].end = end[0]-'A';
				edge[top].w = val;
				top++;
			}
		}
		sort(edge, edge+top, cmp);
		//---
		for (int i=0;i<n;++i)
			f[i] = i;
		int blocks = n, total = 0;
		while (blocks > 1)
		{
			for (int i=0;i<top;++i)
			{
				int x = findf(edge[i].beg);
				int y = findf(edge[i].end);
				if (x != y)
				{
					f[x] = y;
					blocks --;
					total += edge[i].w;
				}
			}
		}
		printf("%d\n", total);
	}
	return 0;
}