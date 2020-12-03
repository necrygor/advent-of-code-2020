#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
  ifstream input;
  string line;
  map<int, string> slope_map;
  int cursor = 0;
  int counter = 0;
  int index = 0;

  input.open("input.txt");

  while (getline(input, line)) {
    slope_map.insert(pair<int, string>(index, line));
    index++;
  }

  cout << "size: " << slope_map.size() << endl;

  for (int i = 0; i < slope_map.size(); i+= 2) {
    int row_length = slope_map.at(i).length();
    cursor += 1;
    cursor %= row_length;
    cout << "i: " << i << endl;
    try {
    if (slope_map.at(i + 2).at(cursor) == '#') {
        counter++;
    }
    } catch (out_of_range oor) {
        cerr << "out of range at: " << i << endl;
    }
  }

  cout << "counter: " << counter << endl;
}
