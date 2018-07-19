#include <stdio.h>
int len[51];
int sum;
int goal;
int min(int x, int y)
{
	return x<y?x:y;
}
bool search(int goal_now, int last, int achieve)
{
	if (goal_now == 0)
	{
		achieve++;
		if (achieve < sum/goal)
			return search(goal, 51, achieve);//这里需要剪枝：新的一轮必须先用上最长的一根
		else
			return true;
	}
	if (goal_now<=50 && len[goal_now]>0)//剪枝2
	{
		return search(0, goal_now, achieve);
	}
	bool flag;
	for (int i=min(goal_now,last);i>=1;--i)
	{
		if (len[i] > 0)
		{
			len[i] --;
			flag = search(goal_now-i, i, achieve);
			len[i] ++;
			if (flag == true)
				return true;
		}
	}
	return false;
}
void test(int n)
{
	int maxn = 0, num;
	for (int i=1;i<=50;++i)
		len[i] = 0;
	sum = 0;
	for (int i=0;i<n;++i)
	{
		scanf("%d", &num);
		len[num] ++;
		if (num > maxn)
			maxn = num;
		sum += num;
	}
	for (int i=maxn;i<=sum;++i)
	{
		if (sum % i == 0)
		{
			goal = i;
			if (search(i, 51, 0) == true)
			{
				printf("%d\n", i);
				return;
			}
		}
	}
}
int main(int argc, char const *argv[])
{
	int n;
	while (scanf("%d", &n), n)
	{
		test(n);
	}
	return 0;
}