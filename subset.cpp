#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::pair<int,int>> edges;
  edges.push_back({0, 0});

  std::vector<int> v(1 + n);
  for(int i = 1;i <= n; i++)
    std::cin >> v[i];
  
  for(int i = 1;i <= m; i++) {
    int x, y;
    std::cin >> x >> y;
    edges.push_back({x, y});
  }

  std::cout << "min:";
  for(int i = 1;i <= n; i++)
    std::cout << " + " << v[i] << " " <<  var("x", i);
  std::cout << ";\n";

  for(int i = 1;i <= n; i++)
    restrict(var("x", i), 0, 1);
  for(int i = 1;i <= m; i++) {
    int x = edges[i].first;
    int y = edges[i].second;
    restrict(var("a", i), 0, 1);
    restrict(var("b", i), 0, 1);
    std::cout << 2 << " " << var("a", i) << " + " << var("b", i) << " + " << var("x", x) << " + " << var("x", y) << " = 2;\n";
  }

  for(int mask = 1; mask < (1 << n); mask++) {
    int verdict = false;
    for(int i = 1; i <= m; i++)
      if((mask & (1 << (edges[i].first - 1))) && (mask & (1 << (edges[i].second - 1)))){
        std::cout << " + " << var("a", i);
        verdict = true;
      }
    if(verdict == true)
      std::cout << " <= " << __builtin_popcount(mask) - 1 << ";\n";
  }

  make_int();
}
