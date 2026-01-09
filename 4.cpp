#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

bool IsAsciiWord(unsigned char c) {
  return std::isalnum(c) != 0;
}

bool IsRussianLetter(const std::string& s, int i) {
  if (i + 1 >= static_cast<int>(s.size())) return false;
  unsigned char a = static_cast<unsigned char>(s[i]);
  unsigned char b = static_cast<unsigned char>(s[i + 1]);

  // А-Я:
  if (a == 0xD0 && b >= 0x90 && b <= 0xAF) return true;

  // а-п:
  if (a == 0xD0 && b >= 0xB0 && b <= 0xBF) return true;

  // Р-Я:
  if (a == 0xD0 && b >= 0xA0 && b <= 0xAF) return true;

  // р-я:
  if (a == 0xD1 && b >= 0x80 && b <= 0x8F) return true;

  // Ё:
  if (a == 0xD0 && b == 0x81) return true;

  // ё:
  if (a == 0xD1 && b == 0x91) return true;

  return false;
}
void MakeRussianUpper(std::string* s, int i) {
  unsigned char& a = reinterpret_cast<unsigned char&>((*s)[i]);
  unsigned char& b = reinterpret_cast<unsigned char&>((*s)[i + 1]);

  // ё - Ё
  if (a == 0xD1 && b == 0x91) {
    a = 0xD0;
    b = 0x81;
    return;
  }

  // а-п: D0 B0..BF - D0 90..9F
  if (a == 0xD0 && b >= 0xB0 && b <= 0xBF) {
    b -= 0x20;
    return;
  }

  // р-я: D1 80..8F - D0 A0..AF
  if (a == 0xD1 && b >= 0x80 && b <= 0x8F) {
    a = 0xD0;
    b += 0x20;
    return;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string filename;
  std::getline(std::cin, filename);

  std::ifstream fin(filename, std::ios::binary);
  if (!fin.is_open()) {
    std::cout << "ошибка\n";
    return 0;
  }

  std::string out_name = "out_" + filename;
  std::ofstream fout(out_name, std::ios::binary);
  if (!fout.is_open()) {
    std::cout << "ошибка\n";
    return 0;
  }

  std::string text((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());

  bool new_word = true;

  for (int i = 0; i < static_cast<int>(text.size()); ++i) {
    unsigned char c = static_cast<unsigned char>(text[i]);
    if (c < 128 && IsAsciiWord(c)) {
      if (new_word) {
        text[i] = static_cast<char>(std::toupper(c));
        new_word = false;
      }
      continue;
    }
    if (IsRussianLetter(text, i)) {
      if (new_word) {
        MakeRussianUpper(&text, i);
        new_word = false;
      }
      ++i;
      continue;
    }

    new_word = true;
  }

  fout << text;
  std::cout << "Готово: " << out_name << "\n";
  return 0;
}
