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

#define UP      1
#define RIGHT   2
#define DOWN    3
#define LEFT    4

#define NORTH   "acima"
#define EAST    "direita"
#define SOUTH   "abaixo"
#define WEST    "esquerda"

#include <array>
#include <iostream>
#include <vector>

using namespace std;

class State {
public:
    State(State &_state);
    State(const int _size);
    State(const int _size, const vector<string> _board);
    
    ~State();
    
    pair<int, int> findBlank();
    
    int ** getBoard();
    int getCost();
    inline int getElement(const int row, const int col);
    int getSize();
    static State getSolution();
    
    bool setBoard(const int _size, const int **_board);
    bool setCost(int _cost);

    State operator=(State &_state);
    State swap(const int move);

    void toString();
    
private:
    bool allocate(int _size);
    
    int** board;
    unsigned int cost;
    unsigned int size;
};

#endif /* State_hpp */
