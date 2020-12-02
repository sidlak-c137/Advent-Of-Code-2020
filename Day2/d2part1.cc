/**
 * @file d2part1.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-01
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 2: Password Philosophy ---
 * Your flight departs in a few days from the coastal airport; the easiest way down to the coast from here is via toboggan.
 * 
 * The shopkeeper at the North Pole Toboggan Rental Shop is having a bad day. "Something's wrong with our computers; we can't log in!" You ask if you can take a look.
 * 
 * Their password database seems to be a little corrupted: some of the passwords wouldn't have been allowed by the Official Toboggan Corporate Policy that was in effect when they were chosen.
 * 
 * To try to debug the problem, they have created a list (your puzzle input) of passwords (according to the corrupted database) and the corporate policy when that password was set.
 * 
 * For example, suppose you have the following list:
 * 
 * 1-3 a: abcde
 * 1-3 b: cdefg
 * 2-9 c: ccccccccc
 * Each line gives the password policy and then the password. The password policy indicates the lowest and highest number of times a given letter must appear for the password to be valid. For example, 1-3 a means that the password must contain a at least 1 time and at most 3 times.
 * 
 * In the above example, 2 passwords are valid. The middle password, cdefg, is not; it contains no instances of b, but needs at least 1. The first and third passwords are valid: they contain one a or nine c, both within the limits of their respective policies.
 * 
 * How many passwords are valid according to their policies?
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

// Check if password is valid
bool isValid(char c, string password, int min, int max);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    // Add lines to a vector
    string str;
    vector<string> vec;
    while (getline(input, str)){
        vec.push_back(str); 
    }
    // Count for valid passwords
    int count = 0;
    for (auto str : vec) {
        // Parse each line into parts
        vector<string> parts;
        stringstream ss(str);
        string s;
        while (ss >> s) {
            parts.push_back(s);
        }
        char c = parts[1].at(0);
        string password = parts[2];
        // Parse numbers
        stringstream st(parts[0]);
        vector<string> out;
        while (getline(st, s, '-')) {
            out.push_back(s);
        }
        int min = stoi(out[0]);
        int max = stoi(out[1]);
        // Check validity of password
        if (isValid(c, password, min, max)) {
            count++;
        }
    }
    // Print number of valid passwords
    cout << count << endl;
    return 0;
}

bool isValid(char c, string password, int min, int max) {
    // Count occurrences of the target letter
    int count = 0;
    for (string::iterator it = password.begin(); it < password.end(); it++) {
        if (*it == c) {
            count++;
        }
    }
    return count >= min && count <= max;
}
