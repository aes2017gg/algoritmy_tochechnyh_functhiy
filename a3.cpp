#include <iostream>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::vector;

const int cMax = 1e9 + 7;

struct Sparce {
  vector<vector<int> > sparce;
  vector<vector<int> > ind;
  int sz;
  Sparce(int num = 1) {
    int deg = 1;
    sz = num;
    for (int i = 1; i < num; i = i * 2) {
      deg++;
    }
    sparce.resize(deg);
    ind.resize(deg);
    for (int i = 0; i < deg; i++) {
      sparce[i].resize(num);
      ind[i].resize(num);
    }
  }

  void Create(vector<int>& arr) {
    for (int i = 0; i < sz; i++) {
      sparce[0][i] = arr[i];
      ind[0][i] = i;
    }
    int pow = 1;
    for (int i = 1; i < (int)sparce.size(); i++) {
      for (int j = 0; j < sz - pow; j++) {
        sparce[i][j] = std::min(sparce[i - 1][j], sparce[i - 1][j + pow]);
        if (sparce[i][j] == sparce[i - 1][j]) {
          ind[i][j] = ind[i - 1][j];
        } else {
          ind[i][j] = ind[i - 1][j + pow];
        }
      }
      pow = pow * 2;
    }
  }

  int Get(int l, int r) {
    int deg = 0;
    int pow = 1;
    while (2 * pow <= r - l) {
      deg++;
      pow = pow * 2;
    }
    if (sparce[deg][l] < sparce[deg][r - pow + 1]) {
      return ind[deg][l];
    }
    return ind[deg][r - pow + 1];
  }
};

int main() {
  int num;
  int que;
  cin >> num >> que;
  vector<int> arr(num);
  for (int i = 0; i < num; i++) {
    cin >> arr[i];
  }
  Sparce sparce(num);
  sparce.Create(arr);
  que++;
  while (--que > 0) {
    int l;
    int r;
    cin >> l >> r;
    l--;
    r--;
    int mid = sparce.Get(l, r);
    int lmin = cMax;
    int rmin = cMax;
    if (l < mid) {
      lmin = sparce.sparce[0][sparce.Get(l, mid - 1)];
    }
    if (r > mid) {
      rmin = sparce.sparce[0][sparce.Get(mid + 1, r)];
    }
    cout << std::min(lmin, rmin) << '\n';
    cerr << l << ' ' << r << ' ' << lmin << ' ' << rmin << ' ' << mid << '\n';
  }
  return 0;
}
