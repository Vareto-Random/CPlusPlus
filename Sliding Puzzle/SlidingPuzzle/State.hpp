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
    State();
    State(State &_state);
    State(const int _size);
    State(const int _size, const vector<string> _board);
    
    ~State();
    
    int calcHash();
    
    int ** getBoard();
    int getCost();
    int getElement(int row, int col);
    int getLevel();
    int getSize();

    State * getParent();
    vector<State *> getNeighbors();
    
    bool setBoard(const int _size, const int **_board);
    bool setCost(int _cost);
    bool setLevel(int _level);
    
    bool setParent(State *_parent);

    bool operator()(State *_stateA, State *_stateB);
    bool operator<(State *_state);
    bool operator>(State *_state);
    bool operator==(State *_state);
    State& operator=(State *_state);

    void toString();
    
private:
    bool allocate(int _size);
    bool copy(int **_board);
    bool deallocate();
    bool initialize();
    
    pair<int, int> getBlank();
    vector<int> getMoves(const int x, const int y);
    
    int** board;
    State *parent;
    unsigned int cost;
    unsigned int hash;
    unsigned int level;
    unsigned int size;
};

class Queue {
public:
    bool operator()(State *_stateA, State *_stateB);
};

class Set {
public:
    bool operator()(State *_stateA, State *_stateB);
};

#endif /* State_hpp */
