#include <stdio.h>
int main(int argc, char const *argv[])
{
	const int NEGA_INF = -(1<<30);
	int t, m[101], p[101], dp[101];
	scanf("%d", &t);
	while (t--)
	{
		int n, k;
		scanf("%d%d", &n, &k); //餐馆之间的距离必须大于k
		m[0] = NEGA_INF; //增加一个虚拟的餐馆
		p[0] = 0;
		for (int i=1;i<=n;++i)
			scanf("%d", &m[i]);//地点位置
		for (int i=1;i<=n;++i)
			scanf("%d", &p[i]);//利润位置
		dp[0] = 0;
		for (int i=1;i<=n;++i)
		{
			dp[i] = NEGA_INF; //dp在这里清零；或者直接=1，就不需要虚拟餐馆了
			int j;
			for (j=i-1;j>=0;--j)
				if (m[i]-m[j] > k) //第一家足够远的餐馆
					break;
			//要考虑到，前面的餐馆都不开，这种情况也是可以的
			for (;j>=0;--j)//有了虚拟的餐馆，就不会全部距离都<=k了
				if (dp[j]+p[i] > dp[i])
					dp[i] = dp[j]+p[i];
		}
		//dp[i] = max(dp[距离超过k的餐馆] + p[i])
		int maxn = 0; //至少可以一家都不开
		for (int i=1;i<=n;++i)
			if (dp[i] > maxn)
				maxn = dp[i];
		printf("%d\n", maxn);
	}
	return 0;
}