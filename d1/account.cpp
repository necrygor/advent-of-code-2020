#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream expense_list;
  int expense;
  vector<int> expenses;

  int retval;

  expense_list.open("tt.txt");

  if (expense_list.is_open()) {
    while (expense_list >> expense) {
      expenses.push_back(expense);
    }
    expense_list.close();
  }

  int size = expenses.size();

  for (const int &a : expenses) {
    for (const int &b : expenses) {
      for (const int &c : expenses) {
        if (a + b + c == 2020) {
          retval = a * b * c;
        }
      }
    }
  }

  cout << retval << endl;

  return 0;
}
