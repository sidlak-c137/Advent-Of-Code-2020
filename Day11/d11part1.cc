/**
 * @file d11part1.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-10
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 11: Seating System ---
 * Your plane lands with plenty of time to spare. The final leg of your journey is a ferry that goes directly to the tropical island where you can finally start your vacation. As you reach the waiting area to board the ferry, you realize you're so early, nobody else has even arrived yet!
 * 
 * By modeling the process people use to choose (or abandon) their seat in the waiting area, you're pretty sure you can predict the best place to sit. You make a quick map of the seat layout (your puzzle input).
 * 
 * The seat layout fits neatly on a grid. Each position is either floor (.), an empty seat (L), or an occupied seat (#). For example, the initial seat layout might look like this:
 * 
 * L.LL.LL.LL
 * LLLLLLL.LL
 * L.L.L..L..
 * LLLL.LL.LL
 * L.LL.LL.LL
 * L.LLLLL.LL
 * ..L.L.....
 * LLLLLLLLLL
 * L.LLLLLL.L
 * L.LLLLL.LL
 * Now, you just need to model the people who will be arriving shortly. Fortunately, people are entirely predictable and always follow a simple set of rules. All decisions are based on the number of occupied seats adjacent to a given seat (one of the eight positions immediately up, down, left, right, or diagonal from the seat). The following rules are applied to every seat simultaneously:
 * 
 * If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
 * If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
 * Otherwise, the seat's state does not change.
 * Floor (.) never changes; seats don't move, and nobody sits on the floor.
 * 
 * After one round of these rules, every seat in the example layout becomes occupied:
 * 
 * #.##.##.##
 * #######.##
 * #.#.#..#..
 * ####.##.##
 * #.##.##.##
 * #.#####.##
 * ..#.#.....
 * ##########
 * #.######.#
 * #.#####.##
 * After a second round, the seats with four or more occupied adjacent seats become empty again:
 * 
 * #.LL.L#.##
 * #LLLLLL.L#
 * L.L.L..L..
 * #LLL.LL.L#
 * #.LL.LL.LL
 * #.LLLL#.##
 * ..L.L.....
 * #LLLLLLLL#
 * #.LLLLLL.L
 * #.#LLLL.##
 * This process continues for three more rounds:
 * 
 * #.##.L#.##
 * #L###LL.L#
 * L.#.#..#..
 * #L##.##.L#
 * #.##.LL.LL
 * #.###L#.##
 * ..#.#.....
 * #L######L#
 * #.LL###L.L
 * #.#L###.##
 * #.#L.L#.##
 * #LLL#LL.L#
 * L.L.L..#..
 * #LLL.##.L#
 * #.LL.LL.LL
 * #.LL#L#.##
 * ..L.L.....
 * #L#LLLL#L#
 * #.LLLLLL.L
 * #.#L#L#.##
 * #.#L.L#.##
 * #LLL#LL.L#
 * L.#.L..#..
 * #L##.##.L#
 * #.#L.LL.LL
 * #.#L#L#.##
 * ..L.L.....
 * #L#L##L#L#
 * #.LLLLLL.L
 * #.#L#L#.##
 * At this point, something interesting happens: the chaos stabilizes and further applications of these rules cause no seats to change state! Once people stop moving around, you count 37 occupied seats.
 * 
 * Simulate your seating area by applying the seating rules repeatedly until no seats change state. How many seats end up occupied?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Returns count of adjacent filled seats
int count(const vector<string>& in, int r, int c);

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    // Put each line into vector
    vector<string> in;
    string n;
    while (input >> n){
        in.push_back(" " + n + " ");
    }
    string space((in[0]).size(), ' ');
    in.push_back(space);
    in.insert(in.begin(), space);
    // Start processing
    vector<string> out;
    int changes = 0;
    do {
        changes = 0;
        int r = 0;
        for (auto row: in) {
            if (r == 0 || r == in.size() - 1) {
                out.push_back(space);
            } else {
                string s = "";
                for (int i = 1; i < row.size() - 1; i++) {
                    int x = count(in, r, i);
                    // Process seat
                    if (row[i] == 'L') {
                        if (x == 0) {
                            // Seat changed
                            s += "#";
                            changes++;
                        } else {
                            s += "L";
                        }
                    } else if (row[i] == '#') {
                        if (x >= 4) {
                            // Seat changed
                            s += "L";
                            changes++;
                        } else {
                            s += "#";
                        }
                    } else {
                        s += ".";
                    }
                }
                out.push_back(" " + s + " ");
            }
            r++;
        }
        in.clear();
        in = out;
        out.clear();
    } while (changes != 0);
    int x = 0;
    for (auto j: in) {
        for (auto c: j) {
            if (c == '#') {
                x++;
            }
        }
    }
    cout << "Seats: " << x << endl;
    return 0;
}

int count(const vector<string>& in, int r, int c) {
    int x = 0;
    if (in[r + 1][c] == '#') {
        x++;
    }
    if (in[r + 1][c + 1] == '#') {
        x++;
    }
    if (in[r][c + 1] == '#') {
        x++;
    }
    if (in[r - 1][c] == '#') {
        x++;
    }
    if (in[r - 1][c - 1] == '#') {
        x++;
    }
    if (in[r][c - 1] == '#') {
        x++;
    }
    if (in[r + 1][c - 1] == '#') {
        x++;
    }
    if (in[r - 1][c + 1] == '#') {
        x++;
    }
    return x;
}