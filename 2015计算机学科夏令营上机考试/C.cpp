#include <stdio.h>
int main(int argc, char const *argv[])
{
	int row, col;
	int arr[100][100];
	int sum;
	scanf("%d %d", &row, &col);
	for (int i=0;i<row;++i)
		for (int j=0;j<col;++j)
			scanf("%d", &arr[i][j]);
	for (int sum=0;sum<=row+col-2;++sum)
		for (int i=0;i<=sum;++i)
		{
			if (i<row && sum-i<col)
			{
				printf("%d\n", arr[i][sum-i]);
			}
		}
	//00 0110 021120 ... row-1col-1
	/*
	3 5
	1 2 3 4 5
	6 7 8 9 10
	11 12 13 14 15
	5 3
	1 2 3
	4 5 6
	7 8 9
	10 11 12
	13 14 15
	*/
	return 0;
}