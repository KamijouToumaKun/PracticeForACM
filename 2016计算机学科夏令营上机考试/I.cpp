/*a1 a2 ... an n<=1000
b1 b2 ... bn
5 -4 -2 -1

局部得不到最优解。4 2 5: 4+2-5，而不是4-2-5

每一位最大是6，1000位最大是6000；dp？∑6i from 0 to 1000，会超时吗

就算不会超时：
5	1	-1	-2
			0
		3	2
			4
	9	7	6
			8
		11	10
			12
最后拿到一个绝对值最小的sum。如果sum可正可负，只取一个。
dp[i, sum]表示为了达到sum，1～i块最少要翻动多少次
sum-num[i]如果在i-1的列表中间，dp[i, sum] = dp[i-1, sum-num[i]]
sum+num[i]如果在i-1的列表中间，dp[i, sum] = dp[i-1, sum+num[i]] + 1（第i位必须翻转）
这是一个背包！
如果最后取反（用n减）可以更小，则取反。
*/
#include <stdlib.h>
#include <stdio.h>
const int BOTTOM = 6000; //避免index为负数
short num[1001], able[1001][12001], dp[1001][12001];//内存还不会爆炸，但是可以用滚动数组啊
int main(int argc, char const *argv[])
{
	int n, a, b;
	scanf("%d", &n);
	for (int i=1;i<=n;++i)
	{
		scanf("%d%d", &a, &b);
		num[i] = a-b;
	}
	able[0][BOTTOM] = 1;
	for (int i=1;i<=n;++i)
		for (int r=-6*i;r<=6*i;++r)
			if (able[i-1][BOTTOM+r] == 1)
			{
				able[i][BOTTOM+r+num[i]] = 1;
				able[i][BOTTOM+r-num[i]] = 1;
			}
	int minn = 10000;
	for (int r=-6*n;r<=6*n;++r)
		if (able[n][BOTTOM+r] == 1 && abs(r) < minn)
			minn = abs(r); //找到能得到的最小值。minn一定有一个正的和负的；只取正的
	dp[0][BOTTOM] = 0; //回溯最小的翻转方案
	for (int i=1;i<=n;++i)
		for (int r=-6*i;r<=6*i;++r)
		{
			dp[i][BOTTOM+r] = 10000;
			if (able[i-1][BOTTOM+r-num[i]] == 1 && dp[i-1][BOTTOM+r-num[i]] < dp[i][BOTTOM+r])
			{
				dp[i][BOTTOM+r] = dp[i-1][BOTTOM+r-num[i]];
			}
			if (able[i-1][BOTTOM+r+num[i]] == 1 && dp[i-1][BOTTOM+r+num[i]]+1 < dp[i][BOTTOM+r])
			{
				dp[i][BOTTOM+r] = dp[i-1][BOTTOM+r+num[i]]+1;
			}
		}
	int ans = dp[n][BOTTOM+minn];
	if (n-ans < ans)
		printf("%d", n-ans);
	else
		printf("%d", ans);
	return 0;
}