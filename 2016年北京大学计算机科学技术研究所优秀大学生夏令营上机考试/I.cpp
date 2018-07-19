#include <iostream>
#include <map>
using namespace std;
int cost[30][30];
int pre[30][30];
int n;
map<string, int> place2index;
map<int, string> index2place;
void floyd()
{
	for (int k=0;k<n;++k)
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				if (cost[i][j] > cost[i][k]+cost[k][j])
				{
					cost[i][j] = cost[i][k]+cost[k][j];
					pre[i][j] = k;
				}
}
void showpath(int b, int e)//前开后闭
{
    if (b == e)
    	return;
    if (pre[b][e] == -1)
    	cout << "->(" << cost[b][e] << ")->" << index2place[e];
    else
    {
        showpath(b, pre[b][e]);
        showpath(pre[b][e], e);
	}
}
int main(int argc, char const *argv[])
{
	int m, t, val;
	string s, beg, end;
	scanf("%d", &n);
	for (int i=0;i<n;++i)
	{
		cin >> s;
		place2index.insert(pair<string, int>(s, i));
		index2place.insert(pair<int, string>(i, s));
	}
	for (int i=0;i<n;++i)
		for (int j=0;j<n;++j)
		{
			cost[i][j] = 1<<28;
			pre[i][j] = -1;
		}
	scanf("%d", &m);
	while (m--)
	{
		cin >> beg >> end >> val;
		if (val < cost[place2index[beg]][place2index[end]])
		{
			cost[place2index[beg]][place2index[end]] = val;
			cost[place2index[end]][place2index[beg]] = val;//无向图
		}
	}
	floyd();
	scanf("%d", &t);
	while (t--)
	{
		cin >> beg >> end;
		int b = place2index[beg], e = place2index[end];
		cout << beg;
		showpath(b, e);
		cout << endl;
	}
	return 0;
}