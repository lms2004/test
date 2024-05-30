#include<bits/stdc++.h>
#include <unordered_set>
#include<stdio.h>
int map[39][39] = { 0 };

int main() {
    int m = 0, n = 0;
    scanf_s("%d %d", &n, &m);

    map[1][1] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (i % 2 == 0 && j % 2 == 0)
                continue;
            else {
                map[i][j] += map[i][j - 1] + map[i - 1][j];
            }
            printf("%d ", map[i][j]);
        }printf("\n");
    }
    printf("%d", map[n][m]);

    return 0;
}