//
//  Puzzle.hpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/30/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Puzzle_hpp
#define Puzzle_hpp

#include <iostream>

using namespace std;

class Puzzle {
public:
    Puzzle();
    Puzzle(int _size);
    Puzzle(int _size, int **_matrix);
    ~Puzzle();
    
    bool readFile(string _fileName);
    bool solve();
    
private:
    bool allocate(int _size);
    bool allocate(int _size, int **_matrix);
    void copyMatrix(int _size, int **_matrix);
    
    bool ready;
    int size;
    int **matrix;
};

#endif /* Puzzle_hpp */
