//
//  Game.cpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/31/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Game.hpp"

/*
 * Public Methods
 */

Game::Game(string _fileName) {
    this->readFile(_fileName);

    this->goal = new State(this->size);
    this->start = new State(this->size, this->rawInput);
}


Game::Game(int _size, State &_state) {
    this->rawInput.clear();
    this->size = _size;
    
    this->goal = new State(this->size);
    this->start = new State(_state);
}


Game::~Game() {
    cout << "Game::~Game invoked" << endl;
    delete this->goal;
    delete this->start;
    
    for (int index = 0; index < this->allocations.size(); index++) {
        delete this->allocations[index];
        this->allocations[index] = NULL;
    }
}


State Game::getGoal() {
    return *(this->goal);
}


State Game::getStart() {
    return *(this->start);
}


bool Game::readFile(string _fileName) {
    string tile;
    ifstream infile(_fileName, ifstream::in);
    
    if (infile.is_open()) {
        if (infile.good()) {
            infile >> this->size;
        }
        while (infile.good()) {
            infile >> tile;
            this->rawInput.push_back(tile);
        }
        return true;
    } else {
        cerr << "SlidingPuzzle could not read input file.\n";
        return false;
    }
}


bool Game::solve() {
    State *begin = new State(*this->start);
    this->queue.push(begin);
    this->allocations.push_back(begin);
    
    while (this->queue.size() > 0) {
        State *current = this->queue.top();
        this->queue.pop();
        this->history.push_back(current);
        
        current->toString();
        vector<State *> neighbors = current->getNeighbors();
        for (int index = 0; index < neighbors.size(); index++) {
            this->allocations.push_back(neighbors[index]);
            neighbors[index]->toString();
        }
        
        
        
    }
    
    
    return false;
}

/*
 * Private Methods
 */

int Game::heuristicA(State &_start, State &_current, State &_goal) {
    int distanceGoal = 0;
    int distanceStart = 0;
    for (int row = 0; row < _start.getSize(); row++) {
        for (int col = 0; col < _start.getSize(); col++) {
            if (_start.getElement(row, col) != _current.getElement(row, col)) {
                distanceStart++;
            }
            if (_goal.getElement(row, col) != _current.getElement(row, col)) {
                distanceGoal++;
            }
        }
    }
    return (distanceStart + distanceGoal);
}

int Game::heuristicB(State &_start, State &_current, State &_goal) {
    int distanceGoal = 0;
    int distanceStart = 0;
    for (int row = 0; row < _start.getSize(); row++) {
        for (int col = 0; col < _start.getSize(); col++) {
            if (_start.getElement(row, col) != _current.getElement(row, col)) {
                distanceStart++;
            }
            if (_goal.getElement(row, col) != _current.getElement(row, col)) {
                distanceGoal++;
            }
        }
    }
    return 2*(distanceStart + distanceGoal);
}

int Game::heuristicC(State &_start, State &_current, State &_goal) {
    int distanceGoal = 0;
    int distanceStart = 0;
    for (int row = 0; row < _start.getSize(); row++) {
        for (int col = 0; col < _start.getSize(); col++) {
            if (_start.getElement(row, col) != _current.getElement(row, col)) {
                distanceStart++;
            }
            if (_goal.getElement(row, col) != _current.getElement(row, col)) {
                distanceGoal++;
            }
        }
    }
    return 2*(distanceStart + distanceGoal);
}
