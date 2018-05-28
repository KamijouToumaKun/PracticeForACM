/*����һ����n���ˣ�0 <= N <= 5000��
��person 2��person n����˵����һ��˵n-1�仰��
Person i˵�Ļ�һ��������2��֮һ��
1��x�Ǻ�/����
2�����x�Ǻ�/���ˣ���y�Ǻ�/����
����һ��˵�滰�����˿���˵�滰����˵�ٻ�
x����max{i-K,1} to (i-1).��1 <= k <= 10��

���ѿ϶���ʱ�ˡ�
int count = 0;
void dfs(int index) {
	if (index == n+1) {
		���������˵���Ƿ���Ǣ
		�����Ǣ������count��
		return;
	}
	if (n+1-index <= count) { //����ʣ�µ���ȫ�Ǻ���Ҳ�������Ž�
		return;
	}
	person[index] = true;
	dfs(index+1);
	person[index] = false;
}
main() {
	����n-1�仰
	dfs(1);
	printf("%d", count);
}

���ǵ�k��С��Ӧ����һ��״̬ѹ���Ķ��档
��count[i][s]��ʾ����ĩk���˵ĺû�״̬Ϊs(0 <= s < 1024)�¡�1��i�к��������ܵĸ���
count[i][s1s2...sk] =
1�����sk=0
	=max{count[i-1][0s1s2...sk-1]��count[i-1][1s1s2...sk-1]}
2�����sk=1��count�Դ�1.
	i�Ļ���s0s1s2...sk-1�е�ĳЩֵ��Ҫ��
	1��i�Ļ�ֻ�漰s1��sk-1
	�������ǰ��s1s2...sk-1ì�ܵĻ���=-1��
	����=max{count[i-1][0s1s2...sk-1]��count[i-1][1s1s2...sk-1]}
	2���漰s0������˵s0=1
	=count[i-1][1s1s2...sk-1]
*/
/*
���������µķ�ʽ��ʾ��
int n = 7, k = 4;
int stmt[5001][5] = {
	{-1},
	{-1},
	{1,1,0}, //Person 2: Person 1 is a bad guy.
	//1��ʾ�����䣬1��ʾPerson1��0��ʾbad��
	{1,2,0}, //Person 3: Person 2 is a bad guy.
	{0,3,1,1,0}, //Person 4: If person 3 is a good guy, person 1 is a bad guy.
	//0��ʾ�����䣬3��ʾPerson3��1��ʾgood��1��ʾperson1��0��ʾbad��
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
	if (i == 1) {//��1����û��˵��
		if ((s & 1) == 0) {
			count[i][s] = 0;
		} else {
			count[i][s] = 1;
		}
		return;
	}
	if ((s & 1) == 0) {//���sk=0����i�ǻ��ˣ����ÿ���i˵�Ļ�
		count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
	} else {//��i�Ǻ��ˣ���Ҫ����i��˵�Ļ���
		if (stmt[i][0] == 1) {//�ǿ϶���
			int person = stmt[i][1];
			int good = stmt[i][2];
			if (i-person < k) {
				if (((s>>1)>>(i-person-1) & 1) == good) {//���û��ì��
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {
					count[i][s] = -2;
				}
			} else {
				count[i][s] = count[i-1][(good<<(k-1))|(s>>1)];
			}
		} else {//��������
			int person1 = stmt[i][1];
			int good1 = stmt[i][2];
			int person2 = stmt[i][3];
			int good2 = stmt[i][4];
			if (i-person1 < k && i-person2 < k) {
				if (((s>>1)>>(i-person1-1) & 1) != good1 //�����������
				|| ((s>>1)>>(i-person2-1) & 1) == good2) {//����۳�������û��ì��
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {
					count[i][s] = -2;
				}
			} else if (i-person1 == k && i-person2 < k) {
				if (((s>>1)>>(i-person2-1) & 1) == good2) {//������۳�������û��ì��
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {//ֻ��������������
					count[i][s] = count[i-1][((1-good1)<<(k-1))|(s>>1)];
				}
			} else if (i-person1 < k && i-person2 == k) {
				if (((s>>1)>>(i-person1-1) & 1) != good1) {//�������������û��ì��
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {//ֻ���������۳���
					count[i][s] = count[i-1][(good2<<(k-1))|(s>>1)];
				}
			} else {
				if (good1 == good2) {//û��ì��
					count[i][s] = max(count[i-1][(s>>1)], count[i-1][(1<<(k-1))|(s>>1)]);
				} else {//����ì��
					count[i][s] = -2;
				}
			}
		}
		count[i][s] ++;//����i�����Ǻ��ˡ�
	}
}
void input() {
	char s[1000];
	scanf("%d %d", &n, &k);
	for (int i=2;i<=n;++i) {
		scanf("%*s %*s %s", s);
		if (strcmp(s, "If") != 0) {//�ǳ�����
			stmt[i][0] = 1;
			scanf("%d %*s %*s %s %*s", &stmt[i][1], s);
			if (strcmp(s, "good") == 0) {
				stmt[i][2] = 1;
			} else {
				stmt[i][2] = 0;
			}
		} else {//��������
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