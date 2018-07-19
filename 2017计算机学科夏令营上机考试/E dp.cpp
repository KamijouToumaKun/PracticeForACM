#include <stdio.h>
int main(int argc, char const *argv[])
{
	int t;
	scanf("%d", &t);
	int h[100], dp[100], dp2[100];
	while (t--)
	{
		int n;
		scanf("%d", &n);
		for (int i=0;i<n;++i)
			scanf("%d", &h[i]);
		for (int i=0;i<n;++i)
		{
			dp[i] = 1;//初值很重要
			for (int j=0;j<i;++j)
				if (h[i] > h[j] && dp[j] + 1 > dp[i])
					dp[i] = dp[j] + 1;//以建筑i开头的话向左最多能跑多远
		}
		for (int i=n-1;i>=0;--i)
		{
			dp2[i] = 1;
			for (int j=i+1;j<n;++j)
				if (h[i] > h[j] && dp2[j] + 1 > dp2[i])
					dp2[i] = dp2[j] + 1;//以建筑i结尾的话向右最多能跑多远
		}
		int maxn = 0;
		for (int i=0;i<n;++i)
			if (dp[i] > maxn)
				maxn = dp[i];
		for (int i=0;i<n;++i)
			if (dp2[i] > maxn)
				maxn = dp2[i];
		printf("%d\n", maxn);
	}
	return 0;
}