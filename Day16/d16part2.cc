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
 * 
 * --- Part Two ---
 * Now that you've identified which tickets contain invalid values, discard those tickets entirely. Use the remaining valid tickets to determine which field is which.
 * 
 * Using the valid ranges for each field, determine what order the fields appear on the tickets. The order is consistent between all tickets: if seat is the third field, it is the third field on every ticket, including your ticket.
 * 
 * For example, suppose you have the following notes:
 * 
 * class: 0-1 or 4-19
 * row: 0-5 or 8-19
 * seat: 0-13 or 16-19
 * 
 * your ticket:
 * 11,12,13
 * 
 * nearby tickets:
 * 3,9,18
 * 15,1,5
 * 5,14,9
 * Based on the nearby tickets in the above example, the first position must be row, the second position must be class, and the third position must be seat; you can conclude that in your ticket, class is 12, row is 11, and seat is 13.
 * 
 * Once you work out which field is which, look for the six fields on your ticket that start with the word departure. What do you get if you multiply those six values together?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>

using namespace std;

// Struct for ranges
struct Range {
    string name;
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
    vector<vector<int>*> tickets;
    vector<Range*> ranges;
    string s;
    // Get ranges
    while (std::getline(input, s)) {
        if (s == "") {
            break;
        } else {
            Range* r = new Range();
            stringstream ss(s);
            string name;
            ss >> name;
            r->name = name;
            while (name[name.size() - 1] != ':') {
                ss >> name;
            }
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
    // Get my ticket
    vector<int> *mine = new vector<int>();
    int token;
    int pos;
    while ((pos = s.find(',')) != string::npos) {
        token = stoi(s.substr(0, pos));
        mine->push_back(token);
        s.erase(0, pos + 1);
    }
    mine->push_back(stoi(s));
    tickets.push_back(mine);
    std::getline(input, s);
    std::getline(input, s);
    int sum = 0;
    // Get and remove invalid nearby tickets
    while (std::getline(input, s)) {
        vector<int> *nums = new vector<int>();
        int token;
        int pos;
        while ((pos = s.find(',')) != string::npos) {
            token = stoi(s.substr(0, pos));
            nums->push_back(token);
            s.erase(0, pos + 1);
        }
        nums->push_back(stoi(s));
        bool discard = false;
        // Check for invalid numbers
        for (auto n: *nums) {
            bool check = false;
            for (auto r: ranges) {
                if ((n >= r->min1 && n <= r->max1) || (n >= r->min2 && n <= r->max2)) {
                    check = true;
                    break;
                }
            }
            if (!check) {
                discard = true;
                break;
            }
        }
        if (!discard) {
            tickets.push_back(nums);
        } else {
            delete nums;
        }
    }
    // Find matching columns
    vector<Range*> posit(ranges.size(), nullptr);
    unordered_set<int> done;
    int k = 0;
    vector<int> again;
    while (done.size() != ranges.size()) {
        unordered_set<int> idx;
        int i = k;
        if (i >= ranges.size()) {
            // Time to do the redos
            i = again[0];
            again.erase(again.begin());
        }
        for (auto t : tickets) {
            int n = (*t)[i];
            if (idx.size() == 0) {
                // First time in
                int j = 0;
                for (auto r: ranges) {
                    if (done.find(j) == done.end()) {
                        if ((n >= r->min1 && n <= r->max1) || (n >= r->min2 && n <= r->max2)) {
                            idx.insert(j);
                        }
                    }
                    j++;
                }
            } else if (idx.size() > 1) {
                // Still could be multiple
                int j = 0;
                for (auto r: ranges) {
                    if (!((n >= r->min1 && n <= r->max1) || (n >= r->min2 && n <= r->max2))) {
                        idx.erase(j);
                    }
                    j++;
                }    
            } else if (idx.size() == 1){
                // Match found!!!
                posit[i] = ranges[*(idx.begin())];
                done.insert(*(idx.begin()));
                idx.clear();
                break;
            }
        }
        if (idx.size() == 1) {
            // Match found on last ticket
            posit[i] = ranges[*(idx.begin())];
            done.insert(*(idx.begin()));
        } else if (idx.size() > 1) {
            // Match not found, redo later
            again.push_back(i);
        }
        k++;
    }
    // Find product
    long long product = 1;
    for (int i = 0; i < posit.size(); i++) {
        if (posit[i]->name == "departure") {
            product *= (long long) (*mine)[i];
        }
    }
    // Print Product
    cout << "Product: " << product << endl;
    // Free Memory
    for (auto r: ranges) {
        delete r;
    }
    for (auto r: tickets) {
        delete r;
    }
    return 0;
}