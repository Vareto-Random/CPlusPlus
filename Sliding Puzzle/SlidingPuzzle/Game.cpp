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
    //cout << "Game::~Game invoked" << endl;
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


bool Game::solvability() {
    bool condA, condB, oddRow;
    int inversions = 0;
    vector<int> array;
    
    for (int row = 0; row < this->start->getSize(); row++) {
        for (int col = 0; col < this->start->getSize(); col++) {
            if (this->start->getElement(row, col) != BLANK) {
                array.push_back(this->start->getElement(row, col));
            }
        }
    }
    
    for (int index = 0; index < array.size() - 1; index++) {
        for (int next = index + 1; next < array.size(); next++) {
            if (array[index] > array[next]) {
                inversions++;
            }
        }
    }
    
    // http://www.cs.bham.ac.uk/~mdr/teaching/modules04/java2/TilesSolvability.html
    condA = ( (this->size % 2 != 0) and (inversions % 2 == 0) );
    //oddRow = ( (this->size - this->start->getBlank().first) % 2 != 0 );
    oddRow = ( (this->start->getBlank().first + 1) % 2 != 0 );
    condB = ( (this->size % 2 == 0) and (oddRow == (inversions % 2 == 0)) );
    
    if (!(condA or condB)) {
        cerr << "This game is not solvable" << endl;
    }
    
    return (condA or condB);
}


bool Game::solve() {
    this->heuristic = this->heuristicB;
    int count = 0;

    int cost = this->heuristic(this->start, this->start, this->goal);
    this->start->setCost(cost);
    this->start->setLevel(0);
    this->start->setParent(NULL);
    
    State *begin = new State(*this->start);
    this->allocations.push_back(begin);
    this->queue.push(begin);
    this->queueHash.insert(begin->calcHash());
    //this->queueSet.insert(begin);
    //begin->toString();

    while (this->queue.size() > 0) {
        State *current = this->queue.top();
        this->queue.pop();
        this->queueHash.erase(current->calcHash());
        this->historyHash.insert(current->calcHash());
        //this->queueSet.erase(current);
        //this->historySet.insert(current);
        count++;
        
        //current->toString();
        //cout << "-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - \n";
        
        vector<State *> neighbors = current->getNeighbors();
        for (int index = 0; index < neighbors.size(); index++) {
            this->allocations.push_back(neighbors[index]);
            
            bool condA = ( this->queueHash.find(neighbors[index]->calcHash()) == this->queueHash.end() );
            bool condB = ( this->historyHash.find(neighbors[index]->calcHash()) == this->historyHash.end() );

            //bool condA = ( this->queueSet.find(neighbors[index]) == this->queueSet.end() );
            //bool condB = ( this->historySet.find(neighbors[index]) == this->historySet.end() );
            
            if (condA and condB) {
                cost = this->heuristic(this->start, neighbors[index], this->goal);
                neighbors[index]->setParent(current);
                neighbors[index]->setLevel(neighbors[index]->getParent()->getLevel() + 1);
                neighbors[index]->setCost(cost + neighbors[index]->getLevel());
                //neighbors[index]->toString();
                
                this->queue.push(neighbors[index]);
                this->queueHash.insert(neighbors[index]->calcHash());
                //this->queueSet.insert(neighbors[index]);
                neighbors[index]->toString();
                
                if (*(this->goal) == neighbors[index]) {
                    //cout << "--------------------------------------------------------\n";
                    neighbors[index]->toString();
                    this->result = neighbors[index];
                    cout << "\nCOUNT: " << count << endl;
                    return true;
                }
            }

        }
        cout << "Queue: " << queue.size() << " Hash: " << queueHash.size() << " History: " << historyHash.size() << endl;
        cout << "--------------------------------------------------------\n";
        //cin.get();
        
    }
    
    cout << "\nCOUNT: " << count << endl;
    
    return false;
}


bool Game::showSteps() {
    State *current = this->result;
    vector<int> steps;
    
    while (current->getParent() != NULL) {
        steps.push_back(current->getMove());
        current = current->getParent();
    }
    
    cout << steps.size() << endl;
    for (long index = steps.size() - 1; index >= 0; index--) {
        switch (steps[index]) {
            case UP:
                cout << "acima" << endl;
                break;
            case DOWN:
                cout << "abaixo" << endl;
                break;
            case RIGHT:
                cout << "direita" << endl;
                break;
            case LEFT:
                cout << "esquerda" << endl;
                break;
        }
    }
    
    return true;
}


/*
 * Private Methods
 */

int Game::heuristicA(State *_start, State *_current, State *_goal) {
    int distance = 0;
    for (int row = 0; row < _start->getSize(); row++) {
        for (int col = 0; col < _start->getSize(); col++) {
            if (_goal->getElement(row, col) != _current->getElement(row, col)) {
                distance++;
            }
        }
    }
    return distance;
}


int Game::heuristicB(State *_start, State *_current, State *_goal) {
    int distance = 0;
    for (int row = 0; row < _start->getSize(); row++) {
        for (int col = 0; col < _start->getSize(); col++) {
            if (_goal->getElement(row, col) != _current->getElement(row, col)) {
                distance++;
            }
        }
    }
    return (2 * distance);
}


int Game::heuristicC(State *_start, State *_current, State *_goal) {
    int distanceGoal = 0;
    int distanceStart = 0;
    for (int row = 0; row < _start->getSize(); row++) {
        for (int col = 0; col < _start->getSize(); col++) {
            if (_start->getElement(row, col) != _current->getElement(row, col)) {
                distanceStart++;
            }
            if (_goal->getElement(row, col) != _current->getElement(row, col)) {
                distanceGoal++;
            }
        }
    }
    return 2*(distanceStart + distanceGoal);
}
