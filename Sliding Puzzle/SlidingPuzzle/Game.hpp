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

#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

#include "State.hpp"

using namespace std;

class Game {
public:
    Game(string _fileName);
    Game(int _size, State &_start);
    
    ~Game();
    
    State getGoal();
    State getStart();

    bool readFile(string _fileName);
    bool solvability();
    bool solve();
    bool writeFile(bool _print = false);
    
private:
    static int heuristicA(State *_state);
    static int heuristicB(State *_state);
    static int heuristicC(State *_state);
    
    bool isSolved;
    
    priority_queue<State *, vector<State *>, Queue> queue;

    State *goal;
    State *start;
    State *result;
    
    set<long> queueHash;
    set<long> historyHash;
    
    //set<State *, Set> queueSet;
    //set<State *, Set> historySet;
    
    vector<State *> allocations;
    vector<int> steps;
    vector<string> rawInput;
    vector<string> rawOutput;

    unsigned int size;
    
    int (*heuristic)(State *_state) = NULL;
    
};

#endif /* Game_hpp */
