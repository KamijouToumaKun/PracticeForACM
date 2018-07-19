#include <stdio.h>
#include <iostream>
using namespace std;
int digit(int x)
{
	switch (x)
	{
		case 0: return 1111110;
		case 1: return  110000;//卧槽，前面不能写0，否则自动认为是八进制！
		case 2: return 1101101;
		case 3: return 1111001;
		case 4: return  110011;
		case 5: return 1011011;
		case 6: return 1011111;
		case 7: return 1110000;
		case 8: return 1111111;
		case 9: return 1111011;
		default: return 0;
	}
}
int a[8];
void produce(int h2, int m2, int h, int m)//前大后小
{
	a[0] = digit(h2/10);
	a[1] = digit(h2%10);
	a[2] = digit(m2/10);
	a[3] = digit(m2%10);
	a[4] = digit(h/10);
	a[5] = digit(h%10);
	a[6] = digit(m/10);
	a[7] = digit(m%10);
}
int show[8];
void translate(char* s0, char *s1, char *s2)
{
	for (int t=0;t<8;++t)
	{
		int offset = t>=4?1:0; //之前忘记了中间存在空格
		show[t] = 0;
		for (int i=3*t;i<3*(t+1);++i)
			if (s0[i+offset] == '_')
				show[t] += 1000000;
		for (int i=3*t;i<3*(t+1);++i)
			if (s1[i+offset] == '|')
				if (i % 3 == 0)
					show[t] += 10;
				else
					show[t] += 100000;
			else if (s1[i+offset] == '_')
				show[t] += 1;
		for (int i=3*t;i<3*(t+1);++i)
			if (s2[i+offset] == '|')
				if (i % 3 == 0)
					show[t] += 100;
				else
					show[t] += 10000;
			else if (s2[i+offset] == '_')
				show[t] += 1000;
	}
	// for (int i=0;i<8;++i) //debug
	// 	printf("%d ", show[i]);
	// printf("\n");
}
bool check()
{
	for (int t=0;t<8;++t)
		for (int mi=1;mi<=1000000;mi*=10)
			if (show[t]/mi %2 == 1 && a[t]/mi %2 == 0)
			{
				return false;
			}// 若show不是a的子集
	return true;
}
void test()
{
	int res[4] = {-1};
	char s[3][30];//3*8+1：中间还有1个空格；+1终止
	cin.getline(s[0], 30, '\n');
	cin.getline(s[1], 30, '\n');
	cin.getline(s[2], 30, '\n');
	// printf("xxx\n%s\n%s\n%s\nxxx\n", s[0],s[1],s[2]); debug
	translate(s[0], s[1], s[2]);//get show
	for (int h=0;h<24;++h) //暴力穷举
		for (int m=0;m<60;++m)
		{
			int m2 = m+15, h2 = h;
			if (m2>=60)
			{
				m2 -= 60;
				h2++;
			}
			if (h2>=24)
				h2-=24;
			produce(h2, m2, h, m);//get a
			if (check()) //check show是不是a的子集
			{
				if (res[0] != -1)//多种答案
				{
					printf("Not Sure\n");
					return;
				}
				else
				{
					res[0] = h2/10;
					res[1] = h2%10;
					res[2] = m2/10;
					res[3] = m2%10;
				}
			}
		}
	if (res[0] == -1)//无解
		printf("Not sure\n");
	else
		printf("%d%d%d%d\n", res[0], res[1], res[2], res[3]);
	return;
}
int main(int argc, char const *argv[])
{
	int n;
	scanf("%d", &n);
	getchar(); //之前忘记了把这个换行符去掉
	while (n--)
	{
		test();
	}
	return 0;
}