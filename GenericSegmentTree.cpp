#include <bits/stdc++.h>
using namespace std;
#define INF (int)1e9
#define int long long
#define ll long long
#define mod1 1000000007
#define mod2 998244353
#define mp make_pair
#define pb push_back
#define rep(i, s, n) for (int i = s; i < n; i++)
#define rrep(i, n, s) for (int i = n; i >= s; i--)
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
typedef pair<int, int> pii;
typedef vector<ll> vi;
typedef vector<string> vs;
typedef vector<char> vc;
typedef vector<bool> vb;
typedef vector<pii> vii;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef map<int, int> mii;
typedef set<int> si;
#define REACH(a,b) for(auto &(a):(b))
#define SIZE(v) (int)v.size()
#define SORT(v) sort(all(v))
#define REVERSE(v) reverse(all(v))
#define GCD(a,b) (__gcd((a),(b)))
#define LCM(a,b) ((a)*((b)/GCD((a),(b))))
#define YESNO(b) ((b)?(cout<<("YES\n")):(cout<<("NO\n")))
void REJECT() {
    cout << -1 << '\n';
    return;
}

struct update {
    ll setval, increment;
    update() {
        setval = -1;
        increment = 0;
    }
    update(ll setval, ll increment) {
        this->setval = setval;
        this->increment = increment;
    }
    bool operator == (const update &other) const {
        return setval == other.setval and increment == other.increment;
    }
};

template<class T, class U>
// T -> node, U->update.
struct Lsegtree {
    vector<T>st;
    vector<U>lazy;
    ll n;
    T identity_element;
    U identity_update;
    Lsegtree(ll n, T identity_element, U identity_update)
    {
        this->n = n;
        this->identity_element = identity_element;
        this->identity_update = identity_update;
        st.assign(4 * n, identity_element);
        lazy.assign(4 * n, identity_update);
    }
    T combine(T l, T r)
    {
        // change this function as required.
        
        // T ans = (l + r);
        // return ans;
        T ans = max(l , r);
        return ans;
    }
    void buildUtil(ll v, ll tl, ll tr, vector<T>&a)
    {
        if (tl == tr)
        {
            st[v] = a[tl];
            return;
        }
        ll tm = (tl + tr) >> 1;
        buildUtil(2 * v + 1, tl, tm, a);
        buildUtil(2 * v + 2, tm + 1, tr, a);
        st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
    }
    // change the following 2 functions, and you're more or less done.
    T apply(T curr, U upd, ll tl, ll tr)
    {
        T ans = (tr - tl + 1) * upd;
        // T ans = curr;
        // if (upd.setval != -1) {
        //     ans = (tr - tl + 1) * (upd.setval + upd.increment);
        // } else {
        //     ans += (tr - tl + 1) * (upd.increment);
        // }

        return ans;
    }
    U combineUpdate(U old_upd, U new_upd, ll tl, ll tr)
    {
        U ans = old_upd;
        // if (new_upd.setval != -1) {
        //     ans = new_upd;
        // } else {
        //     ans.increment += new_upd.increment;
        // }
        return ans;
    }
    void push_down(ll v, ll tl, ll tr)
    {
        if (lazy[v] == identity_update)return;
        st[v] = apply(st[v], lazy[v], tl, tr);
        if (2 * v + 2 < 4 * n)
        {
            ll tm = (tl + tr) >> 1;
            lazy[2 * v + 1] = combineUpdate(lazy[2 * v + 1], lazy[v], tl, tm);
            lazy[2 * v + 2] = combineUpdate(lazy[2 * v + 2], lazy[v], tm + 1, tr);
        }
        lazy[v] = identity_update;
    }
    T queryUtil(ll v, ll tl, ll tr, ll l, ll r)
    {
        push_down(v, tl, tr);
        if (l > r)return identity_element;
        if (tr < l or tl > r)
        {
            return identity_element;
        }
        if (l <= tl and r >= tr)
        {
            return st[v];
        }
        ll tm = (tl + tr) >> 1;
        return combine(queryUtil(2 * v + 1, tl, tm, l, r), queryUtil(2 * v + 2, tm + 1, tr, l, r));
    }

    void updateUtil(ll v, ll tl, ll tr, ll l, ll r, U upd)
    {
        push_down(v, tl, tr);
        if (tr < l or tl > r)return;
        if (tl >= l and tr <= r)
        {
            lazy[v] = combineUpdate(lazy[v], upd, tl, tr);
            push_down(v, tl, tr);
        }
        else
        {
            ll tm = (tl + tr) >> 1;
            updateUtil(2 * v + 1, tl, tm, l, r, upd);
            updateUtil(2 * v + 2, tm + 1, tr, l, r, upd);
            st[v] = combine(st[2 * v + 1], st[2 * v + 2]);
        }
    }



    void build(vector<T>a)
    {
        assert(SIZE(a) == n);
        buildUtil(0, 0, n - 1, a);
    }
    T query(ll l, ll r)
    {
        return queryUtil(0, 0, n - 1, l, r);
    }
    void update(ll l, ll r, U upd)
    {
        updateUtil(0, 0, n - 1, l, r, upd);
    }
};

void Solve()
{
    ll n, q;
    cin >> n >> q;
    vi a(n + 1, 0);
    rep(i, 1, n + 1) {
        cin >> a[i];
    }
    update upd(-1, 0);
    Lsegtree<ll, update> seg(n + 1, 0, upd);
    seg.build(a);
    ll t, l, r, x;

    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> x;
            update upd(-1, x);
            seg.update(l, r, upd);
        } else if (t == 2) {
            cin >> l >> r >> x;
            update upd(x, 0);
            seg.update(l, r, upd);
        } else {
            cin >> l >> r;
            cout << seg.query(l, r) << '\n';
        }
    }
}
