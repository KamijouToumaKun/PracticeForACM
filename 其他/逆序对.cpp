#include <stdio.h>
// 求解逆序对
// 分治法
// 划分问题：把序列分成元素个数尽量相等的两半
// 递归求解：求解两边的逆序对
// 合并问题：合并成一个序列时的逆序对

int ans = 0;
void mergeSort(int *a, int l, int r) {
    // 递归边界
    if (l == r)
        return;
    int m = l + (r - l) / 2; // 取中值
    mergeSort(a, l, m); // 递归左半
    mergeSort(a, m+1, r); // 递归右半

    int totalSize = r - l + 1;
    int *tmp = new int[totalSize];
    int p = 0;
    int i = l, j = m+1;
    while (i<=m && j<=r)
    {
        if (a[i] <= a[j])
            tmp[p++] = a[i++];
        else
        {
            tmp[p++] = a[j++];
            ans += m+1-i;
        }
    }
    // 余下部分
    while (i<=m)
        tmp[p++] = a[i++];
    while (j<=r)
        tmp[p++] = a[j++];
    // 将临时数组的值放入原数组
    for(p=0;p<=r-l;++p)
        a[l+p] = tmp[p];
    delete[] tmp;
}

int main() {
    int a[100], n;
    scanf("%d", &n);
    for (int i=0;i<n;++i)
        scanf("%d", &a[i]);
    mergeSort(a, 0, n - 1);
    printf("%d\n", ans);
    return 0;
}