#include <bitset>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

long determine_row(const string &);
long determine_col(const string &);

int main(int argc, char **argv) {
  ifstream input;
  string line;
  int seat_id = 0;
  int highest_seat_id = 0;
  vector<int> seats;
  int user_seat = 0;

  if (argc < 2) {
    cout << "Please enter a filename for input." << endl;
    return 2;
  }

  input.open(argv[1]);

  while (getline(input, line)) {
    string row_part = line.substr(0, 7);
    string col_part = line.substr(7, 3);

    int row = determine_row(row_part);
    int col = determine_col(col_part);

    seat_id = (row * 8) + col;
    seats.push_back(seat_id);
    if(seat_id > highest_seat_id) {
      highest_seat_id = seat_id;
    }
  }

  cout << "highest_seat: " << highest_seat_id << endl;
  for(int i = 0; i < seats.size(); i++) {
    if(seats[i] != seats[i - 1] + 1) user_seat = seats[i] - 1;
  }

  cout << "seat: " << user_seat << endl;
}

long determine_row(const string &line) {
  bitset<7> row;
  int i = 6;
  for (auto &c : line) {
    if (c == 'B') {
      row[i] = 1;
    } else if(c == 'F') {
      row[i] = 0;
    }
    i--;
  }
  long retval = row.to_ulong();
  return retval;
}

long determine_col(const string &line) { 
  bitset<3> row;
  int i = 2;
  for (auto &c : line) {
    if (c == 'R') {
      row[i] = 1;
    } else if (c == 'L') {
      row[i] = 0;
    }
    i--;
  }
  long retval = row.to_ulong();
  return retval;
}
