#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;
//E -> T| T|E
//T -> F| F&T
//F -> !F|(E)|digit
bool factor_value();//读入一个因子并且返回其值
bool term_value();//读入一项的并且返回其值
bool expression_value();//读入一个表达式并返回值
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
	int t = 1;
	char ans = expression_value() ? 'V' : 'F';
	cout<< "Expression " << t++ << ": " << ans << endl;
	char c = myget();
	while (c == '\n')
	{
		ans = expression_value() ? 'V' : 'F';
		cout<< "Expression " << t++ << ": " << ans << endl;
		c = myget();
	}
	return 0;
}
bool expression_value()//读入一个表达式并返回值
{
	bool result = term_value();//求第一项的值
	char op = mypeek();//看一个字符不取走
	if (op == '|')
	{
		myget();//从输入流中取走一个字符('+'或者'-')
		bool value = expression_value();//读入下一个项
		result = result || value;
	}
	return result;
}
bool term_value()//读入一项的并且返回其值
{
	bool result = factor_value();//读入一个因子
	char op = mypeek();//取出一个字符判断还有没有因子
	if (op == '&')
	{
		myget();
		bool value = term_value();//读入下一个因子
		result = result && value;
	}
	return result;
}
bool factor_value()
{
	bool result;
	char c = mypeek();//取出一个字符判断还有没有因子
	if (c == '!')
	{
		myget();
		bool value = factor_value();//读入下一个因子
		result = !value;
	}
	else if (c == '(')
	{
		myget();//去掉左括号
		result = expression_value();//读入表达式
		myget();//去掉右括号
	}
	else//是字符
	{
		myget();
		if (c == 'V')
			result = true;
		else
			result = false;
	}
	return result;
}