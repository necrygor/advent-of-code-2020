#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

const vector<string> valid_eye_colors = {"amb", "blu", "brn", "gry",
                                         "grn", "hzl", "oth"};
const vector<char> allowed_chars = {'a', 'b', 'c', 'd', 'e', 'f'};

struct passport {
  int byr = 314314; // Birth Year
  int iyr = 314314; // Issue Year
  int eyr = 314314; // Expiration Year
  string hgt = "i"; // Height
  string pid = "i"; // Passport ID
  int cid = 314314; // Country ID
  string hcl = "i"; // Hair Color
  string ecl = "i"; // Eye Color
};

bool further_validation_for_passport(passport);
void print_out_passport(const passport &);
bool validate_passport(passport);
passport devise_passport(string);
string ltrim(const string &);
string rtrim(const string &);
string trim(const string &);

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "You need to enter and at least one argument so that we can "
            "determine the name of input file. Fair enough?"
         << endl;
    return 217;
  }

  vector<passport> documents;
  vector<passport> further_validated;
  ifstream input;
  string line;
  vector<string> indexed_input;
  string subline = "";
  int i = 0;
  int k = 0;

  input.open(argv[1]);

  while (getline(input, line)) {
    if (line.empty()) {
      indexed_input.push_back(subline);
      subline = "";
      continue;
    }
    subline += " " + line;
  }
  for (const string &s : indexed_input) {
    string a = trim(s);
    documents.push_back(devise_passport(a));
  }

  for (passport const &p : documents) {
    bool state = validate_passport(p);

    further_validated.push_back(p);
    if (state) {
      i++;
    }
  }

  for (passport const &p : further_validated) {
    bool further_state = further_validation_for_passport(p);

    if (further_state) {
      cout << "state is true: " << further_state << endl;
      print_out_passport(p);
      k++;
    }
  }

  cout << "number of valid passports: " << i << endl;
  cout << "number of further validated passporst: " << k << endl;
  return 0;
}

bool validate_passport(passport p) {
  if (p.byr == 314314 || p.iyr == 314314 || p.eyr == 314314 || p.hgt == "i" ||
      p.pid == "i" || p.hcl == "i" || p.ecl == "i") {
    return false; // initialized with default values, if not changes then it is
                  // invalid
  }
  return true;
}

passport devise_passport(string line) {
  passport t;
  string s;
  string a;
  char c = ' ';
  int pos = line.find(c);
  int initial_pos = 0;
  vector<string> temp;

  stringstream ss(line);

  while (ss >> a) {
    temp.push_back(a);
  }

  for (const string &s : temp) {
    try {

      if (s.find("byr") != string::npos)
        t.byr = stoi(s.substr(s.find(':') + 1));

      if (s.find("iyr") != string::npos)
        t.iyr = stoi(s.substr(s.find(':') + 1));

      if (s.find("eyr") != string::npos)
        t.eyr = stoi(s.substr(s.find(':') + 1));

      if (s.find("hgt") != string::npos)
        t.hgt = s.substr(s.find(':') + 1);

      if (s.find("hcl") != string::npos)
        t.hcl = s.substr(s.find(':') + 1);

      if (s.find("ecl") != string::npos)
        t.ecl = s.substr(s.find(':') + 1);

      if (s.find("pid") != string::npos)
        t.pid = s.substr(s.find(':') + 1);

      if (s.find("cid") != string::npos)
        t.cid = stoi(s.substr(s.find(':') + 1));
    } catch (const invalid_argument &ia) {
      cout << "inside ia: " << s.substr(s.find(':') + 1);
      cout << "ia: " << ia.what() << endl;
    }
  }

  return t;
}

string ltrim(const string &s) {
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == string::npos) ? "" : s.substr(start);
}

string rtrim(const string &s) {
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == string::npos) ? "" : s.substr(0, end + 1);
}

string trim(const string &s) { return rtrim(ltrim(s)); }

void print_out_passport(const passport &t) {
  cout << "---------------------------------" << endl;
  cout << "p.byr: " << t.byr << endl;
  cout << "p.iyr: " << t.iyr << endl;
  cout << "p.eyr: " << t.eyr << endl;
  cout << "p.hgt: " << t.hgt << endl;
  cout << "p.pid: " << t.pid << endl;
  cout << "p.cid: " << t.cid << endl;
  cout << "p.hcl: " << t.hcl << endl;
  cout << "p.ecl: " << t.ecl << endl;
  cout << "---------------------------------" << endl;
}

bool further_validation_for_passport(passport p) {
  if (p.byr < 1920 || p.byr > 2002) {
    return false;
  }

  if (p.iyr < 2010 || p.iyr > 2020) {
    return false;
  }

  if (p.eyr < 2020 || p.eyr > 2030) {
    return false;
  }

  if (p.hgt.find("cm") != string::npos) {
    int height = stoi(p.hgt.substr(0, p.hgt.find('c')));
    if (height > 193 || height < 150) {
      return false;
    }
  } else if (p.hgt.find("in") != string::npos) {
    int height = stoi(p.hgt.substr(0, p.hgt.find('i')));
    if (height < 59 || height > 76) {
      return false;
    }
  } else {
    return false;
  }

  if (p.hcl.find('#') != string::npos) {
    if (p.hcl.length() != 7) {
      return false;
    }
    for (const int &c : p.hcl) {
      if (c == 35) {
        continue;
      }
      if (!(c >= 48 && c <= 57) && !(c >= 97 && c <= 102)) {
        cout << "int c: " << c << endl;
        return false;
      }
    }
  } else {
    return false;
  }

  if (!any_of(valid_eye_colors.begin(), valid_eye_colors.end(),
              [&](string color) { return color == p.ecl; })) {
    cout << "invalid p.ecl: " << p.ecl << endl;
    return false;
  }

  // p.pid.erase(0, p.pid.find_first_not_of('0'));
  cout << "p.pid: " << p.pid << endl;

  if (p.pid.length() != 9) {
    return false;
  }

  cout << "after p.pid test " << endl;
  return true;
}
