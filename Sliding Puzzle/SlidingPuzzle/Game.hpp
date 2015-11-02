//
//  Game.hpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/31/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#define ASCENDING(a,b) (a.getCost() < b.getCost ? a : b)
#define DESCENDING(a,b) (a.getCost() < b.getCost ? b : a)

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "State.hpp"

using namespace std;

class Game {
public:
    Game(string _fileName);
    Game(int _size, State &_start);
    
    ~Game();
    
//    State getCurrent();
    State getGoal();
    State getStart();

    bool readFile(string _fileName);
    bool solve();
    
private:
    vector<int> getMoves(const int x, const int y);
    vector<State> getNeighbors(int (*heuristic)(int **),const int x, const int y);
    
    int heuristicA(State &_state);
    int heuristicB(const int **_matrix);
    int heuristicC(const int **_matrix);
    
    priority_queue<State> queue;
//    State *current;
    State *goal;
    State *start;
    vector<State> history;
    vector<string> rawInput;
    unsigned int size;
    
};

#endif /* Game_hpp */
