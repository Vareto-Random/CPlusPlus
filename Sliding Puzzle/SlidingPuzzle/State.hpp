//
//  State.hpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/31/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#define BLANK -1234

#include <array>
#include <iostream>
#include <vector>

using namespace std;

class State {
public:
    State(State &_state);
    State(const unsigned int _size);
    State(const unsigned int _size, const vector<string> _board);
    
    ~State();
    
    pair<int, int> findBlank();
    
    int ** getBoard();
    unsigned int getCost();
    int getElement(const unsigned int row, const unsigned int col);
    unsigned int getSize();
    static State getSolution();
    
    bool setBoard(const unsigned int _size, const int **_board);
    bool setCost(unsigned int _cost);

    State operator=(State &_state);

    void toString();
    
private:
    bool allocate(unsigned int _size);
    
    int** board;
    unsigned int cost;
    unsigned int size;
};

#endif /* State_hpp */
