/*
能力值跟座位号有关，跟人无关
如果他的左右两边都空着，他将获得能力值a[i]；
如果当他坐下时，左边或者右边已经有一个人在上机了，他将获得能力值b[i]；
如果当他坐下时，他的左边右边都有人在上机，他将获得能力值c[i]。

这时有N位同学们陆陆续续来到机房，一个一个按照顺序（！）坐在这排机位上。
按人的顺序选座位
*/
#include <stdio.h>
int dp[10000][4];
int a[10000], b[10000], c[10000];
inline int max(int x, int y)
{
	return x>y?x:y;
}
int main()
{
	int n;
	scanf("%d", &n);
	for (int i=0;i<n;++i)
		scanf("%d", &a[i]);
	for (int i=0;i<n;++i)
		scanf("%d", &b[i]);
	for (int i=0;i<n;++i)
		scanf("%d", &c[i]);
		
	if (n == 1)
		printf("%d", a[0]);
	else
	{
		//编号0～n-1的格子的价值只与放进格子n-1时候左右的空与不空 & 编号0～n-2的格子得分有关。
		dp[n-1][0] = a[n-1];
		// 因为放i时右边为空，所以肯定是先放i再放i+1
		dp[n-1][1] = -10000;
		// 因为放i时右边有人，所以肯定是先放i+1再放i，这不可能
		dp[n-1][2] = b[n-1];
		// 因为放i时右边为空，所以肯定是先放i再放i+1
		dp[n-1][3] = -10000;
		// 因为放i时右边有人，所以肯定是先放i+1再放i，这不可能
		for (int i=n-2;i>=0;--i)
		{
			dp[i][0] = a[i] + max(dp[i+1][2], dp[i+1][3]);
			// 放i时两边为空的i～n-1的价值 = 放i+1时左边有人的i+1～n-1的价值（右边不一定）
			// 因为放i时右边为空，所以肯定是先放i再放i+1
			dp[i][1] = b[i] + max(dp[i+1][0], dp[i+1][1]);
			// 放i时右边有人的i～n-1的价值 = 放i+1时左边为空的i+1～n-1的价值（右边不一定）
			// 因为放i时右边有人，所以肯定是先放i+1再放i
			dp[i][2] = b[i] + max(dp[i+1][2], dp[i+1][3]);
			// 放i时左边有人的i～n-1的价值 = 放i+1时左边有人的i+1～n-1的价值（右边不一定）
			// 因为放i时右边为空，所以肯定是先放i再放i+1
			dp[i][3] = c[i] + max(dp[i+1][0], dp[i+1][1]);
			// 放i时两边有人的i～n-1的价值 = 放i+1时左边为空的i+1～n-1的价值（右边不一定）
			// 因为放i时右边有人，所以肯定是先放i+1再放i
		}
		printf("%d", max(dp[0][0], dp[0][1]));
		// 求放0时左边为空的价值（右边不一定）
	}
	return 0;
}
