#include <bits/stdc++.h>
using namespace std;
// n = 100000 : 9592(time: 5.3e-05s)
// n = 1e+06 : 78498(time: 4e-06s)
// n = 1e+07 : 664579(time: 3e-06s)
// n = 1e+08 : 5761455(time: 0.000126s)
// n = 1e+09 : 50847534(time: 0.0006s)
// n = 1e+10 : 455052511(time: 0.00434s)
// n = 1e+11 : 4118054813(time: 0.058318s)
// n = 1e+12 : 37607912018(time: 0.53861s)
// n = 1e+13 : 346065536839(time: 6.10802s)const int N = 3e5 + 9;
using ll = long long;

namespace pcf {
// initialize once by calling init()
#define MAXN 20000010      // initial sieve limit
#define MAX_PRIMES 2000010 // max size of the prime array for sieve
#define PHI_N 100000
#define PHI_K 100

int len = 0; // total number of primes generated by sieve
int primes[MAX_PRIMES];
ll pref0[MAXN];      // pref[i] --> number of primes <= i
ll pref[MAXN];       // pref[i] --> number of primes <= i
ll dp[PHI_N][PHI_K]; // precal of yo(n,k)
bitset<MAXN> f;

inline long long func(int p) {
  // return 1;//p;
  return p;
}

inline long long accfunc(long long n) {
  // return n;//*(n+1)/2;
  return n * (n + 1) / 2;
}

void sieve(int n) {
  f[1] = true;
  for (int i = 4; i <= n; i += 2)
    f[i] = true;
  for (int i = 3; i * i <= n; i += 2) {
    if (!f[i]) {
      for (int j = i * i; j <= n; j += i << 1)
        f[j] = 1;
    }
  }
  pref0[0] = 0;
  pref[0] = 0;
  for (int i = 1; i <= n; i++) {
    if (!f[i]) {
      primes[len++] = i;
      pref0[i] = pref0[i - 1] + 1;
      pref[i] = pref[i - 1] + func(i); // len;
    } else {
      pref0[i] = pref0[i - 1];
      pref[i] = pref[i - 1];
    }
  }
}
void init() {
  sieve(MAXN - 1);
  // precalculation of phi upto size (PHI_N,PHI_K)
  for (int n = 0; n < PHI_N; n++)
    dp[n][0] = accfunc(n);
  for (int k = 1; k < PHI_K; k++) {
    for (int n = 0; n < PHI_N; n++) {
      dp[n][k] =
          dp[n][k - 1] - dp[n / primes[k - 1]][k - 1] * func(primes[k - 1]);
    }
  }
  for (int i = 0; i < 6; i++) {
    cout << endl;
    for (int j = 0; j < 6; j++)
      cout << dp[i][j] << " ";
  }
  cout << endl;
}
// returns the number of integers less or equal n which are
// not divisible by any of the first k primes
// recurrence --> yo(n, k) = yo(n, k-1) - yo(n / p_k , k-1)
// for sum of primes yo(n, k) = yo(n, k-1) - p_k * yo(n / p_k , k-1)
long long yo(long long n, int k) {
  if (n < PHI_N && k < PHI_K)
    return dp[n][k];
  if (k == 1)
    return accfunc((++n) >> 1); ////??????????????????
  if (primes[k - 1] >= n)
    return 1; //*func(n);
  return yo(n, k - 1) - yo(n / primes[k - 1], k - 1) * func(primes[k - 1]);
}
// complexity: n^(2/3).(log n^(1/3))
// long long Legendre(long long n) {
//   if (n < MAXN)
//     return pref[n];
//   int lim = sqrt(n) + 1;
//   int k = upper_bound(primes, primes + len, lim) - primes;
//   return yo(n, k) + (k - 1);
// }
// runs under 0.2s for n = 1e12
long long Lehmer0(long long n) {
  if (n < MAXN)
    return pref0[n];
}

long long Lehmer(long long n) {
  if (n < 2)
    return pref[n];
  long long w, res = 0;
  int b = sqrt(n), c = Lehmer0(cbrt(n)), a = Lehmer0(sqrt(b));
  b = Lehmer0(b);
  cout << endl << "a,b,c:" << a << "," << b << "," << c << endl;
  res = yo(n, a) +
        ((1LL * (b + a - 2) * (b - a + 1)) >> 1) * func(n); // -func(1)+1;
  cout << endl << n << " resA=" << res << "(" << a << "," << b << ")" << endl;
  for (int i = a; i < b; i++) {
    w = n / primes[i];
    int lim = Lehmer(sqrt(w));
    res -= Lehmer(w); //*(func(primes[i]));
    cout << endl
         << n << " resB=" << res << " after entering p=" << primes[i]
         << " substracted Leh(" << w << endl;
    if (i <= c) {
      for (int j = i; j < lim; j++) {
        res += (1 + Lehmer(primes[j - 1])) * func(primes[j]);
        res -= Lehmer(w / primes[j]) * func(primes[j]);
        cout << endl << n << " resC=" << res << endl;
      }
    }
  }
  // cout<<endl<<n<<" resD"<<res<<endl;
  return res;
}
} // namespace pcf
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  pcf::init();
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  // vector<ll> ns = {(ll)1e4,(ll)1e5,(ll)1e6,(ll)1e7,(ll)1e8,(ll)1e9,(ll)1e10,
  // (ll)1e11, (ll)1e12, (ll)1e13};
  vector<ll> ns = {
      // 1,2,3,4,5,
      5, 6 //,7,8,9,10
  }; //,100,1000,10000,99999,100000};//(ll)1e10, (ll)1e11, (ll)1e12, (ll)1e13};
  for (ll n : ns) {
    auto start_time = clock();
    ll res = pcf::Lehmer(n);
    cout << "n = " << (double)n << " : " << res
         << "(time: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << "s)"
         << endl;
  }
  return 0;
}
// https://judge.yosupo.jp/problem/counting_primes