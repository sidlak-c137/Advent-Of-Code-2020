/**
 * @file d16part2.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-16
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 16: Ticket Translation ---
 * As you're walking to yet another connecting flight, you realize that one of the legs of your re-routed trip coming up is on a high-speed train. However, the train ticket you were given is in a language you don't understand. You should probably figure out what it says before you get to the train station after the next flight.
 * 
 * Unfortunately, you can't actually read the words on the ticket. You can, however, read the numbers, and so you figure out the fields these tickets must have and the valid ranges for values in those fields.
 * 
 * You collect the rules for ticket fields, the numbers on your ticket, and the numbers on other nearby tickets for the same train service (via the airport security cameras) together into a single document you can reference (your puzzle input).
 * 
 * The rules for ticket fields specify a list of fields that exist somewhere on the ticket and the valid ranges of values for each field. For example, a rule like class: 1-3 or 5-7 means that one of the fields in every ticket is named class and can be any value in the ranges 1-3 or 5-7 (inclusive, such that 3 and 5 are both valid in this field, but 4 is not).
 * 
 * Each ticket is represented by a single line of comma-separated values. The values are the numbers on the ticket in the order they appear; every ticket has the same format. For example, consider this ticket:
 * 
 * .--------------------------------------------------------.
 * | ????: 101    ?????: 102   ??????????: 103     ???: 104 |
 * |                                                        |
 * | ??: 301  ??: 302             ???????: 303      ??????? |
 * | ??: 401  ??: 402           ???? ????: 403    ????????? |
 * '--------------------------------------------------------'
 * Here, ? represents text in a language you don't understand. This ticket might be represented as 101,102,103,104,301,302,303,401,402,403; of course, the actual train tickets you're looking at are much more complicated. In any case, you've extracted just the numbers in such a way that the first number is always the same specific field, the second number is always a different specific field, and so on - you just don't know what each position actually means!
 * 
 * Start by determining which tickets are completely invalid; these are tickets that contain values which aren't valid for any field. Ignore your ticket for now.
 * 
 * For example, suppose you have the following notes:
 * 
 * class: 1-3 or 5-7
 * row: 6-11 or 33-44
 * seat: 13-40 or 45-50
 * 
 * your ticket:
 * 7,1,14
 * 
 * nearby tickets:
 * 7,3,47
 * 40,4,50
 * 55,2,20
 * 38,6,12
 * It doesn't matter which position corresponds to which field; you can identify invalid nearby tickets by considering only whether tickets contain values that are not valid for any field. In this example, the values on the first nearby ticket are all valid for at least one field. This is not true of the other three nearby tickets: the values 4, 55, and 12 are are not valid for any field. Adding together all of the invalid values produces your ticket scanning error rate: 4 + 55 + 12 = 71.
 * 
 * Consider the validity of the nearby tickets you scanned. What is your ticket scanning error rate?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

// Struct for ranges
struct Range {
    int min1;
    int max1;
    int min2;
    int max2;
};

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    vector<int> nums;
    // Get ranges
    vector<Range*> ranges;
    string s;
    while (std::getline(input, s)) {
        if (s == "") {
            break;
        } else {
            stringstream ss(s);
            string name;
            ss >> name;
            while (name[name.size() - 1] != ':') {
                ss >> name;
            }
            Range* r = new Range();
            string r1;
            ss >> r1;
            int pos =  r1.find('-');
            r->min1 = stoi(r1.substr(0,pos));
            r->max1 = stoi(r1.substr(pos + 1));
            string or;
            ss >> or;
            string r2;
            ss >> r2;
            pos =  r2.find('-');
            r->min2 = stoi(r2.substr(0,pos));
            r->max2 = stoi(r2.substr(pos + 1));
            ranges.push_back(r);
        }
    }
    std::getline(input, s);
    std::getline(input, s);
    std::getline(input, s);
    std::getline(input, s);
    // Get and check nearby tickets
    int sum = 0;
    while (std::getline(input, s)) {
        int token;
        int pos;
        while ((pos = s.find(',')) != string::npos) {
            token = stoi(s.substr(0, pos));
            nums.push_back(token);
            s.erase(0, pos + 1);
        }
        nums.push_back(stoi(s));
        // Check for invalid numbers
        for (auto n: nums) {
            bool check = false;
            for (auto r: ranges) {
                if ((n >= r->min1 && n <= r->max1) || (n >= r->min2 && n <= r->max2)) {
                    check = true;
                    break;
                }
            }
            if (!check) {
                sum += n;
            }
        }
        nums.clear();
    }
    // Print sum
    cout << "Sum: " << sum << endl;
    // Free memory
    for (auto r: ranges) {
        delete r;
    }
    return 0;
}