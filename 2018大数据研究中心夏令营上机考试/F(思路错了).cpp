//不是并查集，是拓扑排序；思路错了。
#include <stdio.h>
int findf(int x) //1表示A<B, 2表示A>B
{
	if (f[x] == x) return x;
	int tmp = f[x];
	f[x] = findf(f[x]);
	return f[x];
}
int main(int argc, char const *argv[])
{
	int type, m;
	char s[4];
	for (int i=0;i<type;++i)
		f[i] = i;
	int blocks = 
	while (m--)
	{
		scanf("%s", s);
		a = s[0]-'A';
		b = s[2]-'A';
		int x = findf(a);
		int y = findf(b);
		if (x != y)//令x<y
		{
			f[y] = x;
			blocks--;
		}
	}
	return 0;
}