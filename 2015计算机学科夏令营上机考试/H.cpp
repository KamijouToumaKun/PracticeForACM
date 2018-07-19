#include <string.h>
#include <stdio.h>
char s[26][27]; //这棵二叉树可能是一条链，所以最多26层
struct range
{
	int beg[26];
	int end[26];
};
void search(int level, range now)
{
	if (level == -1)
	{
		return;
	}
	else if (now.beg[level] == now.end[level]) //本层没有节点
	{
		search(level-1, now); //找到第一层有节点的为止
		return;
	}
	printf("%c", s[level][now.beg[level]]); //输出本节点
	range left, right;
	for (int i=level-1;i>=0;--i)
	{
		int mid;
		for (mid=now.beg[i];mid<now.end[i];++mid)
			if (s[i][mid] > s[level][now.beg[level]]) //根据本节点，对每一层进行划分
				break;
		left.beg[i] = now.beg[i];
		left.end[i] = mid; //若mid == now.beg，则左子树第一层为空
		right.beg[i] = mid;
		right.end[i] = now.end[i]; //若mid == now.end，则右子树第一层为空
	}
	search(level-1, left); //递归处理左子树
	search(level-1, right); //递归处理右子树
}
bool buildTree()
{
	int top = 0;
	scanf("%s", s[top]);
	while (s[top][0] != '*' && s[top][0] != '$')
	{
		top++;
		scanf("%s", s[top]);
	}
	range now;
	for (int i=0;i<top;++i)
	{
		now.beg[i] = 0;
		now.end[i] = strlen(s[i]);
	}
	search(top-1, now); //根节点和这棵树各层节点的位置
	printf("\n");
	if (s[top][0] == '*')
		return true;
	else
		return false;
}
int main(int argc, char const *argv[])
{
	while(buildTree())
	{
		;
	}
	return 0;
}