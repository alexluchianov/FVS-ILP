#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using ll = long long;

std::string var(std::string name, int id) {
  return name + std::to_string(id);
}

std::vector<std::string> variable_list;

void restrict(std::string name, int from, int to) {
  std::cout << name << " >= " << from << ";\n";
  std::cout << name << " <= " << to << ";\n";
  variable_list.push_back(name);  
}

void make_int() {
  std::cout << "int ";
  for(int i = 0; i < variable_list.size(); i++) {
    if(0 < i)
      std::cout << ", ";
    std::cout << variable_list[i] << " ";
  }
  std::cout << ";\n";
}

int const nmax = 17;
int mat[1 + nmax][1 + nmax];
int dp[(1 << nmax)][1 + nmax][1 + nmax];

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> v(1 + n);
  for(int i = 1; i <= n; i++)
    std::cin >> v[i];
  std::vector<std::pair<int,int>> edges;
  edges.push_back({0, 0});
  for(int i = 1; i <= m; i++) {
    int x, y;
    std::cin >> x >> y;
    edges.push_back({x, y});
    mat[x - 1][y - 1] = mat[y - 1][x - 1] = 1;
  }

  std::cout << "min: ";
  for(int i = 1; i <= n; i++) {
    std::cout << " + " << v[i] << " " << var("x", i);
  }
  std::cout << ";\n";
  
  for(int i = 1; i <= n; i++)
    restrict(var("x", i), 0, 1);

  for(int i = 0; i < n; i++)
    dp[(1 << i)][i][i] = 1;
  for(int mask = 1; mask < (1 << n); mask++) {
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
        if(0 < dp[mask][i][j]) {
          for(int h = 0; h < n; h++)
            if(mat[j][h] && 0 == (mask & (1 << h)))
              dp[mask | (1 << h)][i][h] = 1;
        }
  }

  for(int mask = 1; mask < (1 << n); mask++) {
    if(3 <= __builtin_popcount(mask)) {
      bool verdict = false;
      for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
          verdict |= (dp[mask][i][j] & mat[i][j]);
      if(verdict == true) {
        for(int i = 0; i < n; i++)
          if(mask & (1 << i))
            std::cout << " + " << var("x", i + 1) << " ";
        std::cout << " >= 1;\n";
      }
    }
  }
  make_int();
  return 0;
}
