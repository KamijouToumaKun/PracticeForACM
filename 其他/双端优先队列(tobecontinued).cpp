#include <vector>
#include <algorithm>	
#include <stdio.h>
using namespace std;
struct Person
{
	int id;
	int priority;
	Person(int a, int b)
	{
		id = a;
		priority = b;
	}
};
bool mymin(const Person &a, const Person &b) //最小堆的栈顶最小
{
	return a.priority>b.priority;//使用greater<int>或大于函数
}
bool mymax(const Person &a, const Person &b)
{
	return a.priority<b.priority;
}
int main(int argc, char const *argv[])
{
	vector<Person> maxn, minn;
	//建堆
	make_heap(maxn.begin(), maxn.end(), mymax);
	make_heap(minn.begin(), minn.end(), mymin);
	int type, id, priority;
	while (scanf("%d", &type), type)
	{
		if (type == 1)
		{
			scanf("%d%d", &id, &priority);
			//加入新数据 先在容器中加入，再调用push_heap()
			maxn.push_back(Person(id, priority));
			minn.push_back(Person(id, priority));
			push_heap(maxn.begin(), maxn.end(), mymax); //维护堆
			push_heap(minn.begin(), minn.end(), mymin); //维护堆
		}
		else if (type == 2)
		{
			if (maxn.empty())
				printf("0\n");
			else
			{
				pop_heap(maxn.begin(), maxn.end(), mymax);//把first和last-1交换，再维护堆
				printf("%d\n", maxn.back().id); //在pop之后再输出back()
				maxn.pop_back();
			}
		}
		else
		{
			if (minn.empty())
				printf("0\n");
			else
			{
				pop_heap(minn.begin(), minn.end(), mymin);//把first和last-1交换，再维护堆
				printf("%d\n", minn.back().id); //在pop之后再输出back()
				minn.pop_back();
			}
		}
	}
	return 0;
}