/*dp[t, tired] = max(run[t]+dp[t+1, tired+1], dp[t+tired, 0])

dp[N+1, tired] = -INF(tired>0), 0(tired==0)

get dp[0, 0]
*/
#include <stdio.h>
int dp[10001][501];
const int NEGA_INF = -(1<<30);
int add(int x) //如果现在tired=0，也至少要休息一分钟
{
	return x==0 ? 1 : x;
}
int main(int argc, char const *argv[])
{
	int n, m, run[10001];
	scanf("%d%d", &n, &m);
	for (int t=1;t<=n;++t)
		scanf("%d", &run[t]);
	dp[n+1][0] = 0;
	for (int tired=1;tired<=m;++tired) //这里要是m+1
		dp[n+1][tired] = NEGA_INF;
	for (int t=n;t>=1;--t)
		for (int tired=0;tired<=m;++tired)
		{
			dp[t][tired] = NEGA_INF;
			if (tired+1<=m && run[t]+dp[t+1][tired+1] > dp[t][tired])//接着跑
				dp[t][tired] = run[t]+dp[t+1][tired+1];
			if (t+add(tired)<=n+1 && dp[t+add(tired)][0] > dp[t][tired])
				dp[t][tired] = dp[t+add(tired)][0];
		}
	printf("%d", dp[1][0]);
	return 0;
}