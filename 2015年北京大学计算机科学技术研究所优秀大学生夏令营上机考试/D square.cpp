#include <stdio.h>
int arr[40][40];
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n); //(2n-1) ^2
	int lastx = 1, lasty = n;
	int x, y;
	arr[lastx][lasty] = 1;
	for (int i=2;i<=(2*n-1)*(2*n-1);++i)
	{
		if (lastx == 1 && lasty == 2*n-1)//下一行
		{
			x = lastx+1;
			y = lasty;
		}
		else if (lastx == 1)
		{
			x = 2*n-1;
			y = lasty+1;
		}
		else if (lasty == 2*n-1)
		{
			x = lastx-1;
			y = 1;
		}
		else
		{
			x = lastx-1;
			y = lasty+1;
		}
		if (arr[x][y] != 0)//下一行
		{
			x = lastx+1;
			y = lasty;
		}
		arr[x][y] = i;
		lastx = x;
		lasty = y;
	}
	for (int i=1;i<=2*n-1;++i)
	{
		for (int j=1;j<=2*n-1;++j)
		{
			if (j != 1)
				printf(" ");
			printf("%d", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}