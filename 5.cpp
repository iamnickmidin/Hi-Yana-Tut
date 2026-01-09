#include <iostream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int x;
  std::cin >> x;

  if (x <= 0) {
    std::cout << "ошибка\n";
    return 0;
  }

  std::vector<std::vector<long long>> a(x, std::vector<long long>(x, 1));

  for (int i = 1; i < x; ++i) {
    for (int j = 1; j < x; ++j) {
      a[i][j] = a[i - 1][j] + a[i][j - 1];
    }
  }

  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < x; ++j) {
      std::cout << a[i][j] << (j + 1 == x ? '\n' : ' ');
    }
  }

  return 0;
}
