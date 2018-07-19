#include <string.h>
#include <stdio.h>
// DBACEGF ABC'D'EFG
// BAC A'B'C			EGF 'E'FG
char pre[10000], mid[10000];
void search(int prebeg, int midbeg, int len)
{
	if (len == 0) //叶节点
		return;
	for (int i=0;i<len;++i)
	{
		if (mid[midbeg+i] == pre[prebeg]) //在mid中找pre
		{
			search(prebeg+1, midbeg, i); //递归处理前半
			search(prebeg+1+i, midbeg+i+1, len-i-1); //递归处理后半
			putchar(pre[prebeg]); //输出中间
		}
	}
}
int main(int argc, char const *argv[])
{
	while (scanf("%s %s", pre, mid) != -1)
	{
		search(0, 0, strlen(pre));
		printf("\n");
	}
	return 0;
}