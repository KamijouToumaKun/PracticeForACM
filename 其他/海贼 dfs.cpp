#include <stdio.h>
int n;
int adj[16][16];
int minn;
int minLen[16][1<<16];
void search(int last, int now, int status, int len_now)
{
	if ((status & (1<<now)) != 0)//检查越界与重复，这里不会越界
		return;
	status |= (1<<now); //更新vis
	if (now == n-1 && status != (1<<n)-1)
		return;

	len_now += adj[last][now];//累加len
	if (len_now >= minn)//剪枝1
		return;
	//检查过路费，这里没有
	if (len_now >= minLen[now][status])//剪枝2，不然会超时
		return;
	minLen[now][status] = len_now;//更新
	if (now == n-1) //判断终点
	{
		if (len_now < minn)
			minn = len_now;
	}
	else
	{
		for (int i=0;i<n;++i)
			search(now, i, status, len_now);
	}
}
int main(int argc, char const *argv[])
{
	scanf("%d", &n);
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
			scanf("%d", &adj[i][j]);
	const int INF = 1<<28;
	minn = INF;
	for (int i=0;i<n;++i)
		for (int j=0;j<(1<<n);++j)
			minLen[i][j] = INF;
	search(0, 0, 0, 0);
	printf("%d", minn);
	return 0;
}