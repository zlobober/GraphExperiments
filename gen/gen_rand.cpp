#include <cstdio>
#include <set>
#include <algorithm>
#include <cstdlib>
using namespace std;

set<pair<int, int> > S;

int myrand(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    int mx = atoi(argv[2]);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        while (true)
        {
            x = myrand(0, mx);
            y = myrand(0, mx);
            bool bad = false;
            for (set<pair<int, int> >::iterator it = S.begin(); it != S.end(); it++)
            {
                int x2 = it->first;
                int y2 = it->second;
                if ((x - x2) * (x - x2) + (y - y2) * (y - y2) <= 50 * 50)
                    bad = true;
            }
            if (!bad)
                break;
        }
        S.insert(make_pair(x, y));
        printf("%d %d\n", x, y);
    }
    return 0;
}

