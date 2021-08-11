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
  std::vector<std::vector<int>> g;
  g.resize(1 + n);
  std::vector<std::pair<int,int>> edges;
  edges.push_back({0, 0});

  std::vector<int> v(1 + n);
  for(int i = 1;i <= n; i++)
    std::cin >> v[i];

  for(int i = 1;i <= m; i++) {
    int x, y;
    std::cin >> x >> y;
    g[x].push_back(i);
    g[x].push_back(m + i);
    g[y].push_back(i);
    g[y].push_back(m + i);
    edges.push_back({x, y});
  }
  std::cout << "min:";
  for(int i = 1;i <= n; i++)
    std::cout << " + " << v[i] << " " <<  var("x", i);
  std::cout << ";\n";
  
  for(int i = 1;i <= n; i++)
    restrict(var("x", i), 0, 1);
  
  for(int i = 1;i <= m; i++)
    edges.push_back({edges[i].second, edges[i].first});

  for(int i = 1;i <= m; i++) {
    int x = edges[i].first;
    int y = edges[i].second;
    restrict(var("a", i), 0, 1);
    restrict(var("b", i), 0, 1);
    std::cout << 2 << " " << var("a", i) << " + " << var("b", i) << " + " << var("x", x) << " + " << var("x", y) << " = 2;\n";
  }

  restrict("m", 0, m);

  std::cout << "m ";
  for(int i = 1; i <= m; i++)
    std::cout << " - " << var("a", i);
  std::cout << " = 0;\n";
  
  
  for(int i = 1; i <= 2 * m; i++) {
    int x = edges[i].first;
    int y = edges[i].second;
    restrict(var("f", i), 0, n);
    std::cout << var("f", i) << " + " << n << " " << var("x", x) << " <= " << n << ";\n";
    std::cout << var("f", i) << " + " << n << " " << var("x", y) << " <= " << n << ";\n";
  }

  for(int i = 1;i <= n; i++) {
    restrict(var("fin", i), 0, n);
    restrict(var("in", i), 0, 1);
    std::cout << n << " " << var("in", i) << " - " << var("fin", i) << " >= 0;\n";
    std::cout << var("fin", i);
    for(int h = 0; h < g[i].size(); h++) {
      int id = g[i][h];
      if(edges[id].first == i)
        std::cout << " - " << var("f", id);
      else
        std::cout << " + " << var("f", id);
    }
    std::cout << " = 1;\n";
  }

  std::cout << "m ";
  for(int i = 1;i <= n; i++)
    std::cout << " + " << var("in", i);
  std::cout << " = " << n << ";\n";
  make_int();
  
  return 0;
}
