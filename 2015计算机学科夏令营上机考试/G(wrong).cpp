#include <queue>
#include <stdio.h>
using namespace std;
char map[77][77];
int vis[77][77]; //不在地图里面标'#'，而是专门用一个数组来标示是否走过；否则会出错！
int dir[4][2] =
{
	{1, 0}, {-1, 0}, {0, 1},{0, -1},
};
struct RC
{
	int r;
	int c;
	int step;
	int dir;
	RC() {}
	RC(int _r, int _c, int _step, int _dir)
	{
		r = _r;
		c = _c;
		step = _step;
		dir = _dir;
	}
};

int r, c;

void search(int sr, int sc, int er, int ec, int t)
{
	for (int i=0;i<=r+1;++i)
		for (int j=0;j<=c+1;++j)
			vis[i][j] = 0; //每一次广搜前都重置vis。注意，本题的周围一圈是可以走的！
	queue<RC> q;
	q.push(RC(sr, sc, 0, -1));
	vis[sr][sc] = 1;
	RC now, next;
	while (!q.empty())
	{
		now = q.front();
		q.pop();
		for (int i=0;i<4;++i)
		{
			next.r = now.r + dir[i][0];
			next.c = now.c + dir[i][1]; //这里需要更多的点进栈
			if (next.r>=0 && next.r<=r+1 && next.c>=0 && next.c<=c+1
				&& vis[next.r][next.c] == 0) //最外面一圈是空而不是墙，于是得加判断了
			{
				next.dir = i;
				next.step = now.step;
				if (next.dir != now.dir)
					next.step ++; //如果方向相同，拐弯数量不加
				if (next.r == er && next.c == ec) //必须在这里判断终点
				{
					printf("Pair %d: %d segments.\n", t, next.step);
					return;
				}
				else if (map[next.r][next.c] != 'X') //因为终点也是个X
				{
					vis[next.r][next.c] = 1; //为什么封路必须在这里？？？
					q.push(next); //不是浅拷贝，没问题；如果每次push一个新的RC，内存会爆吗？
				}
			}
		}
	}
	printf("Pair %d: impossible.\n", t);
	return;
}
void readpair()
{
	int t = 0;
	int sc, sr, ec, er;
	while (scanf("%d %d %d %d", &sc, &sr, &ec, &er), sc||sr||ec||er) //先列再行
	{
		t ++;
		search(sr, sc, er, ec, t); //每一次都要重置vis数组
	}
}
int main(int argc, char const *argv[])
{
	int k = 0;
	while (scanf("%d %d", &c, &r), r||c) //先行再列
	{
		k ++;
		for (int i=0;i<=r+1;++i)
			for (int j=0;j<=c+1;++j)
				if (i==0 || i==r+1 || j==0 || j==c+1)
					map[i][j] = ' '; //外面一圈是空
		for (int i=1;i<=r;++i)
		{
			getchar(); //跳过换行：r c之后就有冗余的换行符了！
			for (int j=1;j<=c;++j)
			{
				map[i][j] = getchar();//X for no, ' ' for yes
			}
		}
		printf("Board #%d:\n", k);
		readpair();
		printf("\n"); //每一个样例后面要输出一个空行
	}
	return 0;
}