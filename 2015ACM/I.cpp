/*使用置换群的知识。
可以证明，至多需要两次即可。
*/
#include <stdio.h>  
#include <iostream>  
#include <string>  
#include <stdlib.h>  
#include <algorithm>  
#include <math.h>  
#include <string.h>  
#include <map>  
#include <queue>  
#include <stack>  
using namespace std;  
const int INF=0x3f3f3f3f;  
const int MAXN=1005;  
  
typedef long long LL;  
  
map <string,int> m;  
int rou[MAXN][MAXN],nr=0,ir[MAXN],nmap=0,n,mp[MAXN],vis[MAXN];  
string fstr[MAXN];  
  
int findn(string str)   //找到字符串序号  
{  
    if(m.count(str))  
        return m[str];  
    m[str]=++nmap;  
    //cout<<nmap<<endl;  
    fstr[nmap]=str;  
    return nmap;  
}  
  
int main()  
{  
    string str,a,b;  
    cin>>n;  
    int flag=1;  
    memset(vis,0,sizeof(vis));  //是否已经加入某个圈  
    memset(mp,0,sizeof(mp));    //每个人拿的是谁的思想  
    memset(ir,0,sizeof(ir));    //每个圈有多少个人  
    for(int i=0;i<n;i++){  
        cin>>a>>b;  
        if(a==b)  
            continue;  
        int x=findn(a);  
        mp[findn(a)]=findn(b);  
    }  
    n=m.size();  
    for(int i=1;i<=n;i++){  
        if(vis[i])  
            continue;  
        int temp=i;  
        nr++;  
        while(!ir[nr]||temp!=i){      //建圈  
            vis[temp]=1;  
            rou[nr][++ir[nr]]=temp;  
            temp=mp[temp];  
        }  
    }  
    for(int i=1;i<=nr;i++){           //如果每个圈都只有两个元素，就只需要一轮，否则两轮  
        if(ir[i]>2){  
            flag=2;  
            break;  
        }  
    }  
    if(nr==0)  
        cout<<0<<endl;  
    else if(flag==1){  
        cout<<1<<endl;  
        cout<<nr<<endl;  
        for(int i=1;i<=nr;i++){  
            cout<<fstr[rou[i][1]]<<' '<<fstr[rou[i][2]]<<endl; //fstr用于通过序号找到字符串  
        }  
    }  
    else{  
        cout<<2<<endl;  
        int num1=nr,num2=0;                    //第一轮是每个圈1，2换，后面的3和最后一个换，这用往中间对称  
        for(int i=1;i<=nr;i++){                 //第二轮是2和最后一个这样往中间对称换  
            num1+=(ir[i]-2)/2;  
            num2+=(ir[i]-1)/2;  
        }  
        cout<<num1<<endl;  
        for(int i=1;i<=nr;i++){  
            cout<<fstr[rou[i][1]]<<' '<<fstr[rou[i][2]]<<endl;  
    //      swap(rou[i][1],rou[i][2]);  
            int l=3,r=ir[i];  
            while(l<r){  
                cout<<fstr[rou[i][l++]]<<' '<<fstr[rou[i][r--]]<<endl;  
    //          swap(rou[i][l++],rou[i][r--]);  
            }  
        }  
        cout<<num2<<endl;  
        for(int i=1;i<=nr;i++){  
            if(ir[i]>2)  
            cout<<fstr[rou[i][1]]<<' '<<fstr[rou[i][3]]<<endl;  
            int l=4,r=ir[i];  
            while(l<r){  
                cout<<fstr[rou[i][l++]]<<' '<<fstr[rou[i][r--]]<<endl;  
            }  
        }  
    }  
    return 0;  
}  