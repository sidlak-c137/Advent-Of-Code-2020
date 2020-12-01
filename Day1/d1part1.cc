/**
 * @file d1part1.cpp
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-11-30
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 1: Report Repair ---
 * After saving Christmas five years in a row, you've decided to take a vacation at a nice resort on a tropical island. Surely, Christmas will go on without you.
 * 
 * The tropical island has its own currency and is entirely cash-only. The gold coins used there have a little picture of a starfish; the locals just call them stars. None of the currency exchanges seem to have heard of them, but somehow, you'll need to find fifty of these coins by the time you arrive so you can pay the deposit on your room.
 * 
 * To save your vacation, you need to get all fifty stars by December 25th.
 * 
 * Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!
 * 
 * Before you leave, the Elves in accounting just need you to fix your expense report (your puzzle input); apparently, something isn't quite adding up.
 * 
 * Specifically, they need you to find the two entries that sum to 2020 and then multiply those two numbers together.
 * 
 * For example, suppose your expense report contained the following:
 * 
 * 1721
 * 979
 * 366
 * 299
 * 675
 * 1456
 * In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying them together produces 1721 * 299 = 514579, so the correct answer is 514579.
 * 
 * Of course, your expense report is much larger. Find the two entries that sum to 2020; what do you get if you multiply them together?
 * 
 */

#include <iostream>
#include <unordered_set>
#include <fstream>

using namespace std;

// Finds the product of the two numbers in the set that sum
// to 2020 and prints that product to out.
// Input: unordered_set of ints
void sumTwo(const unordered_multiset<int> &nums);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    // Insert all numbers in that file to a hash set
    unordered_multiset<int> nums;
    int x;
    while(input >> x) {
        nums.insert(x);
    }
    // Print product of two numbers summing to 2020
    sumTwo(nums);
    return 0;
}

void sumTwo(const unordered_multiset<int> &nums) {
    unordered_multiset<int>::iterator it, it_find, it_end;
    it_end = nums.cend();
    // Iterate through set
    for (it = nums.cbegin(); it != it_end; it++) {
        int num = *it;
        // Find if 2020 - num is in the set
        it_find = nums.find(2020 - num);
        if (it_find != it_end && it != it_find) {
            // Print product of num and (2020 - num)
            cout << "Product of Numbers: " << num * (2020 - num) << endl;
            return;
        }
    }
}