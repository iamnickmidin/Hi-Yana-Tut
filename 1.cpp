#include <cctype>
#include <iostream>
#include <string>

bool IsDigit(char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  while (true) {
    std::string s;
    std::getline(std::cin, s);

    long long result = 0;
    long long number = 0;

    int sign = 1;
    bool ok = true;
    bool need_number = true;

    for (int i = 0; i < static_cast<int>(s.size()); ++i) {
      char c = s[i];

      if (std::isspace(static_cast<unsigned char>(c))) {
        continue;
      }

      if (c == '+' || c == '-') {
        if (need_number) {
          sign = (c == '+') ? 1 : -1;
        } else {
          result += sign * number;
          number = 0;
          sign = (c == '+') ? 1 : -1;
          need_number = true;
        }
      } else if (IsDigit(c)) {
        number = number * 10 + (c - '0');
        need_number = false;
      } else {
        ok = false;
        break;
      }
    }

    if (ok && !need_number) {
      result += sign * number;
      std::cout << result << "\n";
      break;
    }

    std::cout << "ошибка\n";
  }

  return 0;
}
