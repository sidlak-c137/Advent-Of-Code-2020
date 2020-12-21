/**
 * @file d21part1.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-20
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 21: Allergen Assessment ---
 * You reach the train's last stop and the closest you can get to your vacation island without getting wet. There aren't even any boats here, but nothing can stop you now: you build a raft. You just need a few days' worth of food for your journey.
 * 
 * You don't speak the local language, so you can't read any ingredients lists. However, sometimes, allergens are listed in a language you do understand. You should be able to use this information to determine which ingredient contains which allergen and work out which foods are safe to take with you on your trip.
 * 
 * You start by compiling a list of foods (your puzzle input), one food per line. Each line includes that food's ingredients list followed by some or all of the allergens the food contains.
 * 
 * Each allergen is found in exactly one ingredient. Each ingredient contains zero or one allergen. Allergens aren't always marked; when they're listed (as in (contains nuts, shellfish) after an ingredients list), the ingredient that contains each listed allergen will be somewhere in the corresponding ingredients list. However, even if an allergen isn't listed, the ingredient that contains that allergen could still be present: maybe they forgot to label it, or maybe it was labeled in a language you don't know.
 * 
 * For example, consider the following list of foods:
 * 
 * mxmxvkd kfcds sqjhc nhms (contains dairy, fish)
 * trh fvjkl sbzzf mxmxvkd (contains dairy)
 * sqjhc fvjkl (contains soy)
 * sqjhc mxmxvkd sbzzf (contains fish)
 * The first food in the list has four ingredients (written in a language you don't understand): mxmxvkd, kfcds, sqjhc, and nhms. While the food might contain other allergens, a few allergens the food definitely contains are listed afterward: dairy and fish.
 * 
 * The first step is to determine which ingredients can't possibly contain any of the allergens in any food in your list. In the above example, none of the ingredients kfcds, nhms, sbzzf, or trh can contain an allergen. Counting the number of times any of these ingredients appear in any ingredients list produces 5: they all appear once each except sbzzf, which appears twice.
 * 
 * Determine which ingredients cannot possibly contain any of the allergens in your list. How many times do any of those ingredients appear?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    string s;
    // map: allergen to food
    unordered_map<string, unordered_set<string>*> fmap;
    // all foods
    unordered_set<string> foods;
    // frequency of each food
    unordered_map<string, int> counts;
    // Process all lines
    while (getline(input, s)) {
        stringstream ss(s);
        string t;
        unordered_set<string> f;
        while (ss >> t) {
            if (t == "(contains") {
                break;
            }
            f.insert(t);
            foods.insert(t);
            counts[t]++;
        }
        unordered_set<string> al;
        while (ss >> t) {
            al.insert(t.substr(0, t.size() - 1));
        }
        for (auto a : al) {
            if (fmap.find(a) == fmap.end()) {
                fmap[a] = new unordered_set<string>(f);
            } else {
                auto temp = new unordered_set<string>();
                // Set intersection
                copy_if(fmap[a]->begin(), fmap[a]->end(), inserter(*temp, temp->begin()), 
                        [f](string e){return f.count(e) > 0;});
                delete fmap[a];
                fmap[a] = temp;
            }
        }
    }

    // Count not possible foods
    unordered_set<string> non(foods);
    for (auto a: fmap) {
        for (auto x: *(a.second)) {
            non.erase(x);
        }
    }
    int count = 0;
    for (auto a : non) {
        count += counts[a];
    }
    // Print count
    cout << "Count: " << count << endl;

    // Clear memory
    for (auto a: fmap) {
        delete a.second;
    }
    return 0;
}
