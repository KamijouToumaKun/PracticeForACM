/*
序列最长为1001，第一位为1～9，后面为0～9
s0s1...sk 能到tk+1糖
rule[s0]：材料到t1糖
rule[s1]：t1糖到t2糖
...
rule[sk]：tk糖到tk+1糖

s0s1...sk-1 能到tk糖
机器sk tk糖能到tk+1糖
count[k][b]表示长度为k+1、末端为b的序列
则count[k][b] += ∑foreach s: count[k-1][a]（当s使得a到b）
从count[k-1][a]对应的序列m0m1...mk-1变到了m0m1...mk-1m

空间复杂度logB*C<=1000*1000

但是有要求：对机器的编号序列有要求：只考虑从A到B
10～129
9不在这个区间里，但是90在！

我的想法：划分区间
注意，从这里开始，我的思路异常混乱了……
举一个例子，58～32197 =
58～32197
= 58～59 + 60～32189 + 32190～32197
60～32189
= 60～99 + 100～32099 + 32100～32189（321 + 0～8 + 0～9）
100～32099
= 100～999 + 1000～31999 + 32000～32099（32 + 0～0 + 00～99）
1000～31999
= 1000～9999 + 10000～29999 + 30000～31999（3 + 0～1 + 000～999）
10000～29999

010～129
= 无 + 010～099 + 100～129
左端找到最后一位非0的，把它变成9；之后每一位都变成9；再+1
右端找到最后一位非9的，把它变成0；之后每一位都变成0；再-1

超时……
*/
#define M 20160508
#include <string.h>
#include <stdio.h>
int rule[10010][3];
int C;//颜色种数
int N1, N2;
struct vec {
	int count[1001];
	vec() {
		for (int i=1;i<=1000;++i) {
			count[i] = 0;
		}
	}
	void vecadd(vec o) {
		for (int i=1;i<=C;++i) {
			count[i] += o.count[i];
			count[i] %= M;
		}
	}
	void output() {
		for (int i=1;i<=C;++i) {
			printf("%d\n", count[i]);
		}
	}
};
int count[1001][1001];
vec stat(char pre[], int lenpre, char rangebeg, char rangeend, int lensuf) {
	//前导0已消去
	//0～i-1 i i+1～i+lensuf；lensuf=lenbeg-i-1；总共0～i+lensuf = 0～lenbeg-1
	//0 1～i-1
	//时间复杂度：O(lenpre+lensuf)*O(s1+s2)
	int beg, machine, end;
	for (int i=0;i<=lenpre+lensuf;++i)
		for (int t=1;t<=C;++t)
			count[i][t] = 0; //清0
	// i = 0;
	for (int s=0;s<N1;++s) {
		// beg = rule[s][0]; = 0
		machine = rule[s][1];
		if (machine == pre[0]-'0') {//确认机器的类型
			end = rule[s][2];
			count[0][end] ++;
		}
	}
	if (lensuf >= 0) {//还能进行剩下的步骤
		for (int i=1;i<lenpre;++i) {
			for (int s=N1;s<N1+N2;++s) {
				beg = rule[s][0];
				machine = rule[s][1];
				if (machine == pre[i]-'0') {//确认机器的类型
					end = rule[s][2];
					count[i][end] += count[i-1][beg];
					count[i][end] %= M;
				}
			}
		}
		//i = lenpre <= lenpre+lensuf;
		for (int s=N1;s<N1+N2;++s) {
			beg = rule[s][0];
			machine = rule[s][1];
			if (machine >= rangebeg-'0' && machine <= rangeend-'0') {//确认机器的类型
				end = rule[s][2];
				count[lenpre][end] += count[lenpre-1][beg];
				count[lenpre][end] %= M;
			}
		}
		for (int i=lenpre+1;i<=lenpre+lensuf;++i) {
			for (int s=N1;s<N1+N2;++s) {
				beg = rule[s][0];
				// machine = rule[s][1];
				// 不用确认机器的类型
				end = rule[s][2];
				count[i][end] += count[i-1][beg];
				count[i][end] %= M;
			}
		}
	}

	vec ans;
	for (int t=1;t<=C;++t) {
		ans.count[t] = count[lenpre+lensuf][t];
	}
	return ans;
}
bool lt(char a[], char b[]) {
	for (int i=0;i<strlen(b);++i) {
		if (a[i] < b[i]) return true;
		else if (a[i] > b[i]) return false;
	}
	return false;
}
vec div(char beg[], char end[]) {
	bool flagbeg = false, flagend = false;

	vec ans; //统计结果
	const int lenbeg = strlen(beg);
	const int lenend = strlen(end);
	int i, j;
	for (i=lenbeg-1;i>=0;--i)
		if (beg[i] != '0')
			break;
	if (i <= 0) {//i是最高位：进位溢出，例如beg=20000
		//中间没有需要统计的
		//beg 20000 -> newbeg 20000
		flagbeg = true;
	} else {//例如beg=21000；或者beg=010
		for (j=0;j<lenbeg;++j)
			if (beg[j] != '0')
				break;//消除前导0
		if (i == j) {//类似于10～99这种
			for (;beg[i]<='9';++beg[i]) {//把特殊的第一位单独划出来
				//lenend >= 1. lenend=1比较特殊，在stat中特判
				ans.vecadd(stat(beg+i, 1, '0', '9', lenend-i-1-1));
				//统计30000～39999
				//统计40000～49999...
			}
		} else {
			ans.vecadd(stat(beg+j, i-j, beg[i], '9', lenbeg-j-i-1));//统计21000～29999
				//统计（前缀=beg[0~i-1]，beg[i]～9，后缀长度=lenbeg-i，每一位从0～9）) ;
		}
		beg[i] = '0';
		beg[i-1] ++;
		for (j=i-1;;--j) {
			if (beg[j] > '9') {
				beg[j] -= 10;
				beg[j-1] ++; //因为高位有补0，所以不会溢出
			} else {
				break;
			}
		} //beg 21000 -> newbeg 30000
	}

	for (i=lenend-1;i>=0;--i)
		if (end[i] != '9')
			break;
	if (i <= 0) {//i是最高位。例如end=59999
		//中间没有需要统计的end
		//end 59999 -> newend 59999
		flagend = true;
	} else {//例如end=58999。这时i>=1；或者end=129
		//不会有前导0
		ans.vecadd(stat(end, i, '0', end[i], lenend-i-1));//统计50000～58999；统计100～129
			//统计（前缀=end[0~i-1]，0～end[i]，后缀长度=lenend-i每一位从0～9）);
		end[i] = '9';
		end[i-1] --;
		for (j=i-1;;--j) {
			if (end[j] < '0') {
				end[j] += 10;
				end[j-1] --; //不会溢出
			} else {
				break;
			}
		} //end 58999 -> newend 49999
	}
	if (flagbeg && flagend) {//都没有更新：说明已经到了递归的头：要直接计算30000～49999了
		for (i=0;i<lenend;++i)
			if (beg[i] != '0')
				break;//找到最高位，跳过前导0
		for (;beg[i]<=end[i];++beg[i]) {//把特殊的第一位单独划出来
			//lenend >= 1. lenend=1比较特殊，在stat中特判
			ans.vecadd(stat(beg+i, 1, '0', '9', lenend-i-1-1));
			//统计30000～39999
			//统计40000～49999...
		}
	} else {
		if (lt(beg, end)) {//排除100～099这种
			for (i=0;i<lenend;++i)
				if (end[i] != '0')
					break;
			ans.vecadd(div(beg+i, end+i));//消除多余的前导0，统计30000～49999
		}
	}
	return ans;
}
int main(int argc, char const *argv[]) {
	int T;
	scanf("%d", &T);
	while (T--) {
		char A0[1001], B[1001]; //序列的起点和终点
		scanf("%s %s", A0, B);
		int len = strlen(B);
		char A[1001]={0};
		for (int i=strlen(A0)-1,j=strlen(B)-1;j>=0;--i,--j) {
			if (i >= 0) A[j] = A0[i]; //数位对齐
			else A[j] = '0';
		}
		scanf("%d", &C);//输入颜色种数
		scanf("%d", &N1);
		for (int s=0;s<N1;++s) {//输入各条规则
			scanf("%d %d", &rule[s][1], &rule[s][2]); //machine end
			rule[s][0] = 0; //beg = 0;
		}
		scanf("%d", &N2);
		for (int s=N1;s<N1+N2;++s) {
			scanf("%d %d %d", &rule[s][0], &rule[s][1], &rule[s][2]); //beg machine end
		}
		div(A, B).output();
	}
	return 0;
}