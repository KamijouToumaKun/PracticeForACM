/*并查集，做出来WA了。
而且我的做法很弱，网上的解法都涉及并查集的删边算法。
看来就算改对了，也会超时。
*/
#include <stdio.h>
int pre[100001] = {0};
int pre0[100001] = {0};
int edge[200000][3];
long long count[100001];
long long count0[100001];
int find(int x) {
    int r=x;
    while(pre[r]!=r)
    	r=pre[r];//找到他的前导结点
    int i=x,j;
    while(i!=r)//路径压缩算法
    {
        j=pre[i];//记录x的前导结点
        pre[i]=r;//将i的前导结点设置为r根节点
        i=j;
    }
    return r;
}
void join(int x,int y) {
    int a=find(x);//x的根节点为a
    int b=find(y);//y的根节点为b
    if(a!=b)//如果a,b不是相同的根节点，则说明ab不是连通的
    {
        pre[a]=b;//我们将ab相连 将a的前导结点设置为b
        count[b]+=count[a];
        count[a]=0;
    }
}

int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, m, k;
		scanf("%d %d %d", &n, &m, &k);
		//n<=100000个点，m<=200000条边，k<=100000天&边一共有k种
		for (int i=0;i<m;++i) {
			scanf("%d %d %d", &edge[i][0], &edge[i][1], &edge[i][2]);//beg end type
		}
		for (int i=1;i<=n;++i) {
			pre0[i] = i;
			count[i] = 1;
		}
		for (int i=0;i<m;++i) {
			if (edge[i][2] > k) {//道路永远不会被封锁
				join(edge[i][0], edge[i][1]);
			}
		}
		for (int i=1;i<=n;++i) {
			count0[i] = count[i];
		}//并查集初始化，只统计永远不会被封锁的道路

		for (int day=1;day<=k;++day) {
			for (int i=1;i<=n;++i) {
				pre[i] = pre0[i];
				count[i] = count0[i];
			}//并查集初始化
			for (int i=0;i<m;++i) {
				if (edge[i][2] <= k && edge[i][2] != day) {//现在只分析<=k的道路
					join(edge[i][0], edge[i][1]);
				}
			}
			long long sum = 0;
			for (int i=1;i<=n;++i) {
				sum += count[i]*(count[i]-1)/2;
			}
			printf("%lld\n", sum);
		}
	}
	return 0;
}