#include <stdio.h>
long long dp[1000][1000];//据说数据是500以下
long long search(int sum, int last)
{
	if (dp[sum][last] >= 0)
		return dp[sum][last];
	long long ans = 0;
	if (sum >= last)//长度为1的回文
		ans ++;
	if (sum%2 == 0 && sum >= 2*last)//长度为2的回文
		ans ++;
	//长度>2的回文
	//dp[sum, last] = dp[sum-2*last, last] + ...
	int i = last;
	while (sum - 3*i >= 0) //至少需要sum-2*last >= last
	{
		ans += search(sum-2*i, i);
		i ++;
	}
	dp[sum][last] = ans;
	return ans;
}
// ans += sum%2; //长度为1和长度为2的回文串
int main(int argc, char const *argv[])
{
	int sum;
	for (int i=0;i<1000;++i)
		for (int j=0;j<1000;++j)
			dp[i][j] = -10000;
	while (scanf("%d", &sum), sum)
	{
		printf("%d %lld\n", sum, search(sum, 1));
	}
	return 0;
}