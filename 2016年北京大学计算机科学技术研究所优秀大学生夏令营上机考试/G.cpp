/*可以用DP。注意*考虑三种情形：匹配0个字符、1个字符、多个字符。
设f[i][j]为第一个字符串的前缀i是否能和第二个字符串的前缀j匹配，
则这三种情况分别对应f[i-1][j]、f[i-1][j-1]、f[i][j-1]。
再者，边界的处理要慎重。如果把前缀0作为空串，那么空串能和空串、*匹配。
*/
#include <cstdio>
#include <cstring>
using namespace std;
char s[22], t[22];
bool f[22][22];

int main()
{
    scanf("%s %s", s+1, t+1);
    int m = strlen(s+1), n = strlen(t+1);
    f[0][0] = true;
    for (int i = 1; s[i] == '*'; ++i)
        f[i][0] = true;
    for (int i = 1; s[i]; ++i)
        for (int j = 1; t[j]; ++j) {
            if (s[i] == '?')
                f[i][j] = f[i-1][j-1];
            else if (s[i] == '*')
                f[i][j] = f[i-1][j] || f[i-1][j-1] || f[i][j-1];//0个 1个 多个
            else
                f[i][j] = f[i-1][j-1] && (s[i] == t[j]);
        }
    puts(f[m][n] ? "matched" : "not matched");
    return 0;
}