/**
 * @file d13part1.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-12
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 13: Shuttle Search ---
 * Your ferry can make it safely to a nearby port, but it won't get much further. When you call to book another ship, you discover that no ships embark from that port to your vacation island. You'll need to get from the port to the nearest airport.
 * 
 * Fortunately, a shuttle bus service is available to bring you from the sea port to the airport! Each bus has an ID number that also indicates how often the bus leaves for the airport.
 * 
 * Bus schedules are defined based on a timestamp that measures the number of minutes since some fixed reference point in the past. At timestamp 0, every bus simultaneously departed from the sea port. After that, each bus travels to the airport, then various other locations, and finally returns to the sea port to repeat its journey forever.
 * 
 * The time this loop takes a particular bus is also its ID number: the bus with ID 5 departs from the sea port at timestamps 0, 5, 10, 15, and so on. The bus with ID 11 departs at 0, 11, 22, 33, and so on. If you are there when the bus departs, you can ride that bus to the airport!
 * 
 * Your notes (your puzzle input) consist of two lines. The first line is your estimate of the earliest timestamp you could depart on a bus. The second line lists the bus IDs that are in service according to the shuttle company; entries that show x must be out of service, so you decide to ignore them.
 * 
 * To save time once you arrive, your goal is to figure out the earliest bus you can take to the airport. (There will be exactly one such bus.)
 * 
 * For example, suppose you have the following notes:
 * 
 * 939
 * 7,13,x,x,59,x,31,19
 * Here, the earliest timestamp you could depart is 939, and the bus IDs in service are 7, 13, 59, 31, and 19. Near timestamp 939, these bus IDs depart at the times marked D:
 * 
 * time   bus 7   bus 13  bus 59  bus 31  bus 19
 * 929      .       .       .       .       .
 * 930      .       .       .       D       .
 * 931      D       .       .       .       D
 * 932      .       .       .       .       .
 * 933      .       .       .       .       .
 * 934      .       .       .       .       .
 * 935      .       .       .       .       .
 * 936      .       D       .       .       .
 * 937      .       .       .       .       .
 * 938      D       .       .       .       .
 * 939      .       .       .       .       .
 * 940      .       .       .       .       .
 * 941      .       .       .       .       .
 * 942      .       .       .       .       .
 * 943      .       .       .       .       .
 * 944      .       .       D       .       .
 * 945      D       .       .       .       .
 * 946      .       .       .       .       .
 * 947      .       .       .       .       .
 * 948      .       .       .       .       .
 * 949      .       D       .       .       .
 * The earliest bus you could take is bus ID 59. It doesn't depart until timestamp 944, so you would need to wait 944 - 939 = 5 minutes before it departs. Multiplying the bus ID by the number of minutes you'd need to wait gives 295.
 * 
 * What is the ID of the earliest bus you can take to the airport multiplied by the number of minutes you'll need to wait for that bus?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    int n;
    input >> n;
    string str;
    input >> str;
    stringstream ss(str);
    char c;
    string s = "";
    // Process input
    vector<int> in;
    while (ss >> c) {
        if (c == ',') {
            if (s == "x") {
                in.push_back(-1);
            } else {
                in.push_back(stoi(s));
            }
            s = "";
        } else {
            s += c;
        }
    }
    if (s == "x") {
        in.push_back(-1);
    } else {
        in.push_back(stoi(s));
    }
    int n2 = n;
    bool check = true;
    int id = -1;
    // Find num
    while (check) {
        for (auto x: in) {
           if (x != -1 && n2 % x == 0 && check) {
               check = false;
               id = x;
           } 
        }
        n2++;
    }
    // Note: n2 overcounts by 1
    cout << (n2 - n - 1) * id << endl;
    return 0;
}