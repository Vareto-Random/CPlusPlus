//
//  main.cpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/30/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include <iostream>

#include "Game.hpp"

int main(int argc, const char * argv[]) {
    Game puzzle = Game(argv[1]);
    if(puzzle.solvability()) {
        puzzle.solve();
        puzzle.writeFile();
    }

//    vector <int> temp;
//    for (int row = 0; row < puzzle.size; row++) {
//        for (int col = 0; col < puzzle.size; col++) {
//            temp = puzzle.getMoves(row, col);
//        }
//    }
    
    return 0;
}
