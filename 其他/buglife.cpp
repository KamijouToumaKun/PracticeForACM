#include <stdio.h>
int f[2001], r[2001];
int findf(int x)
{
	if (f[x] == x) return x;
	int tmp = f[x];
	f[x] = findf(f[x]);
	r[x] = (r[x]+r[tmp]) % 2;
	return f[x];
}
int main(int argc, char const *argv[])
{
	int t, n, m, a, b, x, y;
	bool flag;
	scanf("%d", &t);
	for (int k=1;k<=t;++k)
	{
		scanf("%d%d", &n, &m);
		if (k != 1)
			printf("\n");
		printf("Scenario #%d:\n", k);
		flag = false;
		for (int i=1;i<=n;++i)
		{
			f[i] = i;
			r[i] = 0;
		}
		while (m--)
		{
			scanf("%d%d", &a, &b);
			if (flag)
				continue;
			x = findf(a);
			y = findf(b);
			if (x != y)
			{
				f[x] = y;//把x合并到y；
            	r[x] = (r[b]-r[a]+1) % 2;
            	//x对y的关系 = (- a对x的关系 + a对b的关系 + b对y的关系) % 2
			}
			else if ((r[b]-r[a]+1) % 2 != 0)
			{
				flag = true;//标记一下，还得把剩下的内容读完
			}
		}
		if (flag == true)
			printf("Suspicious bugs found!\n");
		else
			printf("No suspicious bugs found!\n");
	}
	return 0;
}