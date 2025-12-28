#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

struct Path {
  int sum;
  std::string moves;
};

void RecursionSearch(const std::vector<std::vector<int>>& a, int i, int j,
         int sum, const std::string& moves,
         std::vector<Path>* paths) {
  int k = static_cast<int>(a.size());
  sum += a[i][j];

  if (i == k - 1 && j == k - 1) {
    paths->push_back({sum, moves});
    return;
  }

  if (j + 1 < k) RecursionSearch(a, i, j + 1, sum, moves + "R", paths);
  if (i + 1 < k) RecursionSearch(a, i + 1, j, sum, moves + "D", paths);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int k;
  std::cin >> k;

  std::srand(static_cast<unsigned>(std::time(nullptr)));

  std::vector<std::vector<int>> a(k, std::vector<int>(k));
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      a[i][j] = std::rand() % 10;
    }
  }

  std::cout << "Матрица:\n";
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      std::cout << a[i][j] << " ";
    }
    std::cout << "\n";
  }

  std::vector<Path> paths;
  RecursionSearch(a, 0, 0, 0, "", &paths);

  std::sort(paths.begin(), paths.end(),
            [](const Path& x, const Path& y) {
              if (x.sum != y.sum) return x.sum < y.sum;
              return x.moves < y.moves;
            });

  std::cout << "\nПути по возрастанию суммы:\n";
  for (int i = 0; i < static_cast<int>(paths.size()); ++i) {
    std::cout << paths[i].sum << " " << paths[i].moves << "\n";
  }

  return 0;
}
