#include <stdio.h>
const int INF = 1<<28;
int m, n, k;
int minn;
char map[200][200];
int minLen[200][200][11];//是一个加强版的vis数组
bool inboard(int x, int y)
{
	return x>=0 && x<m && y>=0 && y<n;
}
void search(int x, int y, int k_now, int len_now)//作为参数，就不需要恢复其原状态
{
	if (inboard(x, y) == false)//检查范围
		return;
	++len_now;
	if (len_now >= minn) //剪枝1
		return;
	if (map[x][y] == '#')//过路费
	{
		if (k_now > 0)
			-- k_now;
		else
			return;
	}
	for (int i=k_now;i<=k;++i)
		if (minLen[x][y][i] <= len_now) //剪枝2
			return;
	minLen[x][y][k_now] = len_now;
	if (map[x][y] == '+') //判断终点
	{
		if (len_now < minn)
			minn = len_now;
	}
	else
	{
		search(x-1, y, k_now, len_now);
		search(x+1, y, k_now, len_now);
		search(x, y-1, k_now, len_now);
		search(x, y+1, k_now, len_now);
	}
}
int main(int argc, char const *argv[])
{
	int sx, sy;
	scanf("%d%d%d", &m, &n, &k);
	minn = INF;
	for (int i=0;i<m;++i)
		for (int j=0;j<n;++j)
			for (int k_now=0;k_now<=k;++k_now)
				minLen[i][j][k_now] = INF;
	for (int i=0;i<m;++i)
	{
		getchar();
		for (int j=0;j<n;++j)
		{
			map[i][j] = getchar();
			if (map[i][j] == '@')
			{
				sx = i;
				sy = j;
			}
		}
	}
	// 其中@代表鸣人，+代表佐助。*代表通路，#代表大蛇丸的手下。
	search(sx, sy, k, -1);
	if (minn != INF)
		printf("%d", minn);
	else
		printf("-1");
	return 0;
}	