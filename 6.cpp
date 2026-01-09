#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

double F(double x) {
  return x / 3.0 + 20.0 * std::pow(x, 6);
}

double RandDouble(double a, double b) {
  return a + (b - a) * (std::rand() / (double)RAND_MAX);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << "Введите количество тестовых точек. Чем больше точек - тем выш точность и тем медленнее алгоритм" << std::endl;

  int n;
  std::cin >> n;

  if (n <= 0) {
    std::cout << "ошибка\n";
    return 0;
  }

  std::srand((unsigned)std::time(nullptr));

  double x_min = 0.0;
  double x_max = 0.4;
  double y_min = 0.0;
  double y_max = F(x_max);

  int hit = 0;

  for (int i = 0; i < n; ++i) {
    double x = RandDouble(x_min, x_max);
    double y = RandDouble(y_min, y_max);

    if (y <= F(x)) {
      ++hit;
    }
  }

  double rect_area = (x_max - x_min) * (y_max - y_min);
  double s = rect_area * hit / (double)n;

  std::cout << s << "\n";
  return 0;
}
