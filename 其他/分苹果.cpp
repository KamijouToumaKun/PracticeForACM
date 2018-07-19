#include <stdio.h>
int dp[11][11][11];//允许有的盘子空着不放
int search(int m, int n, int last)
{//dp[m,n,last] = dp[m-last, n-1, last] + dp[m-last-1, n-1, last+1] +...
//至少保证m/n >= last
	if (dp[m][n][last] >= 0)
		return dp[m][n][last];
	if (n == 1)
	{
		dp[m][n][last] = 1;
		return 1;
	}
	else
	{
		int ans = 0;
		for (int i=last;i<=m/n;++i)
			ans += search(m-i, n-1, i);
		dp[m][n][last] = ans;
		return ans;
	}
}
int main(int argc, char const *argv[])
{
	int t, m, n;//m个相同的苹果、n个相同的盘子，每个盘子至少放i个苹果
	scanf("%d", &t);
	for (int i=0;i<11;++i)
		for (int j=0;j<11;++j)
			for (int k=0;k<11;++k)
				dp[i][j][k] = -1;
	while (t--)
	{
		scanf("%d%d", &m, &n);
		printf("%d\n", search(m, n, 0));//允许有的不放
	}
	return 0;
}