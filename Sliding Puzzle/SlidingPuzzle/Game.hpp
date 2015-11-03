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
    bool solve();
    
private:
    static int heuristicA(State &_start, State &_current, State &_goal);
    static int heuristicB(State &_start, State &_current, State &_goal);
    static int heuristicC(State &_start, State &_current, State &_goal);
    
//    priority_queue<State *> queue;
    priority_queue<State *, vector<State*>, Comparator> queue;

    State *goal;
    State *start;
    
    set<State *> queueSet;
    set<State *> historySet;
    
    vector<State *> allocations;
//    vector<State *> history;
    vector<string> rawInput;

    unsigned int size;
    
    int (*heuristic)(State &_start, State &_current, State &_goal) = NULL;
    
};

#endif /* Game_hpp */
