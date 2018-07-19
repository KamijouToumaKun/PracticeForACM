#include <stdio.h>
int dp[13000];
int w[3500], p[3500];
int main(int argc, char const *argv[])
{
	int n, v;
	scanf("%d%d", &n, &v);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d", &w[i], &p[i]);
	}
	dp[0] = 0; //滚动数组
	for (int i=1;i<=n;++i)
		for (int j=v;j>=0;--j)
		{
			// dp[i][j] = dp[i-1][j];
			if (j-w[i] >= 0)
			{
				if (dp[j] <= dp[j-w[i]]+p[i])
					dp[j] = dp[j-w[i]]+p[i];
			}
		}
	printf("%d", dp[v]);
	return 0;
}