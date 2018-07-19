#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
string pre2str(int prefix)
{
	string s = "";
	for (int i=0;i<prefix;++i)
		s += "|     ";
	return s;
}
string readdir(string dirname, int prefix)
{
	string res = pre2str(prefix) + dirname + '\n';
	string file[1000], dir[1000];
	int filetop = 0, dirtop = 0;
	string s;
	while (cin>>s, s[0]!=']')
	{
		if (s[0] == 'f')
			file[filetop++] = pre2str(prefix) + s;
		else
			dir[dirtop++] = readdir(s, prefix+1);
	}
	sort(file, file+filetop);
	for (int i=0;i<dirtop;++i)
		res += dir[i];
	for (int i=0;i<filetop;++i)
		res += file[i] + '\n';
	return res;
}
bool readtest(int t)
{
	string res = "ROOT\n";
	string file[1000], dir[1000];
	int filetop = 0, dirtop = 0;
	string s;
	while (cin>>s, s[0]!='*'&&s[0]!='#')
	{
		if (s[0] == 'f')
			file[filetop++] = s; //需要排序
		else
			dir[dirtop++] = readdir(s, 1);
	}
	if (s[0] == '#')
		return false;
	sort(file, file+filetop);
	for (int i=0;i<dirtop;++i)
		res += dir[i];
	for (int i=0;i<filetop;++i)
		res += file[i] + '\n';
	cout << "DATA SET " << t << ":" << endl << res;
	return true;
}
int main(int argc, char const *argv[])
{
	int t = 0;
	while (readtest(++t))
	{
		printf("\n"); //还有一个空行
	}
	return 0;
}