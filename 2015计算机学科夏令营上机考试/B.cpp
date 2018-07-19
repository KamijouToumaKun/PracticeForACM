#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	char s[1000];
	cin.getline(s, sizeof(s), '\n');
	for (int i=0;i<strlen(s);)
	{
		printf("%c", s[i]);
		if (s[i] == ' ')
		{
			while (s[i] == ' ')
				i++;
		}
		else
			i++;
	}
	return 0;
}