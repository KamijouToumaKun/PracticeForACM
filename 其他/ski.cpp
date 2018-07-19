#include <stdio.h>
int m, n;
int dp[102][102];
int arr[102][102];
const int dir[4][2] = 
{
	{1,0},{-1,0},{0,1},{0,-1}
};
int search(int x, int y)
{
	if (dp[x][y] > 0)
		return dp[x][y];
	dp[x][y] = 1;
	int newx, newy;
	for (int i=0;i<4;++i)
	{
		newx = x + dir[i][0];
		newy = y + dir[i][1];
		if (arr[x][y] > arr[newx][newy] && search(newx, newy)+1 > dp[x][y])
			dp[x][y] = search(newx, newy)+1;
	}
	return dp[x][y];
}
int main(int argc, char const *argv[])
{
	scanf("%d%d", &m, &n);
	for (int i=1;i<=m;++i)
		for (int j=1;j<=n;++j)
		{
			scanf("%d", &arr[i][j]);
		}
	const int INF = 99999999;
	for (int i=0;i<=m+1;++i)
		for (int j=0;j<=n+1;++j)
			if (i==0||i==m+1||j==0||j==n+1)
				arr[i][j] = INF;
	int maxn = 0;
	for (int i=1;i<=m;++i)
		for (int j=1;j<=n;++j)
		{
			if (maxn < search(i, j))
				maxn = search(i, j);
		}
	printf("%d", maxn);
	return 0;
}