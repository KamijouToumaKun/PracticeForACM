#include<stdio.h>
int f[50010],r[50010];//带权并查集
int getf(int n)
{
    if(f[n]==n)return n;
    int tmp=f[n];
    f[n]=getf(f[n]); //令自己的父亲 = 父亲的父亲，递归更新为祖宗
    r[n]=(r[tmp]+r[n])%3; //自己与祖宗的关系 = (自己与父亲的关系+父亲与祖宗的关系)%3
    return f[n];
} 
int main()
{
    int n, k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        f[i]=i; //r[i]初始为0；0为同类，1为吃，2被吃
    int tp, a, b, x, y, cnt = 0;
    while(k--)
    {
        scanf("%d%d%d",&tp,&a,&b);
        if(a<1 || a>n || b<1 || b>n){cnt++;continue;}//数字非法
        x=getf(a);y=getf(b);//找根。现在a的父亲是x，b的父亲是y
        if(x!=y) //x和y还没有建立过联系
        {
            f[x]=y;//把x合并到y；
            r[x]=(r[b]-r[a]+tp-1+3)%3;
            //x对y的关系 = (- a对x的关系 + a对b的关系 + b对y的关系) % 3
            //tp==1的话，指定a对b的关系是0
            //即-r[a]+0+r[b]
            //tp==2的话，指定a对b的关系是1
            //即-r[a]+1+r[b]
        }
        else //已经建立过联系了，则判断关系是否正确
            if((tp-1+r[b]-r[a])%3) cnt++;
    }
    printf("%d",cnt);
    return 0;
}