/**
 * @file d20part2.cc
 * @author Sidharth Lakshmanan
 * @brief 
 * @version 0.1
 * @date 2020-12-19
 * 
 * @copyright Copyright (c) 2020
 * 
 * --- Day 20: Jurassic Jigsaw ---
 * The high-speed train leaves the forest and quickly carries you south. You can even see a desert in the distance! Since you have some spare time, you might as well see if there was anything interesting in the image the Mythical Information Bureau satellite captured.
 * 
 * After decoding the satellite messages, you discover that the data actually contains many small images created by the satellite's camera array. The camera array consists of many cameras; rather than produce a single square image, they produce many smaller square image tiles that need to be reassembled back into a single image.
 * 
 * Each camera in the camera array returns a single monochrome image tile with a random unique ID number. The tiles (your puzzle input) arrived in a random order.
 * 
 * Worse yet, the camera array appears to be malfunctioning: each image tile has been rotated and flipped to a random orientation. Your first task is to reassemble the original image by orienting the tiles so they fit together.
 * 
 * To show how the tiles should be reassembled, each tile's image data includes a border that should line up exactly with its adjacent tiles. All tiles have this border, and the border lines up exactly when the tiles are both oriented correctly. Tiles at the edge of the image also have this border, but the outermost edges won't line up with any other tiles.
 * 
 * For example, suppose you have the following nine tiles:
 * 
 * Tile 2311:
 * ..##.#..#.
 * ##..#.....
 * #...##..#.
 * ####.#...#
 * ##.##.###.
 * ##...#.###
 * .#.#.#..##
 * ..#....#..
 * ###...#.#.
 * ..###..###
 * 
 * Tile 1951:
 * #.##...##.
 * #.####...#
 * .....#..##
 * #...######
 * .##.#....#
 * .###.#####
 * ###.##.##.
 * .###....#.
 * ..#.#..#.#
 * #...##.#..
 * 
 * Tile 1171:
 * ####...##.
 * #..##.#..#
 * ##.#..#.#.
 * .###.####.
 * ..###.####
 * .##....##.
 * .#...####.
 * #.##.####.
 * ####..#...
 * .....##...
 * 
 * Tile 1427:
 * ###.##.#..
 * .#..#.##..
 * .#.##.#..#
 * #.#.#.##.#
 * ....#...##
 * ...##..##.
 * ...#.#####
 * .#.####.#.
 * ..#..###.#
 * ..##.#..#.
 * 
 * Tile 1489:
 * ##.#.#....
 * ..##...#..
 * .##..##...
 * ..#...#...
 * #####...#.
 * #..#.#.#.#
 * ...#.#.#..
 * ##.#...##.
 * ..##.##.##
 * ###.##.#..
 * 
 * Tile 2473:
 * #....####.
 * #..#.##...
 * #.##..#...
 * ######.#.#
 * .#...#.#.#
 * .#########
 * .###.#..#.
 * ########.#
 * ##...##.#.
 * ..###.#.#.
 * 
 * Tile 2971:
 * ..#.#....#
 * #...###...
 * #.#.###...
 * ##.##..#..
 * .#####..##
 * .#..####.#
 * #..#.#..#.
 * ..####.###
 * ..#.#.###.
 * ...#.#.#.#
 * 
 * Tile 2729:
 * ...#.#.#.#
 * ####.#....
 * ..#.#.....
 * ....#..#.#
 * .##..##.#.
 * .#.####...
 * ####.#.#..
 * ##.####...
 * ##..#.##..
 * #.##...##.
 * 
 * Tile 3079:
 * #.#.#####.
 * .#..######
 * ..#.......
 * ######....
 * ####.#..#.
 * .#...#.##.
 * #.#####.##
 * ..#.###...
 * ..#.......
 * ..#.###...
 * By rotating, flipping, and rearranging them, you can find a square arrangement that causes all adjacent borders to line up:
 * 
 * #...##.#.. ..###..### #.#.#####.
 * ..#.#..#.# ###...#.#. .#..######
 * .###....#. ..#....#.. ..#.......
 * ###.##.##. .#.#.#..## ######....
 * .###.##### ##...#.### ####.#..#.
 * .##.#....# ##.##.###. .#...#.##.
 * #...###### ####.#...# #.#####.##
 * .....#..## #...##..#. ..#.###...
 * #.####...# ##..#..... ..#.......
 * #.##...##. ..##.#..#. ..#.###...
 * 
 * #.##...##. ..##.#..#. ..#.###...
 * ##..#.##.. ..#..###.# ##.##....#
 * ##.####... .#.####.#. ..#.###..#
 * ####.#.#.. ...#.##### ###.#..###
 * .#.####... ...##..##. .######.##
 * .##..##.#. ....#...## #.#.#.#...
 * ....#..#.# #.#.#.##.# #.###.###.
 * ..#.#..... .#.##.#..# #.###.##..
 * ####.#.... .#..#.##.. .######...
 * ...#.#.#.# ###.##.#.. .##...####
 * 
 * ...#.#.#.# ###.##.#.. .##...####
 * ..#.#.###. ..##.##.## #..#.##..#
 * ..####.### ##.#...##. .#.#..#.##
 * #..#.#..#. ...#.#.#.. .####.###.
 * .#..####.# #..#.#.#.# ####.###..
 * .#####..## #####...#. .##....##.
 * ##.##..#.. ..#...#... .####...#.
 * #.#.###... .##..##... .####.##.#
 * #...###... ..##...#.. ...#..####
 * ..#.#....# ##.#.#.... ...##.....
 * For reference, the IDs of the above tiles are:
 * 
 * 1951    2311    3079
 * 2729    1427    2473
 * 2971    1489    1171
 * To check that you've assembled the image correctly, multiply the IDs of the four corner tiles together. If you do this with the assembled tiles from the example above, you get 1951 * 3079 * 2971 * 1171 = 20899048083289.
 * 
 * Assemble the tiles into an image. What do you get if you multiply together the IDs of the four corner tiles?
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

typedef unsigned long long ull;

// Class to store tiles
class Img {
    public:
    ull id;
    vector<string> base;
    vector<vector<string>> variants;

    Img::Img(int id, vector<string> base) {
        this->id = id;
        this->base = base;
        this->variants.push_back(base);
        for (int i = 1; i < 4; i++) {
            this->variants.push_back(Img::rotate(variants[i - 1]));
        }
        for (int i = 0; i < 4; i++) {
            this->variants.push_back(Img::flip(variants[i]));
        }
    }

    vector<string> Img::rotate(vector<string>& vec) {
        vector<string> temp = vec;
        for (int y = 0; y < vec.size(); y++) {
            for (int x = 0; x < vec.size(); x++) {
                temp[y][x] = vec[vec.size() - 1 - x][y];
            }
        }
        return temp;
    }

    vector<string> Img::flip(vector<string>& vec) {
        vector<string> temp = vec;
        for (int y = 0; y < vec.size(); y++) {
            for (int x = 0; x < vec.size(); x++) {
                temp[y][x] = vec[y][vec.size() - 1 - x];
            }
        }
        return temp;
    }
};

// Checks if img fits
bool fits(int x, int y, vector<string> var, vector<vector<vector<string>>>& fin);

// Solves for final image
void solve(int i, ull prod, vector<vector<vector<string>>>& fin, vector<int>& done, vector<Img*>& tiles);

// Product
ull product = 1;

int main() {
    // Read in file
    ifstream input;
    input.open("input.txt");
    if (!input) {
        cerr << "Could not open file!" << endl;
        return 1;
    }
    string s;
    ull id;
    char c;
    // Process tiles
    vector<Img*> tiles;
    while (input >> s >> id >> c) {
        vector<string> v;
        getline(input, s);
        while (getline(input, s)) {
            if (s.size() == 0) {
                break;
            }
            v.push_back(s);
        }
        tiles.push_back(new Img(id, v));
    }
    vector<vector<vector<string>>> fin(sqrt(tiles.size()), vector<vector<string>>(sqrt(tiles.size()), vector<string>(0)));
    vector<int> done(tiles.size(), -1);
    // Find product of 4 corners
    solve(0, product, fin, done, tiles);
    cout << "Product: " << product << endl;
    // Free memory
    for (auto x: tiles) {
        delete x;
    }
    return 0;
}

bool fits(int x, int y, vector<string> var, vector<vector<vector<string>>>& fin) {
    if (x > 0) {
        vector<string> left = fin[y][x - 1];
        for (int i = 0; i < var.size(); i++) {
            if (left[i][var.size() - 1] != var[i][0]) {
                return false;
            }
        }
    }
    if (y > 0) {
        vector<string> top = fin[y - 1][x];
        for (int i = 0; i < var.size(); i++) {
            if (top[var.size() - 1][i] != var[0][i]) {
                return false;
            }
        }
    }
    return true;
}

void solve(int i, ull prod, vector<vector<vector<string>>>& fin, vector<int>& done, vector<Img*>& tiles) {
    if (i == done.size()) {
        product = prod;
        return;
    }
    int y = i / sqrt(done.size());
    int x = i % (int) sqrt(done.size());
    for (int j = 0; j < done.size(); j++) {
        if (done[j] != -1) {
            continue;
        }
        done[j] = i;
        // Corners
        ull temp = prod;
        Img* curr = tiles[j];
        if (i == 0 || i == sqrt(done.size()) - 1 || i == done.size() - 1 
                    || i == done.size() - sqrt(done.size())) {
            temp *= tiles[j]->id;
        }
        for (int v = 0; v < 8; v++) {
            // Find tile that fits
            if (fits(x, y, curr->variants.at(v), fin)) {
                fin[y][x] = curr->variants.at(v);
                solve(i + 1, temp, fin, done, tiles);
            }
        }
        done[j] = -1;
    }
}