#include <queue>
#include <stdio.h>
using namespace std;
char map[32][32][32];
int vis[32][32][32]; //不在地图里面标'#'，而是专门用一个数组来标示是否走过；否则会出错！
int dir[6][3] =
{
	{1, 0, 0},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0},
	{0, 0, 1},
	{0, 0, -1},
};
struct LRC
{
	int l;
	int r;
	int c;
	int step;
	LRC() {}
	LRC(int _l, int _r, int _c, int _step)
	{
		l = _l;
		r = _r;
		c = _c;
		step = _step;
	}
};
LRC s;
void search()
{
	queue<LRC> q;
	q.push(s);
	LRC now, next;
	while (!q.empty())
	{
		now = q.front();
		if (map[now.l][now.r][now.c] == 'E')
		{
			printf("Escaped in %d minute(s).\n", now.step);
			return;
		}
		q.pop();
		// vis[now.l][now.r][now.c] = 1; 如果改成在这里封路的话，就会爆炸+超时！
		for (int i=0;i<6;++i)
		{
			next.l = now.l + dir[i][0];
			next.r = now.r + dir[i][1];
			next.c = now.c + dir[i][2];
			next.step = now.step + 1;
			if (vis[next.l][next.r][next.c]==0 && map[next.l][next.r][next.c]!='#')
			{
				vis[next.l][next.r][next.c] = 1; //为什么封路必须在这里？？？
				q.push(next); //不是浅拷贝，没问题；如果每次push一个新的LRC，内存会爆吗？
			}
		}
	}
	printf("Trapped!\n");
	return;
}
int main(int argc, char const *argv[])
{
	int l, r, c;
	scanf("%d %d %d", &l, &r, &c); //level row col
	while (l != 0)
	{
		for (int k=0;k<=l+1;++k)
			for (int i=0;i<=r+1;++i)
				for (int j=0;j<=c+1;++j)
					if (k==0 || k==l+1 || i==0 || i==r+1 || j==0 || j==c+1)
						map[k][i][j] = '#';
		for (int k=1;k<=l;++k)
		{
			getchar(); //跳过换行：l r c之后就有冗余的换行符了！
			for (int i=1;i<=r;++i)
			{
				for (int j=1;j<=c;++j)
				{
					map[k][i][j] = getchar();//# for no, . for yes, S, E
					vis[k][i][j] = 0;
					if (map[k][i][j] == 'S')
					{
						s.l = k;
						s.r = i;
						s.c = j;
						s.step = 0;
					}
				}
				getchar(); //跳过换行
			}
		}
		// for (int k=1;k<=l;++k) //debug
		// 	for (int i=1;i<=r;++i)
		// 	{
		// 		for (int j=1;j<=c;++j)
		// 			printf("%c", map[k][i][j]);
		// 		printf("\n");
		// 	}
		search();
		scanf("%d %d %d", &l, &r, &c); //level row col
	}
	return 0;
}