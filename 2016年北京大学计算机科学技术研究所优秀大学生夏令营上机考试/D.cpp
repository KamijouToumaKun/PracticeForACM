#include <stdio.h>
int dayformonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
bool runnian(int year)
{
	return (year%100!=0 && year%4==0) || (year%400==0);
}
int main(int argc, char const *argv[])
{
	int year, month;
	// scanf("%d%d", &year, &month);
	year = 2006, month = 5;
	int d = 1;
	for (int i=1900;i<year;++i)
		if (runnian(i))
			d = (d+366)%7;
		else
			d = (d+365)%7;
	for (int i=1;i<month;++i)
	{
		if (runnian(year) && i == 2)
			d = (d+29)%7;
		else
			d = (d+dayformonth[i])%7;
	}
	printf("Sun Mon Tue Wed Thu Fri Sat\n");
	int count = 0;
	for (int i=0;i<d;++i)
	{
		count ++;
		printf("    ");
	}
	if (runnian(year) && month==2)
		dayformonth[month] ++;
	for (int i=1;i<=dayformonth[month];++i)
	{
		if (i <= 9)
			printf("  %d", i);
// printf("%*d\n", 宽度, i);用空格补充
// printf("%0*d\n\n", 宽度, i);用0补充
// %3d 表示输出3位整型数, 不够3位右对齐。
// %9.2f 表示输出场宽为9的浮点数, 其中小数位为2, 整数位为6, 小数点占一位, 不够9位右对齐。
// %8s 表示输出8个字符的字符串, 不够8个字符右对齐。 
		else
			printf(" %d", i);
		count ++;
		if (i != dayformonth[month] && count%7 != 0)
			printf(" ");
		else if (count%7==0)
			printf("\n");
	}
	return 0;
}