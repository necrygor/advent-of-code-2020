#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool check_if_passes(string);
pair<string, string> divide_the_line(string);

int main() {
  string line;
  ifstream input_list;
  map<int, string> pass_list;
  int i = 0;

  input_list.open("input.txt");

  while (getline(input_list, line)) {
    if (check_if_passes(line)) {
      pass_list.insert(std::pair<int, string>(i, line));
    }
    i++;
  }
  
  cout << "size of vector is: " << pass_list.size() << endl;
}

bool check_if_passes(string line) {
  pair<string, string> pol_code = divide_the_line(line);
  string first = pol_code.first;
  string password = pol_code.second;

  auto control_char = first.substr(first.find(' ') + 1);
  auto occurences = first.substr(0, first.find(' '));

  auto min_occurence = std::stoi(occurences.substr(0, occurences.find('-')));
  auto max_occurence = std::stoi(occurences.substr(occurences.find('-') + 1));

  /* first part
  int i = 0;

  for (char const &c : password) {
    if (c == control_char[0]) {
      i++;
    }
  }
  if (i >= min_occurence && i <= max_occurence) {
    cout << "TRUE "
         << "he bu da i: " << i << " min_occurence: " << min_occurence
         << " max_occurence: " << max_occurence
         << " control_char[0]: " << control_char[0] << " password: " << password
         << endl;
    return true;
  } else {
    return false;
  }
  */

  // second part
  bool char_in_at_least_one_position =
      (password.at(min_occurence) == control_char[0] ||
       password.at(max_occurence) == control_char[0]);
  bool char_in_both_positions =
      (password.at(min_occurence) == control_char[0] &&
       password.at(max_occurence) == control_char[0]);

  cout << "--------------------------------------------------" << endl
       << "password:" << password << endl
       << "control_char: " << control_char << endl
       << "first_pos: " << min_occurence - 1 << endl
       << "second_pos: " << max_occurence - 1 << endl
       << "line at " << min_occurence << " : " << password.at(min_occurence)
       << endl
       << "line at " << max_occurence << " : " << password.at(max_occurence)
       << endl
       << "char_in_at_least_one_position: " << char_in_at_least_one_position
       << endl
       << "char_in_both_positions: " << char_in_both_positions << endl
       << endl;

  if (char_in_at_least_one_position && !char_in_both_positions) {
    return true;
  } else {
    return false;
  }
}

pair<string, string> divide_the_line(string line) {
  pair<string, string> pol_code;

  int pos = line.find(':');
  pol_code.first = line.substr(0, pos);
  pol_code.second = line.substr(pos + 1);

  return pol_code;
}
