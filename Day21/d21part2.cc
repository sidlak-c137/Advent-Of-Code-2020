/**
 * @file d21part2.cc
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
 * 
 * --- Part Two ---
 * Now that you've isolated the inert ingredients, you should have enough information to figure out which ingredient contains which allergen.
 * 
 * In the above example:
 * 
 * mxmxvkd contains dairy.
 * sqjhc contains fish.
 * fvjkl contains soy.
 * Arrange the ingredients alphabetically by their allergen and separate them by commas to produce your canonical dangerous ingredient list. (There should not be any spaces in your canonical dangerous ingredient list.) In the above example, this would be mxmxvkd,sqjhc,fvjkl.
 * 
 * Time to stock your raft with supplies. What is your canonical dangerous ingredient list?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;

// Finds pairs of allergen and food
void possible(map<string, string>& found, unordered_map<string, unordered_set<string>*>& fmap);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    string s;
    // Process all input
    // map: allergen to food
    unordered_map<string, unordered_set<string>*> fmap;
    while (getline(input, s)) {
        stringstream ss(s);
        string t;
        unordered_set<string> f;
        while (ss >> t) {
            if (t == "(contains") {
                break;
            }
            f.insert(t);
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
                // set intersection
                copy_if(fmap[a]->begin(), fmap[a]->end(), inserter(*temp, temp->begin()), 
                        [f](string e){return f.count(e) > 0;});
                delete fmap[a];
                fmap[a] = temp;
            }
        }
    }
    map<string, string> found;
    while (!fmap.empty()) {
        possible(found, fmap);
    }
    // Print dangerous foods (remove last comma)
    for (auto x : found) {
        cout << x.second << ",";
    }
    cout << endl;

    // Clear memory (just in case)
    for (auto a: fmap) {
        delete a.second;
    }
    return 0;
}

void possible(map<string, string>& found, unordered_map<string, unordered_set<string>*>& fmap) {
    string danger = "";
    string aller = "";
    for (auto a: fmap) {
        if (a.second->size() == 1) {
            danger = *(a.second->begin());
            aller = a.first;
            break;
        }
    }
    if (danger.size() > 0) {
        found[aller] = danger;
        auto it = fmap.find(aller);
        delete it->second;
        fmap.erase(it);
        for (auto a: fmap) {
            a.second->erase(danger);
        }
    }
}
