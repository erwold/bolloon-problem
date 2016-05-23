#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Balloon {
  double r;
  double x, y;
};

constexpr double kXMax = 1.0;
constexpr double kXMin = -1.0;
constexpr double kYMax = 1.0;
constexpr double kYMin = -1.0;

bool IsConflict(const Balloon& now, const vector<Balloon> &balloons) {
  for (auto &other : balloons) {
    double dist2 = (now.x - other.x)*(now.x - other.x)
                 + (now.y - other.y)*(now.y - other.y);
    if (sqrt(dist2) < abs(now.r + other.r)) {
      return true;
    }
  }
  return false;
}

double Solve(size_t num, vector<Balloon> &balloons) {

  double delta = (kXMax - kXMin) / 2.0f;
  double eps = 0.001;
  double xbase = 0.0, ybase = 0.0;
  while (0 != num) {
    num -= 1;
    Balloon now {-1.0, 0.0, 0.0};

    while (delta > eps) {
      // search right
      xbase = -1.0f;
      ybase = -1.0f;

      while (xbase+delta <= kXMax) {
        xbase += delta;
        double r = delta;
        for (int iter = 0; iter < 10; ++iter) {
          cout << "right " << iter << endl;
          if (r < now.r) {
            break;
          }
          if (!IsConflict({r, xbase, ybase+r}, balloons) && r > now.r) {
            now = {r, xbase, ybase+r};
            cout << now.r << " " << now.x << " " << now.y << endl;
          }
          r *= 0.5;
        }
      }

      // search up
      xbase = 1.0f;
      ybase = -1.0f;

      while (ybase+delta <= kYMax) {
        ybase += delta;
        double r = delta;
        for (int iter = 0; iter < 10; ++iter) {
          cout << "up " << iter << endl;
          if (r < now.r) {
            break;
          }
          if (!IsConflict({r, xbase-r, ybase}, balloons) && r > now.r) {
            now = {r, xbase-r, ybase};
            cout << now.r << " " << now.x << " " << now.y << endl;
          }
          r = 0.5;
        }
      }

      // search left
      xbase = 1.0f;
      ybase = 1.0f;

      while (xbase-delta >= kXMin) {
        xbase -= delta;
        double r = delta;
        for (int iter = 0; iter < 10; ++iter) {
          cout << "left " << iter << endl;
          if (r < now.r) {
            break;
          }
          if (!IsConflict({r, xbase, ybase-r}, balloons) && r > now.r) {
            now = {r, xbase, ybase-r};
            cout << now.r << " " << now.x << " " << now.y << endl;
          }
          r *= 0.5;
        }
      }

      // search down
      xbase = -1.0f;
      ybase = 1.0f;

      while (ybase-delta >= kYMin) {
        ybase -= delta;
        double r = delta;
        for (int iter = 0; iter < 10; ++iter) {
          cout << "down " << iter << endl;
          if (r < now.r) {
            break;
          }
          if (!IsConflict({r, xbase+r, ybase}, balloons) && r > now.r) {
            now = {r, xbase+r, ybase};
            cout << now.r << " " << now.x << " " << now.y << endl;
          }
          r *= 0.5;
        }
      }

      if (now.r > 0.0) {
        break;
      } else {
        delta *= 0.5;
      }
    }

    balloons.push_back(now);
  }

  return 0.0;
}

int main() {
  vector<Balloon> balloons;
  int num = 0;
  cin >> num;
  double sum = Solve(num, balloons);
  sum = 0.0;
  for (auto &b : balloons) {
    cout << b.r << " " << b.x << " " << b.y << endl;
    sum += b.r * b.r;
  }
  cout << "sum: " << sum << endl;
  return 0;
}

