/*
*题目描述：表达式求值（递归算法）
	   表达式：1、可以是一个项
			   2、也可以由多个项通过加减构成
	   项：1、项本身可以是一个因子
		   2、项也可以由若干个因子通过乘除组成
	   因子：1、因子本身可以是一个数字
			 2、因子也可以由表达式加上括号组成
*/
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
//E -> T+-T+-...
//T -> F*/F*/...
//F -> (E)|digit
int factor_value();//读入一个因子并且返回其值
int term_value();//读入一项的并且返回其值
int expression_value();//读入一个表达式并返回值
char mypeek()
{
	char c;
	while (true)
	{
		c = cin.peek();//看一个字符不取走
		if (c == ' ')
			cin.get();
		else
			break;
	}
	return c;
}
char myget()
{
	char c;
	while (true)
	{
		c = cin.get();
		if (c != ' ')
			return c;
	}
	return c;
}
int main()
{
	cout<< expression_value() <<endl;
	return 0;
}
int expression_value()//读入一个表达式并返回值
{
	int result = term_value();//求第一项的值
	while (true)
	{
		char op = mypeek();//看一个字符不取走
		if (op == '+' || op == '-')
		{
			myget();//从输入流中取走一个字符('+'或者'-')
			int value = term_value();//读入下一个项
			if (op == '+')
				result += value;
			else
				result -= value;
		}
		else
			break;
	}
	return result;
}
int term_value()//读入一项的并且返回其值
{
	int result = factor_value();//读入一个因子
	while (true)
	{
		char op = mypeek();//取出一个字符判断还有没有因子
		if (op=='*' || op=='/')
		{
			myget();
			int value = factor_value();//读入下一个因子
			if (op == '*')
				result *= value;
			else
				result /= value;
		}
		else
			break;
	}
	return result;
}
int factor_value()//读入一个因子并返回值
{
	int result = 0;
	char c = mypeek();//取出一个字符判断输入流中是一个因子还是一个整数
	if (c == '(')
	{
		myget();//去掉左括号
		result = expression_value();//读入表达式
		myget();//去掉右括号
	}
	else//是一个数字
	{
		while (isdigit(c))//求出数字的值
		{
			result = 10 * result +c- '0';
			myget();
			c = mypeek();
		}
	}
	return result;
}