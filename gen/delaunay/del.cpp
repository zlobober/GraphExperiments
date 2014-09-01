#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
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

set<pair<int, int> > crossed;

const int N = 2000;
vector<int> E[N];

int tmp[N];

vector<pair<int, int> > ed;
bool try_cross(int a, int b)
{
    sort(E[a].begin(), E[a].end());
    sort(E[b].begin(), E[b].end());
    int q = set_intersection(E[a].begin(), E[a].end(), E[b].begin(), E[b].end(), tmp) - tmp;
    if (q != 2)
        return false;
    int c = tmp[0], d = tmp[1];
    int U[] = {
        a, b,
        a, c,
        a, d,
        b, c,
        b, d,
        c, d,
    };
    for (int u = 0; u < 5; u++)
        if (crossed.find(make_pair(U[2 * u], U[2 * u + 1])) != crossed.end())
            return false;
    E[c].push_back(d);
    E[d].push_back(c);
    for (int u = 0; u < 6; u++)
        crossed.insert(make_pair(U[2 * u], U[2 * u + 1])), crossed.insert(make_pair(U[2 * u + 1], U[2 * u]));
    ed.push_back(make_pair(c, d));
    return true;
}

int main(int argc, char* argv[])
{
    assert(argc == 7);
    int m = atoi(argv[1]);
    int k = atoi(argv[2]);
    int c = atoi(argv[3]);
    FILE* pts = fopen(argv[4], "r");
    FILE* tri = fopen(argv[5], "r");
    srand(atoi(argv[6]));
    int n;
    assert(fscanf(pts, "%d", &n));
    vector<int> bombs(n, 0);
    for (int i = 0; i < k; i++)
        bombs[i] = 1;
    random_shuffle(bombs.begin(), bombs.end());
    vector<vt> P(n);
    for (int i = 0; i < n; i++)
        assert(fscanf(pts, "%d %d", &P[i].x, &P[i].y));;
    printf("{\n\t\"nodes\": [\n");
    for (int i = 0; i < n; i++)
        printf("\t\t[%d, %d, %d]%c\n", P[i].x, P[i].y, bombs[i], ", "[i + 1 == n]);
    printf("],\n\t\"edges\": [\n");
    while (true)
    {
        int a, b, c;
        if (fscanf(tri, "%d %d %d", &a, &b, &c) == 3)
        {
            --a, --b, --c;
            ed.push_back(make_pair(a, b));
            ed.push_back(make_pair(b, c));
            ed.push_back(make_pair(c, a));
        }
        else
            break;
    }
    sort(ed.begin(), ed.end());
    ed.resize(unique(ed.begin(), ed.end()) - ed.begin());
    random_shuffle(ed.begin(), ed.end());
    ed.resize(m);
    for (int i = 0; i < ed.size(); i++)
    {
        here:;
        if (i == ed.size())
            break;
        for (int j = 0; j < ed.size(); j++)
        {
            if (i == j)
                continue;
            int a[2] = {ed[i].first, ed[i].second};
            int b[2] = {ed[j].first, ed[j].second};
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
                    ed.erase(ed.begin() + ((rand() & 1) ? i : j));
                    goto here;
                }
            }
        }
    }

    for (int i = 0; i < ed.size(); i++)
    {
        E[ed[i].first].push_back(ed[i].second);
        E[ed[i].second].push_back(ed[i].first);
    } 

    for (int i = 0; i < c; i++)
    {
        while (true)
        {
            int q = rand() % ed.size();
            if (try_cross(ed[q].first, ed[q].second))
                break;
        }
    }

    random_shuffle(ed.begin(), ed.end()); 

    for (int i = 0; i < ed.size(); i++)
        printf("\t\t[%d, %d]%c\n", ed[i].first, ed[i].second, ", "[i + 1 == ed.size()]);
    printf("\t]\n}\n");

}
