#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int get_count_everyone_said_yes(string, int);

int main(int argc, char **argv) {
  ifstream input;
  string line;
  string responses;
  int count = 0;

  if (argc < 2) {
    cout << "You gotta enter a filename dude." << endl;
    exit(1);
  }

  input.open(argv[1]);
/*
  while (getline(input, line)) {
    responses += line;
    // Dependent on the last empty line in the input. If no empty line at the
    // end, will give wrong result.
    if (line.empty()) {
      sort(responses.begin(), responses.end());
      responses.erase(unique(responses.begin(), responses.end()),
                      responses.end());
      count += responses.length();
      responses = "";
    }
  }
*/
  responses = "";
  int group_count = 0;
  int counter_for_part_two = 0;
  while (getline(input, line)) {
    responses += line;
    if (line.empty()) {
      sort(responses.begin(), responses.end());
      counter_for_part_two +=
          get_count_everyone_said_yes(responses, group_count - 1);
      group_count = 0;
      responses = "";
    }
    group_count++;
  }

  cout << "count2: " << counter_for_part_two << endl;
  cout << "count1: " << count;
}

int get_count_everyone_said_yes(string str, int i) {
  int a = 0;
  int count = 0;
  int counter = 0;
  cout << "line in func: " << str << endl;
  cout << "group_count: " << i << endl;

  for (a = 0; a < str.length(); a++) {
    if (!a)
      continue;
    if (str.at(a) == str.at(a - 1)) {
      count++;
      if (count == i - 1) {
        counter++;
      }
    } else {
      count = 0;
    }
  }
  cout << "counter: " << counter << endl;

  return counter;
}
