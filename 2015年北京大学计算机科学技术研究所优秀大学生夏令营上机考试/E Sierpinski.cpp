#include <string.h>
#include <stdio.h>
char s[11][1<<10][1<<11];
int main(int argc, char const *argv[])
{
	// n=1: 2^1行，2^2列
	// n=2: 2^2行，2^3列
	// n-1: 2^(n-1), 2^n
	// n: 2^n行，2^(n+1)列
	strcpy(s[1][0], " /\\ ");
	strcpy(s[1][1], "/__\\");
	for (int n=2;n<=10;++n)
		for (int i=0;i<(1<<n);++i)
			for (int j=0;j<(1<<(n+1));++j)
			{
				if (i < (1<<(n-1)))//上半段
				{
					if (j < (1<<(n-1)) || j >= 3*(1<<(n-1)))//两边的空格
						s[n][i][j] = ' ';
					else//中间是s[n-1]
						s[n][i][j] = s[n-1][i][j-(1<<(n-1))];
				}
				else//两个s[n-1]
				{
					s[n][i][j] = s[n-1][i-(1<<(n-1))][j%(1<<n)];
				}
			}
	int n;
	while (scanf("%d", &n), n)
	{
		for (int i=0;i<(1<<n);++i)
		{
			for (int j=0;j<(1<<(n+1));++j)
				printf("%c", s[n][i][j]);
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}