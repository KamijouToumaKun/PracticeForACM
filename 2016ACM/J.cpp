/*输出序列能否对应一颗二叉树的中序遍历
特别的，#表示空树

#v#v#v##v#
如果出现一个v，它的右边（不一定相邻）一定还有#，因为还要遍历右子树
如果最左边是#、最右边是#，才有可能。
情况1: #|v|#v#v##v#
	递归判断左边是不是可以、右边是不是可以
情况2: #v#|v|#v##v#
情况3: #v#v#|v|##v#
情况4: #v#v#v##|v|#

我去……归纳假设，所有n-1层的树都是#v#v#v#v#这样的交叉的：
	v		v		v		v
	/\		/\		/\		/\
	# #		# v		v #		v v
	#v#		#v(#v#) (#v#)v# (#v#)v(#v#)
这么想太简单了？但是是对的！
*/
#include <stdio.h>
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	char s[1000][10];
	while (T--) {
		int n;
		scanf("%d", &n);
		int i;
		for (i=0;i<n;++i) {
			scanf("%s", s[i]);
		} //总得把内容读完
		if (n % 2 == 0) {
			printf("No\n");
		} else {
			for (i=0;i<n;++i) {
				if ((i%2==0 && s[i][0]!='#') || (i%2==1 && s[i][0]=='#')) {
					printf("No\n");
					break;
				}
			}
			if (i == n) {
				printf("Yes\n");
			}
		}
	}
	return 0;
}