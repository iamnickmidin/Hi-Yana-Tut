#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

double RoundToHundredths(double x) {
  return std::round(x * 100.0) / 100.0;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string filename;
  std::getline(std::cin, filename);

  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cout << "ошибка\n";
    return 0;
  }

  std::vector<double> values;
  double x = 0.0;
  while (fin >> x) {
    double squared = x * x;
    values.push_back(RoundToHundredths(squared));
  }
  fin.close();

  std::ofstream fout(filename, std::ios::trunc);
  if (!fout.is_open()) {
    std::cout << "ошибка\n";
    return 0;
  }

  fout << std::fixed << std::setprecision(2);
  for (int i = 0; i < static_cast<int>(values.size()); ++i) {
    if (i > 0) {
      fout << " ";
    }
    fout << values[i];
  }
  fout << "\n";

  fout.close();
  return 0;
}
