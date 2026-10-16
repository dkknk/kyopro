// https://github.com/dkknk/kyopro/blob/main/lib/utility.hpp
#pragma once
namespace detail {
  template <typename Tp, size_t Nb>
  auto make_v(std::vector<size_t>& sizes, Tp const& x) {
    if constexpr (Nb == 1) {
      return std::vector(sizes[0], x);
    } else {
      size_t size = sizes[Nb-1];
      sizes.pop_back();
      return std::vector(size, make_v<Tp, Nb-1>(sizes, x));
    }
  }
}  // detail::

template <typename Tp, size_t Nb>
auto make_v(size_t const(&sizes)[Nb], Tp const& x = Tp()) {
  std::vector<size_t> s(Nb);
  for (size_t i = 0; i < Nb; ++i) s[i] = sizes[Nb-i-1];
  return detail::make_v<Tp, Nb>(s, x);
}
template<class T> bool chmax(T &a, const T &b){if(a<b) {a=b;return 1;}return 0;}
template<class T> bool chmin(T &a, const T &b){if(a>b) {a=b;return 1;}return 0;}
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
void yn(bool ok){
    if(ok) cout << "Yes\n";
    else cout << "No\n";
}

