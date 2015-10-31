//
//  State.hpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/31/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#define SIZE 3

#include <array>
#include <stdio.h>

using namespace std;

class State {
public:
    State();
    State(unsigned int _size);
    State(unsigned int _size, int **_board);
    
    ~State();
    
    int ** getBoard();
    unsigned int getCost();
    inline int getElement(unsigned int row, unsigned int col);
    unsigned int getSize();

    bool setBoard(unsigned int _size, int **_board);
    bool setCost(unsigned int _cost);
    
    State operator=(State &_state);
    
private:
    bool allocate(unsigned int _size);
    
    int** board;
    unsigned int cost;
    unsigned int size;
};

#endif /* State_hpp */
