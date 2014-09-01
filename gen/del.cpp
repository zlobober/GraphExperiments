#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;

int myrand(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

typedef long long llong;

llong abs(llong x)
{
    return (x > 0) ? x : -x;
}

struct vt
{
    int x, y;
    vt(int _x, int _y)
    {
        x = _x, y = _y;
    }
    friend vt operator +(vt a, vt b)
    {
        return vt(a.x + b.x, a.y + b.y);
    }
    friend vt operator -(vt a, vt b)
    {
        return vt(a.x - b.x, a.y - b.y);
    }
    friend llong operator *(vt a, vt b)
    {
        return (llong)a.x * b.x + (llong)a.y * b.y;
    }
    friend llong operator ^(vt a, vt b)
    {
        return (llong)a.x * b.y - (llong)b.x * a.y;
    }
    friend bool operator <(vt a, vt b)
    {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
    friend bool operator ==(vt a, vt b)
    {
        return a.x == b.x && a.y == b.y;
    }
    vt() {}
};

int main(int argc, char* argv[])
{
    assert(argc == 5);
    int m = atoi(argv[1]);
    int k = atoi(argv[2]);
    FILE* pts = fopen(argv[3], "r");
    FILE* tri = fopen(argv[4], "r");
    int n;
    assert(fscanf(pts, "%d", &n));
    vector<int> bombs(n, 0);
    for (int i = 0; i < k; i++)
        bombs[i] = 1;
    random_shuffle(bombs.begin(), bombs.end());
    vector<vt> P(n);
    for (int i = 0; i < n; i++)
        assert(fscanf(pts, "%d %d", &P[i].x, &P[i].y));;
    printf("document.data = {\n\t'nodes' : [\n");
    for (int i = 0; i < n; i++)
        printf("\t\t[%d, %d, %d]%c\n", P[i].x, P[i].y, bombs[i], ", "[i + 1 == n]);
    printf("],\n\t'edges': [\n");
    vector<pair<int, int> > E;
    while (true)
    {
        int a, b, c;
        if (fscanf(tri, "%d %d %d", &a, &b, &c) == 3)
        {
            --a, --b, --c;
            E.push_back(make_pair(a, b));
            E.push_back(make_pair(b, c));
            E.push_back(make_pair(c, a));
        }
        else
            break;
    }
    sort(E.begin(), E.end());
    E.resize(unique(E.begin(), E.end()) - E.begin());
    random_shuffle(E.begin(), E.end());
    E.resize(m);
    for (int i = 0; i < E.size(); i++)
    {
        here:;
        if (i == E.size())
            break;
        for (int j = 0; j < E.size(); j++)
        {
            if (i == j)
                continue;
            int a[2] = {E[i].first, E[i].second};
            int b[2] = {E[j].first, E[j].second};
            int c = -1;
            for (int u = 0; u < 2; u++)
                for (int v = 0; v < 2; v++)
                    if (a[u] == b[v])
                        c = a[u];
            if (c != -1)
            {
                if (a[1] == c)
                    swap(a[0], a[1]);
                if (b[1] == c)
                    swap(b[0], b[1]);
                vt va = P[a[1]] - P[a[0]];
                vt vb = P[b[1]] - P[b[0]];
                if (abs(atan2(va ^ vb, va * vb)) < 3.1415926 / 10)
                {
                    E.erase(E.begin() + ((rand() & 1) ? i : j));
                    goto here;
                }
            }
        }
    }
    for (int i = 0; i < E.size(); i++)
        printf("\t\t[%d, %d]%c\n", E[i].first, E[i].second, ", "[i + 1 == E.size()]);
    printf("\t]\n}\n");

}
