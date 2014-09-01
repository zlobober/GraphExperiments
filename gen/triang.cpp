#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;

typedef long long llong;

const int MAX = 200000000;
const int N = 200500;

int myrand(int a, int b)
{
    return rand() % (b - a + 1) + a;
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
map<vt, int> M;

struct cmp_by_d
{
    vt d;
    cmp_by_d(vt _d) : d(_d) {}
    bool operator ()(vt a, vt b)
    {
        return (b - a) * d > 0;
    }
};

vector<vt> extract(const vector<vt>& V, vt a, vt b)
{
    vector<vt> res;
    for (int i = 0; i < V.size(); i++)
        if (((V[i] - a) ^ (b - a)) == 0 && ((V[i] - a) * (V[i] - b) <= 0))
            res.push_back(V[i]);
    sort(res.begin(), res.end(), cmp_by_d(b - a));
    return res;
}

pair<int, int> ed[3 * N];
int pt = 0;

inline void add_edge(vt a, vt b)
{
    assert(pt < 3 * N);
    ed[pt++] = make_pair(M[a], M[b]);
}

inline bool in(vt a, vt b, vt c, vt x)
{
    return abs((a - x) ^ (b - x)) + abs((b - x) ^ (c - x)) + abs((c - x) ^ (a - x)) == abs((b - a) ^ (c - a));
}

void triangulate(vt a, vt b, vt c, vector<vt> D)
{
    if (((a - b) ^ (b - c)) == 0)
        return;
    assert(D.size() >= 3);
    if (D.size() == 3)
        return;
    while (true)
    {
        int x = myrand(0, (int)D.size() - 1);
        vt u = D[x];
        if (u == a || u == b || u == c)
            continue;
        vt R[3] = {a, b, c};
        int any = -1;
        for (int i = 0; i < 3; i++)
            if (((R[(i + 1) % 3] - u) ^ (R[(i + 2) % 3] - u)) == 0)
                any = i;
        for (int i = 0; i < 3; i++)
            if (any == -1 || any == i)
            {
                vector<vt> W = extract(D, u, R[i]);
                for (int j = 0; j + 1 < W.size(); j++)
                    add_edge(W[j], W[j + 1]);
            }
        vector<vt> T[3];
        for (int i = 0; i < D.size(); i++)
        {
            for (int j = 0; j < 3; j++)
                if (in(R[(j + 1) % 3], R[(j + 2) % 3], u, D[i]))
                    T[j].push_back(D[i]);
        }
        for (int i = 0; i < 3; i++)
            triangulate(u, R[(i + 1) % 3], R[(i + 2) % 3], T[i]);
        return;
    }
}

void triangulate_convex(vector<vt> A, vector<vt> B)
{
    if (A.size() == 1)
        return;
    if (A.size() == 2)
        return;
    if (A.size() == 3)
    {
        triangulate(A[0], A[1], A[2], B);
        return;
    }
    int a, b;
    while (true)
    {
        a = myrand(0, (int)A.size() - 1);
        b = myrand(0, (int)A.size() - 1);
        if (abs(a - b) <= 1 || abs(a - b) + 1 == A.size())
            continue;
        vector<vt> R = extract(B, A[a], A[b]);
        for (int i = 0; i + 1 < R.size(); i++)
            add_edge(R[i], R[i + 1]);
        vector<vt> C, D, E, F;
        C.push_back(A[a]);
        for (int i = (a + 1) % A.size(); i != b; i = (i + 1) % A.size())
            C.push_back(A[i]);
        C.push_back(A[b]);
        E.push_back(A[b]);
        for (int i = (b + 1) % A.size(); i != a; i = (i + 1) % A.size())
            E.push_back(A[i]);
        E.push_back(A[a]);
        for (int i = 0; i < B.size(); i++)
        {
            long long d = ((A[b] - A[a]) ^ (B[i] - A[a]));
            if (d >= 0)
                F.push_back(B[i]);
            if (d <= 0)
                D.push_back(B[i]);
        }
        triangulate_convex(C, D);
        triangulate_convex(E, F);
        break;
    }
}

int A[N];

struct cmp
{
    vt O;
    cmp(vt _O)
    {
        O = _O;
    }
    bool operator ()(vt a, vt b)
    {
        llong d = (a - O) ^ (b - O);
        if (d != 0)
            return d > 0;
        else
            return (a - O) * (a - O) < (b - O) * (b - O);
    }
};

vector<vt> convex(vector<vt> A)
{
    swap(A.front(), *max_element(A.begin(), A.end(), cmp_by_d(vt(-1, -(int)1e9))));
    sort(A.begin() + 1, A.end(), cmp(A.front()));
    vector<vt> st(1, A.front());
    for (int i = 1; i < A.size(); i++)
    {
        while (st.size() >= 2 && ((A[i] - *st.rbegin()) ^ (*st.rbegin() - *(++st.rbegin()))) >= 0)
            st.pop_back();
        st.push_back(A[i]);
    }
    return st;
}

int main(int argc, char* argv[])
{
    int m = atoi(argv[1]);
    int n;
    assert(scanf("%d", &n));
    assert(n < N);
    vector<vt> P(n);
    for (int i = 0; i < n; i++)
        assert(scanf("%d %d", &P[i].x, &P[i].y)), M[P[i]] = i;
    printf("document.data = {\n\t'nodes' : [\n");
    for (int i = 0; i < n; i++)
        printf("\t\t[%d, %d]%c\n", P[i].x, P[i].y, ", "[i + 1 == n]);
    vector<vt> C = convex(P);
    for (int i = (C.size() <= 2); i < C.size(); i++)
    {
        vector<vt> D = extract(P, C[i], C[(i + 1) % C.size()]);
        for (int j = 0; j + 1 < D.size(); j++)
            add_edge(D[j], D[j + 1]);
    }
    triangulate_convex(C, P);
    printf("],\n\t'edges': [\n");
    for (int i = 0; i < min(pt, m); i++)
        printf("\t\t[%d, %d]%c\n", ed[i].first, ed[i].second, ", "[i + 1 == min(pt, m)]);
    printf("\t]\n}\n");
}
