/*
def readd(name, space):
	new d = (name, space)
	while (subname = readname != ]||*):
		if subname==f:
			d.files += readf(subname, space) // need to sort
		else if subname==d:
			d.dirs += readd(subname, space+1) // don't need to sort
	d.files.sort()
	return d

def output(d):
	cout << space << name << endl
	for dir in d.dirs:
		output(dir)
	for file in d.files:
		cout << space << file << endl

output(readd('ROOT'， 0))
*/
#include <algorithm>
#include <iostream>
using namespace std;

string prefix = "|     ";
string readDir(string name, int spacenum) {
	string dirs[30];
	string files[30];
	int dirTop = 0;
	int fileTop = 0;

	string subname;
	cin >> subname;
	while (subname != "]" && subname != "*") {
		if (subname == "#") {
			return "";
		} else if (subname[0] == 'f') {
			files[fileTop] = "";
			for (int i=0;i<spacenum;++i) {
				files[fileTop] += prefix;
			}
			files[fileTop] += subname + "\n";
			fileTop ++;
		} else {
			dirs[dirTop] = readDir(subname, spacenum+1);
			dirTop ++;
		}
		cin >> subname;
	}
	sort(files, files+fileTop);

	string res = "";
	for (int i=0;i<spacenum;++i) {
		res += prefix;
	}
	res += name + "\n";
	for (int i=0;i<dirTop;++i) {
		res += dirs[i];
	}
	for (int i=0;i<fileTop;++i) {
		res += files[i];
	}
	return res;
}

int main(int argc, char const *argv[])
{
	string res = "";
	int i = 1;
	while ((res = readDir("ROOT", 0)) != "") {
		cout << "DATA SET " << i << ":" << endl;
		cout << res << endl;//最后会多输出一行
		i++;
	}
	return 0;
}