/*岛上一共有n个人，0 <= N <= 5000。
从person 2到person n依次说话，一共说n-1句话。
Person i说的话一定是以下2种之一：
1、x是好/坏人
2、如果x是好/坏人，则y是好/坏人
好人一定说真话，坏人可能说真话可能说假话
x属于max{i-K,1} to (i-1).（1 <= k <= 10）

暴搜肯定超时了。
int count = 0;
void dfs(int index) {
	if (index == n+1) {
		检验各个人说的是否自洽
		如果自洽，更新count。
		return;
	}
	if (n+1-index <= count) { //就算剩下的人全是好人也不是最优解
		return;
	}
	person[index] = true;
	dfs(index+1);
	person[index] = false;
}
main() {
	输入n-1句话
	dfs(1);
	printf("%d", count);
}

考虑到k很小，应该是一个状态压缩的动规。
设count[i][s]表示给定末k个人的好坏状态为s(0 <= s < 1024)下、1～i中好人最多可能的个数
count[i][s1s2...sk] =
1、如果sk=0
	=max{count[i-1][0s1s2...sk-1]，count[i-1][1s1s2...sk-1]}
2、如果sk=1。count自带1.
	i的话对s0s1s2...sk-1中的某些值有要求。
	1）i的话只涉及s1～sk-1
	如果跟当前的s1s2...sk-1矛盾的话，=-1。
	否则，=max{count[i-1][0s1s2...sk-1]，count[i-1][1s1s2...sk-1]}
	2）涉及s0。假如说s0=1
	=count[i-1][1s1s2...sk-1]
*/
/*
样例用如下的方式表示：
int n = 7, k = 4;
int stmt[5001][5] = {
	{-1},
	{-1},
	{1,1,0}, //Person 2: Person 1 is a bad guy.
	//1表示陈述句，1表示Person1，0表示bad。
	{1,2,0}, //Person 3: Person 2 is a bad guy.
	{0,3,1,1,0}, //Person 4: If person 3 is a good guy, person 1 is a bad guy.
	//0表示条件句，3表示Person3，1表示good，1表示person1，0表示bad。
	{1,2,0},
	{0,4,1,2,0},
	{1,6,0},
};*/
#include <string.h>
#include <stdio.h>
int n = 7, k = 2;
int stmt[5001][5];
int count[5001][1024] = {0};
inline int max(int x, int y) {
	if (x > y) return x;
	else return y;
}
void dp(int i, int s) {
	if (i == 1) {//第1个人没有说话
		if ((s & 1) == 0) {
			count[i][s] = 0;
		} else {
			count[i][s] = 1;
		}
		return;
	}
	if ((s & 1) == 0) {//如果sk=0，即i是坏人，则不用考虑i说的话
		count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
	} else {//若i是好人，则要考虑i所说的话了
		if (stmt[i][0] == 1) {//是肯定句
			int person = stmt[i][1];
			int good = stmt[i][2];
			if (i-person < k) {
				if (((s>>1)>>(i-person-1) & 1) == good) {//如果没有矛盾
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {
					count[i][s] = -2;
				}
			} else {
				count[i][s] = count[i-1][(good<<(k-1))|(s>>1)];
			}
		} else {//是条件句
			int person1 = stmt[i][1];
			int good1 = stmt[i][2];
			int person2 = stmt[i][3];
			int good2 = stmt[i][4];
			if (i-person1 < k && i-person2 < k) {
				if (((s>>1)>>(i-person1-1) & 1) != good1 //如果条件错误
				|| ((s>>1)>>(i-person2-1) & 1) == good2) {//或结论成立，则没有矛盾
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {
					count[i][s] = -2;
				}
			} else if (i-person1 == k && i-person2 < k) {
				if (((s>>1)>>(i-person2-1) & 1) == good2) {//如果结论成立，则没有矛盾
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {//只能依靠条件错误
					count[i][s] = count[i-1][((1-good1)<<(k-1))|(s>>1)];
				}
			} else if (i-person1 < k && i-person2 == k) {
				if (((s>>1)>>(i-person1-1) & 1) != good1) {//如果条件错误，则没有矛盾
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {//只能依靠结论成立
					count[i][s] = count[i-1][(good2<<(k-1))|(s>>1)];
				}
			} else {
				if (good1 == good2) {//没有矛盾
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {//绝对矛盾
					count[i][s] = -2;
				}
			}
		}
		count[i][s] ++;//加上i本人是好人。
	}
}
void input() {
	char s[1000];
	scanf("%d %d", &n, &k);
	for (int i=2;i<=n;++i) {
		scanf("%*s %*s %s", s);
		if (strcmp(s, "If") != 0) {//是陈述句
			stmt[i][0] = 1;
			scanf("%d %*s %*s %s %*s", &stmt[i][1], s);
			if (strcmp(s, "good") == 0) {
				stmt[i][2] = 1;
			} else {
				stmt[i][2] = 0;
			}
		} else {//是条件句
			stmt[i][0] = 0;
			scanf("%*s %d %*s %*s %s %*s", &stmt[i][1], s);
			if (strcmp(s, "good") == 0) {
				stmt[i][2] = 1;
			} else {
				stmt[i][2] = 0;
			}
			scanf("%*s %d %*s %*s %s %*s", &stmt[i][3], s);
			if (strcmp(s, "good") == 0) {
				stmt[i][4] = 1;
			} else {
				stmt[i][4] = 0;
			}
		}
	}
}
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		input();
		for (int i=1;i<=n;++i)
			for (int s=0;s<(1<<k);++s)
				dp(i, s);
		int maxn = 0;
		for (int s=0;s<(1<<k);++s)
			if (count[n][s] > maxn) {
				maxn = count[n][s];
			}
		printf("%d\n", maxn);
	}
	return 0;
}