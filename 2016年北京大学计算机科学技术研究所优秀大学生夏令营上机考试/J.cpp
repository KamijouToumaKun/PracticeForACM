/*
9
伪满二叉树的先序遍历：a0 b0 $1 c0 d0 $1 e1 f1 $1
*/
#include <stdio.h>
struct Node
{
	char c;
	Node *left, *right;
	Node(char _c)
	{
		c = _c;
	}
};
Node* readnode() //读取伪满二叉树
{
	char s[3];
	scanf("%s", s);
	Node *node = new Node(s[0]);
	if (s[1] == '0') //如果不是叶节点
	{
		node->left = readnode(); //构建左子树
		node->right = readnode(); //构建右子树
	}
	else
	{
		node->left = node->right = NULL; //左右子树置空
	}
	return node;
}
/*void show(Node *root) //遍历 debug
{
	if (root == NULL)
		return;
	if (root->c != '$')
		printf("%c ", root->c);
	show(root->left);
	show(root->right);
	delete root;
}*/
void show(Node *root)
{
	Node *vir = new Node('$');//构建一个虚拟的根节点
	vir->left = root;
	vir->right = NULL;

	Node *q1[100] = {vir}, *q2[100]; //队列
	int top1 = 1, top2 = 0, toptmp;
	Node **p1 = q1, **p2 = q2, **ptmp;
	// 已经构建好了最初的队列1
	while (top1 != 0)
	{
		top2 = 0;
		for (int i=0;i<top1;++i)
		{
			Node *tmp = p1[i]->left; //队列1的左孩子入队
			while (tmp != NULL) //这些左孩子的右孩子、右孩子的右孩子……入队
			{
				p2[top2++] = tmp;
				tmp = tmp->right;
			}
		}
		for (int i=top1-1;i>=0;--i) //倒序输出队列1
		{
			if (p1[i]->c != '$')
			{
				if (p1[i] != root) //root前面不输出空格
					printf(" ");
				printf("%c", p1[i]->c);
			}
			delete p1[i];
		}
		ptmp = p1; //交换队列1与队列2
		p1 = p2;
		p2 = ptmp;
		toptmp = top1;
		top1 = top2;
		top2 = toptmp;
	}
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	Node *root = readnode();
	show(root);
	return 0;
}