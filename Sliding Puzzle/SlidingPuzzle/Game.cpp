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
    this->heuristic = this->heuristicA;

    int cost = this->heuristic(*this->start, *this->start, *this->goal);
    this->start->setCost(cost);
    this->start->setLevel(0);
    this->start->setParent(NULL);
    
    State *begin = new State(*this->start);
    this->allocations.push_back(begin);
    this->queue.push(begin);
    this->queueSet.insert(begin);

    while (this->queue.size() > 0) {
        State *current = this->queue.top();
        this->queue.pop();
        cout << this->queueSet.erase(current) << endl;
        this->historySet.insert(current);

        current->toString();
        cout << "-  -  -  -  -  -  -  -  -  -\n";
        for (set<State *>::iterator it = this->queueSet.begin(); it != this->queueSet.end(); it++) {
            (*it)->toString();
        }
        
        
        vector<State *> neighbors = current->getNeighbors();
        for (int index = 0; index < neighbors.size(); index++) {
            this->allocations.push_back(neighbors[index]);
            //neighbors[index]->toString();
            
            //if ( (this->queueSet.find(neighbors[index]) == this->queueSet.end())){// and (this->historySet.find(neighbors[index]) == this->historySet.end()) ) {
                
                cost = this->heuristic(*this->start, *neighbors[index], *this->goal);
                neighbors[index]->setParent(current);
                neighbors[index]->setLevel(neighbors[index]->getParent()->getLevel() + 1);
                neighbors[index]->setCost(cost + neighbors[index]->getLevel());
                
                this->queue.push(neighbors[index]);
                this->queueSet.insert(neighbors[index]);
                
                if (*(this->goal) == neighbors[index]) {
                    return true;
                }
            //}

        }
        cout << "----------------------------";
        cin.get();
        
    }
    
    return false;
}


/*
 * Private Methods
 */

int Game::heuristicA(State &_start, State &_current, State &_goal) {
    int distance = 0;
    for (int row = 0; row < _start.getSize(); row++) {
        for (int col = 0; col < _start.getSize(); col++) {
            if (_goal.getElement(row, col) != _current.getElement(row, col)) {
                distance++;
            }
        }
    }
    return distance;
}


int Game::heuristicB(State &_start, State &_current, State &_goal) {
    int distance = 0;
    for (int row = 0; row < _start.getSize(); row++) {
        for (int col = 0; col < _start.getSize(); col++) {
            if (_goal.getElement(row, col) != _current.getElement(row, col)) {
                distance++;
            }
        }
    }
    return (2 * distance);
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
