#include <stdio.h>
int map[102][102];
int main(int argc, char const *argv[])
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			scanf("%d", &map[i][j]);
	int sum = 0;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (map[i][j] == 1)
			{
				sum += !map[i-1][j] + !map[i+1][j] + !map[i][j-1] + !map[i][j+1];
			}
	printf("%d", sum);
	return 0;
}