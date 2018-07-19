#include <stdio.h>
int nn[101], mm[101], f[1001][501], hpcost[1001][501];
int main(int argc, char const *argv[])
{
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int t=1;t<=k;++t)
	{
		scanf("%d%d", &nn[t], &mm[t]);
	}
	for (int i=n;i>=0;--i)
		for (int j=m;j>=1;--j)
			if (i==0 || j==1)
			{
				f[i][j] = 0;
			}
	for (int t=1;t<=k;++t)
		for (int i=n;i>=0;--i)
			for (int j=m;j>=1;--j)
			{
				//f..[i][j] = f..[i][j]
				if (i>=nn[t] && j>mm[t])
				{
					if (f[i-nn[t]][j-mm[t]]+1 > f[i][j])
					{
						f[i][j] = f[i-nn[t]][j-mm[t]]+1;
						hpcost[i][j] = hpcost[i-nn[t]][j-mm[t]]+mm[t];
					}
					else if (f[i-nn[t]][j-mm[t]]+1 == f[i][j] && hpcost[i-nn[t]][j-mm[t]]+mm[t]<hpcost[i][j])
					{
						hpcost[i][j] = hpcost[i-nn[t]][j-mm[t]]+mm[t];
					}
				}
			}
	//index-1 -> m->?
	printf("%d %d", f[n][m], m-hpcost[n][m]);
	return 0;
}
/*
有的题目要求“恰好装满背包”时的最优解，有的题目则并没有要求必须把背包装满。
一种区别这两种问法的实现方法是在初始化的时候有所不同。
如果是第一种问法，要求恰好装满背包，那么在初始化时除了f[0]为0其它f[1..V]均设为-∞，
这样就可以保证最终得到的f[N]是一种恰好装满背包的最优解。
如果并没有要求必须把背包装满，而是只希望价格尽量大，初始化时应该将f[0..V]全部设为0。
*/