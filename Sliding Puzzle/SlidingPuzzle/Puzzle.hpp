//
//  Puzzle.hpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/30/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Puzzle_hpp
#define Puzzle_hpp

#define BLANK   -12345

#define UP      1
#define RIGHT   2
#define DOWN    3
#define LEFT    4

#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "State.hpp"

using namespace std;

class Puzzle {
public:
    Puzzle(const string _fileName);
    Puzzle(const int _size);
    Puzzle(const int _size, const int **_matrix);
    
    ~Puzzle();

    bool populate(const vector<string> &_rawFile);
    bool readFile(const string _fileName);
    bool solve();
    
//private:
    bool allocate(const int _size);
    bool allocate(const int _size, const int **_matrix);
    bool copy(const int _size, const int **_matrix);
    bool initialize();
    
    vector<int> getMoves(const int row, const int column);
    vector< pair<int **, int> > getNeighbors(int (*heuristic)(int **),const int x, const int y);
    bool swap(const int x, const int y, const int move);
    
    int heuristicA(const int **_matrix);
    int heuristicB(const int **_matrix);
    int heuristicC(const int **_matrix);
    
    bool ready;
    int size;
    int **matrix;
    int **goal;
    priority_queue<pair<int, int>, vector<int>, greater<int> > neighbors;
    vector<string> rawMatrix;
};

#endif /* Puzzle_hpp */
