#include <vector>
#include <algorithm>	
#include <stdio.h>
// #include <functional>
using namespace std;
bool cmp(const int &a, const int &b) //最小堆的栈顶最小
{
	return a>b;//使用greater<int>或大于函数
}
int main(int argc, char const *argv[])
{
	int t;
	scanf("%d", &t);
	vector<int> arr;
	while (t--)
	{
		int n, type, num;
		scanf("%d", &n);
		arr.clear();
		//建堆
		make_heap(arr.begin(), arr.end(), cmp);
		//默认是建立最大堆的。对int类型，可以在第三个参数传入greater<int>()得到最小堆。
		for (int i=0;i<n;++i)
		{
			scanf("%d", &type);
			if (type == 1)
			{
				scanf("%d", &num);
				//加入新数据 先在容器中加入，再调用push_heap()
				arr.push_back(num);
				push_heap(arr.begin(), arr.end(), cmp); //维护堆
			}
			else
			{
				//删除数据  要先调用pop_heap()，再在容器中删除
				// printf("%d\n", arr.front()); 是不对的
				pop_heap(arr.begin(), arr.end(), cmp);//把first和last-1交换，再维护堆
				printf("%d\n", arr.back()); //在pop之后再输出back()
				arr.pop_back();
			}
		}
	}
	return 0;
}