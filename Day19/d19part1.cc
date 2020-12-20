/**
 * @file d19part1.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-18
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 19: Monster Messages ---
 * You land in an airport surrounded by dense forest. As you walk to your high-speed train, the Elves at the Mythical Information Bureau contact you again. They think their satellite has collected an image of a sea monster! Unfortunately, the connection to the satellite is having problems, and many of the messages sent back from the satellite have been corrupted.
 * 
 * They sent you a list of the rules valid messages should obey and a list of received messages they've collected so far (your puzzle input).
 * 
 * The rules for valid messages (the top part of your puzzle input) are numbered and build upon each other. For example:
 * 
 * 0: 1 2
 * 1: "a"
 * 2: 1 3 | 3 1
 * 3: "b"
 * Some rules, like 3: "b", simply match a single character (in this case, b).
 * 
 * The remaining rules list the sub-rules that must be followed; for example, the rule 0: 1 2 means that to match rule 0, the text being checked must match rule 1, and the text after the part that matched rule 1 must then match rule 2.
 * 
 * Some of the rules have multiple lists of sub-rules separated by a pipe (|). This means that at least one list of sub-rules must match. (The ones that match might be different each time the rule is encountered.) For example, the rule 2: 1 3 | 3 1 means that to match rule 2, the text being checked must match rule 1 followed by rule 3 or it must match rule 3 followed by rule 1.
 * 
 * Fortunately, there are no loops in the rules, so the list of possible matches will be finite. Since rule 1 matches a and rule 3 matches b, rule 2 matches either ab or ba. Therefore, rule 0 matches aab or aba.
 * 
 * Here's a more interesting example:
 * 
 * 0: 4 1 5
 * 1: 2 3 | 3 2
 * 2: 4 4 | 5 5
 * 3: 4 5 | 5 4
 * 4: "a"
 * 5: "b"
 * Here, because rule 4 matches a and rule 5 matches b, rule 2 matches two letters that are the same (aa or bb), and rule 3 matches two letters that are different (ab or ba).
 * 
 * Since rule 1 matches rules 2 and 3 once each in either order, it must match two pairs of letters, one pair with matching letters and one pair with different letters. This leaves eight possibilities: aaab, aaba, bbab, bbba, abaa, abbb, baaa, or babb.
 * 
 * Rule 0, therefore, matches a (rule 4), then any of the eight options from rule 1, then b (rule 5): aaaabb, aaabab, abbabb, abbbab, aabaab, aabbbb, abaaab, or ababbb.
 * 
 * The received messages (the bottom part of your puzzle input) need to be checked against the rules so you can determine which are valid and which are corrupted. Including the rules and the messages together, this might look like:
 * 
 * 0: 4 1 5
 * 1: 2 3 | 3 2
 * 2: 4 4 | 5 5
 * 3: 4 5 | 5 4
 * 4: "a"
 * 5: "b"
 * 
 * ababbb
 * bababa
 * abbbab
 * aaabbb
 * aaaabbb
 * Your goal is to determine the number of messages that completely match rule 0. In the above example, ababbb and abbbab match, but bababa, aaabbb, and aaaabbb do not, producing the answer 2. The whole message must match all of rule 0; there can't be extra unmatched characters in the message. (For example, aaaabbb might appear to match rule 0 above, but it has an extra unmatched b on the end.)
 * 
 * How many messages completely match rule 0?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

// Struct to hold rule options
struct opt {
    int a;
    int b;
    int c;
    char d;

    opt(string s) {
        // If rule is a character, set a, b, c to -1
        if (s[0] == '"') {
           d = s[1];
           a = -1;
           b = -1;
           c = -1; 
        } else {
            // Set a, b, c (if applicable) to next rules
            stringstream ss(s);
            int t;
            if (ss >> t) {
                a = t;
            } else {
                a = -1;
            }
            if (ss >> t) {
                b = t;
            } else {
                b = -1;
            }
            if (ss >> t) {
                c = t;
            } else {
                c = -1;
            }
            d = ' ';
        }
    }
};

// Tests string
bool test(string& s, unordered_map<int, vector<opt*>*>& v, int& index, int rule);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    unordered_map<int, vector<opt*>*> v;
    string s;
    // Parse rules
    while (std::getline(input, s)) {
        if (s == "") {
            break;
        }
        stringstream ss(s);
        string token;
        ss >> token;
        int rule = stoi(token.substr(0, token.length() - 1));
        // Add rules to map
        v[rule] = new vector<opt*>();
        while (getline(ss, token, '|')) {
            v[rule]->push_back(new opt(token.substr(1)));
        }
    }
    // Count rules
    int count = 0;
    while (std::getline(input, s)) {
        int index = 0;
        if (test(s, v, index, 0) && index == s.size()) {
            count++;
        }
    }
    cout << "Count: " << count << endl;
    // Free memory
    for (auto i: v) {
        for (auto j: *(i.second)) {
            delete j;
        }
        delete i.second;
    }
    return 0;
}

bool test(string& s, unordered_map<int, vector<opt*>*>& v, int& index, int rule) {
    if (index >= s.size()) {
        return false;
    }
    // Reached a character
    if (v[rule]->at(0)->a == -1 && v[rule]->at(0)->b == -1  && v[rule]->at(0)->c == -1) {
        if (v[rule]->at(0)->d != s[index]) {
            return false;
        }
        index++;
        return true;
    }
    // Process all of the opts in vector of rules
    for (auto i: *(v[rule])) {
        int temp = index;
        bool rv = true;
        if (i->a != -1) {
            rv &= test(s, v, temp, i->a);
        }
        if (i->b != -1) {
            rv &= test(s, v, temp, i->b);
        }
        if (i->c != -1) {
            rv &= test(s, v, temp, i->c);
        }
        if (rv) {
            index = temp;
            return true;
        }
    }
    return false;
}   