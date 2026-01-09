#include <cstdlib>
#include <ctime>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <fcntl.h>
#include <termios.h>

//termios используется для управления терминалом, переход в raw режим 
struct P { int x, y; };

const int W = 20, H = 12;
termios oldt;
int oldf;

void RawOn() {
  tcgetattr(0, &oldt);
  termios t = oldt;
  t.c_lflag &= ~(ICANON | ECHO | ISIG);
  t.c_iflag &= ~(ICRNL);
  t.c_cc[VMIN] = 0;
  t.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &t);

  oldf = fcntl(0, F_GETFL);
  fcntl(0, F_SETFL, oldf | O_NONBLOCK);
}

void RawOff() {
  tcsetattr(0, TCSANOW, &oldt);
  fcntl(0, F_SETFL, oldf);
}

bool In(const std::vector<P>& s, int x, int y) {
  for (int i = 0; i < (int)s.size(); ++i)
    if (s[i].x == x && s[i].y == y) return true;
  return false;
}

P Food(const std::vector<P>& s) {
  while (true) {
    P f{std::rand() % W, std::rand() % H};
    if (!In(s, f.x, f.y)) return f;
  }
}

void Draw(const std::vector<P>& s, P f, int sc, bool p) {
  std::cout << "\033[2J\033[H"; //очистка экрана 
  std::cout << "Score: " << sc << (p ? " [PAUSE]\n" : "\n");

  for (int y = -1; y <= H; ++y) {
    for (int x = -1; x <= W; ++x) {
      if (x == -1 || x == W || y == -1 || y == H) { std::cout << "#"; continue; }
      if (x == f.x && y == f.y) { std::cout << "*"; continue; }
      bool printed = false;
      for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i].x == x && s[i].y == y) { std::cout << (i == 0 ? "@" : "o"); printed = true; break; }
      }
      if (!printed) std::cout << " ";
    }
    std::cout << "\n";
  }
  std::cout << "WASD - движение | Пробел - пауза | Esc - выход\n" << std::flush;
}

int main() {
  std::srand((unsigned)std::time(nullptr));
  RawOn();
  atexit(RawOff);

  std::vector<P> s(1, {W / 2, H / 2});
  int dx = 1, dy = 0, sc = 0;
  bool pause = false;
  P f = Food(s);

  while (true) {
    char c;
    if (read(0, &c, 1) == 1) {
      if (c == 27) break;
      if (c == ' ') pause = !pause;
      if (!pause) {
        if (c == 'w' || c == 'W') { dx = 0; dy = -1; }
        if (c == 's' || c == 'S') { dx = 0; dy = 1; }
        if (c == 'a' || c == 'A') { dx = -1; dy = 0; }
        if (c == 'd' || c == 'D') { dx = 1; dy = 0; }
      }
    }

    if (!pause) {
      P h = s[0];
      P n{h.x + dx, h.y + dy};

      if (n.x < 0) n.x = W - 1;
      if (n.x >= W) n.x = 0;
      if (n.y < 0) n.y = H - 1;
      if (n.y >= H) n.y = 0;

      if (In(s, n.x, n.y)) {
        Draw(s, f, sc, false);
        std::cout << "\nGAME OVER\n";
        break;
      }

      s.insert(s.begin(), n);

      if (n.x == f.x && n.y == f.y) { sc++; f = Food(s); }
      else s.pop_back();
    }

    Draw(s, f, sc, pause);
    usleep(120000);
  }

  return 0;
}
