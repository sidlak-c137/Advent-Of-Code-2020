/**
 * @file d17part1.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-16
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 17: Conway Cubes ---
 * As your flight slowly drifts through the sky, the Elves at the Mythical Information Bureau at the North Pole contact you. They'd like some help debugging a malfunctioning experimental energy source aboard one of their super-secret imaging satellites.
 * 
 * The experimental energy source is based on cutting-edge technology: a set of Conway Cubes contained in a pocket dimension! When you hear it's having problems, you can't help but agree to take a look.
 * 
 * The pocket dimension contains an infinite 3-dimensional grid. At every integer 3-dimensional coordinate (x,y,z), there exists a single cube which is either active or inactive.
 * 
 * In the initial state of the pocket dimension, almost all cubes start inactive. The only exception to this is a small flat region of cubes (your puzzle input); the cubes in this region start in the specified active (#) or inactive (.) state.
 * 
 * The energy source then proceeds to boot up by executing six cycles.
 * 
 * Each cube only ever considers its neighbors: any of the 26 other cubes where any of their coordinates differ by at most 1. For example, given the cube at x=1,y=2,z=3, its neighbors include the cube at x=2,y=2,z=2, the cube at x=0,y=2,z=3, and so on.
 * 
 * During a cycle, all cubes simultaneously change their state according to the following rules:
 * 
 * If a cube is active and exactly 2 or 3 of its neighbors are also active, the cube remains active. Otherwise, the cube becomes inactive.
 * If a cube is inactive but exactly 3 of its neighbors are active, the cube becomes active. Otherwise, the cube remains inactive.
 * The engineers responsible for this experimental energy source would like you to simulate the pocket dimension and determine what the configuration of cubes should be at the end of the six-cycle boot process.
 * 
 * For example, consider the following initial state:
 * 
 * .#.
 * ..#
 * ###
 * Even though the pocket dimension is 3-dimensional, this initial state represents a small 2-dimensional slice of it. (In particular, this initial state defines a 3x3x1 region of the 3-dimensional space.)
 * 
 * Simulating a few cycles from this initial state produces the following configurations, where the result of each cycle is shown layer-by-layer at each given z coordinate (and the frame of view follows the active cells in each cycle):
 * 
 * Before any cycles:
 * 
 * z=0
 * .#.
 * ..#
 * ###
 * 
 * 
 * After 1 cycle:
 * 
 * z=-1
 * #..
 * ..#
 * .#.
 * 
 * z=0
 * #.#
 * .##
 * .#.
 * 
 * z=1
 * #..
 * ..#
 * .#.
 * 
 * 
 * After 2 cycles:
 * 
 * z=-2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 * 
 * z=-1
 * ..#..
 * .#..#
 * ....#
 * .#...
 * .....
 * 
 * z=0
 * ##...
 * ##...
 * #....
 * ....#
 * .###.
 * 
 * z=1
 * ..#..
 * .#..#
 * ....#
 * .#...
 * .....
 * 
 * z=2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 * 
 * 
 * After 3 cycles:
 * 
 * z=-2
 * .......
 * .......
 * ..##...
 * ..###..
 * .......
 * .......
 * .......
 * 
 * z=-1
 * ..#....
 * ...#...
 * #......
 * .....##
 * .#...#.
 * ..#.#..
 * ...#...
 * 
 * z=0
 * ...#...
 * .......
 * #......
 * .......
 * .....##
 * .##.#..
 * ...#...
 * 
 * z=1
 * ..#....
 * ...#...
 * #......
 * .....##
 * .#...#.
 * ..#.#..
 * ...#...
 * 
 * z=2
 * .......
 * .......
 * ..##...
 * ..###..
 * .......
 * .......
 * .......
 * After the full six-cycle boot process completes, 112 cubes are left in the active state.
 * 
 * Starting with your given initial configuration, simulate six cycles. How many cubes are left in the active state after the sixth cycle?
 * 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Simulates cycles
int cycle(const unordered_set<vector<int>*>& v, int n, unordered_map<string, char>& pos);

// Gets count of neighbors
int getNeighbors(const unordered_set<vector<int>*>& v, string c, const unordered_map<string, char>& pos);

// Get all possible permutations of coords (except 0,0,0,0)
void getD(int dim, unordered_set<vector<int>*>& v, vector<int>& curr);

// toString for coords
string getCoord(int x, int y, int z);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    // Process input
    string s;
    unordered_map<string, char> pos;
    int x = 0;
    int y = 0;
    int z = 0;
    while (std::getline(input, s)) {
        stringstream ss(s);
        char c;
        while (ss >> c) {
            pos[getCoord(x, y, z)] = c;
            x++;
        }
        x = 0;
        y++;
    }
    // Get all neighboring coords
    unordered_set<vector<int>*> v;
    vector<int> temp;
    getD(3, v, temp);
    // Print active
    cout << "Active: " << cycle(v, 6, pos) << endl;
    for (auto c: v) {
        delete c;
    }
    return 0;
}

int getNeighbors(const unordered_set<vector<int>*>& v, string c, const unordered_map<string, char>& pos) {
    stringstream ss(c);
    int x;
    ss >> x;
    int y;
    ss >> y;
    int z;
    ss >> z;
    // Count neighbors
    int count = 0;
    for (auto vec: v) {
        auto it = pos.find(getCoord(x + (*vec)[0], y + (*vec)[1], z + (*vec)[2]));
        if (it != pos.end()) {
            if (it->second == '#') {
                count++;
            }
        }
    }
    return count;
}

int cycle(const unordered_set<vector<int>*>& v, int n, unordered_map<string, char>& pos) {
    for (int i = 0; i < n; i++) {
        unordered_map<string, char> temp;
        for (auto p: pos) {
            stringstream ss(p.first);
            int x;
            ss >> x;
            int y;
            ss >> y;
            int z;
            ss >> z;
            // Add not-in-frame points
            for (auto vec: v) {
                string coord = getCoord(x + (*vec)[0], y + (*vec)[1], z + (*vec)[2]);
                auto it = pos.find(coord);
                if (it == pos.end()) {
                    int m = getNeighbors(v, coord, pos);
                    if (m == 3) {
                        temp[coord] = '#';
                    } else {
                        temp[coord] = '.';
                    }
                }
            }
            // Modify current point
            int num = getNeighbors(v, p.first, pos);
            if (p.second == '.') {
                if (num == 3) {
                    temp[p.first] = '#';
                } else {
                    temp[p.first] = '.';
                }
            } else {
                if (num == 3 || num == 2) {
                    temp[p.first] = '#';
                } else {
                    temp[p.first] = '.';
                }
            }
        }
        pos = temp;
    }
    // Count
    int count = 0;
    for (auto p: pos) {
        if (p.second == '#') {
            count++;
        }
    }
    return count;
}

void getD(int dim, unordered_set<vector<int>*>& v, vector<int>& curr) {
    // Base case
    if (dim == 0) {
        if (count(curr.begin(), curr.end(), 0) != curr.size()) {
            vector<int>* temp = new vector<int>();
            for (auto c: curr) {
                temp->push_back(c);
            }
            v.insert(temp);
        }
    } else {
        // Add possible coords
        for (int i = -1; i < 2; i++) {
            curr.push_back(i);
            getD(dim - 1, v, curr);
            curr.pop_back();
        }
    }
    
}

string getCoord(int x, int y, int z) {
    return to_string(x) + " " + to_string(y) + " " + to_string(z);
}