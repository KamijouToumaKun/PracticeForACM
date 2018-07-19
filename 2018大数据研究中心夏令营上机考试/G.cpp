#include <stdio.h>
int n, arr[1000], index[1001], vis[1001];
void check()
{
	for (int i=0;i<n;++i)
	{
		vis[arr[i]] = 1;
		//arr[i], arr[i]-1, ...中间尚未出栈的，他们的索引必须递增
		int last = arr[i], now;
		while (true)
		{
			now = last-1;
			while (now>0 && vis[now]==1)//now是第一个比last小的没有vis过的
				now --;
			if (now == 0)
				break;
			if (index[now] < index[last])
			{
				printf("No\n");
				return;
			}
			last = now;
		}
	}
	printf("Yes\n");
	return;
}
int main(int argc, char const *argv[])
{
	bool flag = false;
	while (scanf("%d", &n), n)
	{
		if (flag == false)
			flag = true;
		else
			printf("\n");
		while (scanf("%d", &arr[0]), arr[0])
		{
			if (arr[0] != 0)
			{
				index[arr[0]] = 0;//倒排索引
				for (int i=1;i<n;++i)
				{
					scanf("%d", &arr[i]);
					index[arr[i]] = i;//倒排索引
					vis[arr[i]] = 0;
				}
			}
			check();
		}
	}
	return 0;
}