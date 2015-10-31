//
//  Puzzle.hpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/30/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Puzzle_hpp
#define Puzzle_hpp

#define BLANK -12345

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

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
    
private:
    bool allocate(const int _size);
    bool allocate(const int _size, const int **_matrix);
    bool copy(const int _size, const int **_matrix);
    bool initialize();
    int getNeighbors();
    
    bool ready;
    int size;
    int **matrix;
    int **goal;
    vector<string> rawMatrix;
};

#endif /* Puzzle_hpp */
