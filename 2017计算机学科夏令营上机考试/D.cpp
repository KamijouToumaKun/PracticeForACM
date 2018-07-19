// 尼玛，数据太弱，不需要剪枝！
#include <algorithm>
#include <string.h>
#include <stdio.h>
using namespace std;
void test(int target, char s[])
{
	const int len = strlen(s);
	sort(s, s+len); // 候选集排序
	int num[5][26]; // 保存幂
	for (int i=0;i<len;++i)
	{
		num[0][i] = s[i] - 'A' + 1;
		for (int t=1;t<5;++t)
			num[t][i] = num[t-1][i]*num[0][i];
	}
	int v, w, x, y, z;
	int sum = 0;
	for (int a=len-1;a>=0;--a)
	{
		sum += num[0][a];
		if (sum-num[1][len-1]-num[3][len-1] <= target && sum+num[2][len-1]+num[4][len-1] >= target) //剪枝
		for (int b=len-1;b>=0;--b)
		{
			if (b == a) continue;
			sum -= num[1][b];
			if (sum-num[3][len-1] <= target && sum+num[2][len-1]+num[4][len-1] >= target) //剪枝
			for (int c=len-1;c>=0;--c)
			{
				if (c == a || c == b) continue;
				sum += num[2][c];
				if (sum-num[3][len-1] <= target && sum+num[4][len-1] >= target) //剪枝
				for (int d=len-1;d>=0;--d)
				{
					if (d == a || d == b || d == c) continue;
					sum -= num[3][d];
					if (sum <= target && sum+num[4][len-1] >= target) //剪枝
					for (int e=len-1;e>=0;--e)
					{
						if (e == a || e == b || e == c || e == d) continue;
						sum += num[4][e];
						if (sum == target)
						{
							printf("%c%c%c%c%c\n", s[a], s[b], s[c], s[d], s[e]);
							return;
						}
						sum -= num[4][e];
					}
					sum += num[3][d];
				}
				sum -= num[2][c];
			}
			sum += num[1][b];
		}
		sum -= num[0][a];
	}
	// 根据v - w2+ x3- y4+ z5= target，来剪枝
	printf("no solution\n");
	return;
}

int main(int argc, char const *argv[])
{
	int target;
	char s[27];
	while (true)
	{
		scanf("%d %s", &target, s);
		if (target == 0 && strcmp(s, "END") == 0)
			break;
		test(target, s);
	}
	return 0;
}