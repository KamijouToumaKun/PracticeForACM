#include <stdio.h>
int a[100001];
int arr[100001]; //tmp
int kth(int beg, int end, int k)//闭区间
{
	int first = beg, last = end;
	int key = arr[first];
	while (first < last)
	{
		while (first<last && arr[last]>=key) //顺序不能反！
			last--;
		arr[first] = arr[last];
		while (first<last && arr[first]<=key)
			first++;
		arr[last] = arr[first];	
	}
	// now first == last，它是第first-beg+1小的（下标从1开始）
	arr[first] = key;
	if (first-beg+1 > k)
		return kth(beg, first-1, k);
	else if (first-beg+1 < k)
		return kth(first+1, end, k-(first-beg+1));
	else
		return key;
}
int main(int argc, char const *argv[])
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i=1;i<=n;++i)
		scanf("%d", &a[i]);
	int beg, end, k;
	while (m--)
	{
		scanf("%d%d%d", &beg, &end, &k);
		for (int i=beg;i<=end;++i)
			arr[i-beg] = a[i];
		printf("%d\n", kth(0, end-beg, k));
	}
	return 0;
}