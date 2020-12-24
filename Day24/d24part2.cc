/**
 * @file d24part2.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-23
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 24: Lobby Layout ---
 * Your raft makes it to the tropical island; it turns out that the small crab was an excellent navigator. You make your way to the resort.
 * 
 * As you enter the lobby, you discover a small problem: the floor is being renovated. You can't even reach the check-in desk until they've finished installing the new tile floor.
 * 
 * The tiles are all hexagonal; they need to be arranged in a hex grid with a very specific color pattern. Not in the mood to wait, you offer to help figure out the pattern.
 * 
 * The tiles are all white on one side and black on the other. They start with the white side facing up. The lobby is large enough to fit whatever pattern might need to appear there.
 * 
 * A member of the renovation crew gives you a list of the tiles that need to be flipped over (your puzzle input). Each line in the list identifies a single tile that needs to be flipped by giving a series of steps starting from a reference tile in the very center of the room. (Every line starts from the same reference tile.)
 * 
 * Because the tiles are hexagonal, every tile has six neighbors: east, southeast, southwest, west, northwest, and northeast. These directions are given in your list, respectively, as e, se, sw, w, nw, and ne. A tile is identified by a series of these directions with no delimiters; for example, esenee identifies the tile you land on if you start at the reference tile and then move one tile east, one tile southeast, one tile northeast, and one tile east.
 * 
 * Each time a tile is identified, it flips from white to black or from black to white. Tiles might be flipped more than once. For example, a line like esew flips a tile immediately adjacent to the reference tile, and a line like nwwswee flips the reference tile itself.
 * 
 * Here is a larger example:
 * 
 * sesenwnenenewseeswwswswwnenewsewsw
 * neeenesenwnwwswnenewnwwsewnenwseswesw
 * seswneswswsenwwnwse
 * nwnwneseeswswnenewneswwnewseswneseene
 * swweswneswnenwsewnwneneseenw
 * eesenwseswswnenwswnwnwsewwnwsene
 * sewnenenenesenwsewnenwwwse
 * wenwwweseeeweswwwnwwe
 * wsweesenenewnwwnwsenewsenwwsesesenwne
 * neeswseenwwswnwswswnw
 * nenwswwsewswnenenewsenwsenwnesesenew
 * enewnwewneswsewnwswenweswnenwsenwsw
 * sweneswneswneneenwnewenewwneswswnese
 * swwesenesewenwneswnwwneseswwne
 * enesenwswwswneneswsenwnewswseenwsese
 * wnwnesenesenenwwnenwsewesewsesesew
 * nenewswnwewswnenesenwnesewesw
 * eneswnwswnwsenenwnwnwwseeswneewsenese
 * neswnwewnwnwseenwseesewsenwsweewe
 * wseweeenwnesenwwwswnew
 * In the above example, 10 tiles are flipped once (to black), and 5 more are flipped twice (to black, then back to white). After all of these instructions have been followed, a total of 10 tiles are black.
 * 
 * Go through the renovation crew's list and determine which tiles they need to flip. After all of the instructions have been followed, how many tiles are left with the black side up?
 * 
 * --- Part Two ---
 * The tile floor in the lobby is meant to be a living art exhibit. Every day, the tiles are all flipped according to the following rules:
 * 
 * Any black tile with zero or more than 2 black tiles immediately adjacent to it is flipped to white.
 * Any white tile with exactly 2 black tiles immediately adjacent to it is flipped to black.
 * Here, tiles immediately adjacent means the six tiles directly touching the tile in question.
 * 
 * The rules are applied simultaneously to every tile; put another way, it is first determined which tiles need to be flipped, then they are all flipped at the same time.
 * 
 * In the above example, the number of black tiles that are facing up after the given number of days has passed is as follows:
 * 
 * Day 1: 15
 * Day 2: 12
 * Day 3: 25
 * Day 4: 14
 * Day 5: 23
 * Day 6: 28
 * Day 7: 41
 * Day 8: 37
 * Day 9: 49
 * Day 10: 37
 * 
 * Day 20: 132
 * Day 30: 259
 * Day 40: 406
 * Day 50: 566
 * Day 60: 788
 * Day 70: 1106
 * Day 80: 1373
 * Day 90: 1844
 * Day 100: 2208
 * After executing this process a total of 100 times, there would be 2208 black tiles facing up.
 * 
 * How many tiles will be black after 100 days?
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

typedef long long int ll;

// Tile locations
struct coord {
    int x; 
    int y; 

    coord(int a, int b) {
        x = a;
        y = b;
    }

    string toString() {
        return to_string(x) + " " + to_string(y);
    }
};

vector<vector<int>> getNeighbors(int x, int y) {
    return vector<vector<int>>({{x+1,y-1},{x,y-1},{x+1,y},{x-1,y},{x,y+1},{x-1,y+1}});
}

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    string s;
    // Process intial floor layout
    map<string, int> floor; 
    while (getline(input, s)) {
        stringstream ss(s);
        char c;
        coord tile(0, 0);
        while (ss >> c) {
            string dir(1, c);
            if (c == 'n' || c == 's') {
                ss >> c;
                dir += c;
            }
            if (dir == "e") {
                tile.x++;
            } else if (dir == "w") {
                tile.x--;
            } else if (dir == "se") {
                tile.x++;
                tile.y--;
            } else if (dir == "nw") {
                tile.x--;
                tile.y++;
            } else if (dir == "sw") {
                tile.y--;
            } else {
                tile.y++;
            }
        }
        string str = tile.toString();
        floor[str]++;
    }
    // Create set of black tiles
    set<string> black;
    for (auto tile: floor) {
        if (tile.second % 2 == 1) {
            black.insert(tile.first);
        }
    }

    // Simulate floors
    for (int i = 0; i < 100; i++) {
        map<string, int> temp;
        // Count neighbors
        for (auto j: black) {
            stringstream ss(j);
            int x, y;
            ss >> x >> y; 
            for (auto k: getNeighbors(x, y)) {
                coord t(k[0], k[1]);
                temp[t.toString()]++;
            }
        }
        // Add newly created black tiles
        set<string> newBlack;
        for (auto x: temp) {
            if (black.find(x.first) != black.end()) {
                if (x.second > 0 && x.second <= 2) {
                    newBlack.insert(x.first);
                }
            } else {
                if (x.second == 2) {
                    newBlack.insert(x.first);
                }
            }
        }
        black = newBlack;
    }
    // Print number of black tiles
    cout << "Black tiles: " << black.size() << endl;
    return 0;
}