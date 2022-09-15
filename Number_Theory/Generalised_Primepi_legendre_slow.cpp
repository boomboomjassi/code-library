#include <bits/stdc++.h>
using ll = long long;
using namespace std;
// credits: Lucy_Hedgehog
// Legendre
// O(n^(3/4))
// n = 1e+10 :  7413165246951120256(time: 0.843584s)
// n = 1e+11 :  8746113789707973631(time: 1.74779s)
// n = 1e+12 :  8247104618519365631(time: 5.27918s)

// #include <boost/unordered_map.hpp>

using ull = unsigned long long;

using namespace std;

// using namespace boost;

vector<ull> V;

// boost::

unordered_map<ull, ull> S;

ull prime_sum(ull n) {
  ull r = (ull)sqrt(n);
  for (int i = 1; i <= r; i++) {
    V.push_back(n / i);
  }
  for (int i = V[V.size() - 1] - 1; i > 0; i--) {
    V.push_back(i);
  }
  for (int i = 0; i < V.size(); i++) {
    S[V[i]] = V[i] * (V[i] + 1) / 2 - 1;
  }

  for (int p = 2; p <= r; p++) {
    if (S[p] > S[p - 1]) {
      ull sp = S[p - 1];
      for (int i = 0; i < V.size() && V[i] >= p * p; i++) {
        S[V[i]] -= p * (S[V[i] / p] - sp);
      }
    }
  }
  return S[n];
}

int main() {
  vector<ll> ns = {(ll)1e10, (ll)1e11, (ll)1e12, (ll)1e13};
  for (ll n : ns) {
    auto start_time = clock();
    ll res = prime_sum(n);
    cout << "n = " << n << " : " << res
         << "(time: " << (double)(clock() - start_time) / CLOCKS_PER_SEC << "s)"
         << endl;
  }
  return 0;
}