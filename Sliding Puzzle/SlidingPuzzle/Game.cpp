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

    this->isSolved = false;
    
    this->goal = new State(this->size);
    this->start = new State(this->size, this->rawInput);
}


Game::Game(int _size, State &_state) {
    this->rawInput.clear();
    this->size = _size;
    
    this->isSolved = false;
    
    this->goal = new State(this->size);
    this->start = new State(_state);
}


Game::~Game() {
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
    oddRow = ( (this->start->getBlank().first + 1) % 2 != 0 );
    condB = ( (this->size % 2 == 0) and (oddRow == (inversions % 2 == 0)) );
    
    if (!(condA or condB)) {
        cerr << "This game is not solvable" << endl;
    }
    return (condA or condB);
}


bool Game::solve() {
    this->heuristic = this->heuristicB;

    int cost = this->heuristic(this->start);
    this->start->setCost(cost);
    this->start->setLevel(0);
    this->start->setParent(NULL);
    
    State *begin = new State(*this->start);
    this->allocations.push_back(begin);
    this->queue.push(begin);
    this->queueHash.insert(begin->calcHash());

    while (this->queue.size() > 0) {
        State *current = this->queue.top();
        this->queue.pop();
        this->queueHash.erase(current->calcHash());
        this->historyHash.insert(current->calcHash());
        
        vector<State *> neighbors = current->getNeighbors();
        for (int index = 0; index < neighbors.size(); index++) {
            this->allocations.push_back(neighbors[index]);
            
            bool condA = ( this->queueHash.find(neighbors[index]->calcHash()) == this->queueHash.end() );
            bool condB = ( this->historyHash.find(neighbors[index]->calcHash()) == this->historyHash.end() );
            
            if (condA and condB) {
                cost = this->heuristic(neighbors[index]);
                neighbors[index]->setParent(current);
                neighbors[index]->setLevel(neighbors[index]->getParent()->getLevel() + 1);
                neighbors[index]->setCost(cost + neighbors[index]->getLevel());
                
                this->queue.push(neighbors[index]);
                this->queueHash.insert(neighbors[index]->calcHash());
                
                if (*(this->goal) == neighbors[index]) {
                    this->isSolved = true;
                    this->result = neighbors[index];
                    current = neighbors[index];;
                    while (current->getParent() != NULL) {
                        steps.push_back(current->getMove());
                        current = current->getParent();
                    }
                    return true;
                }
            }
        }
    }
    return false;
}


bool Game::writeFile(bool _print) {
    ofstream outfile("output.txt", ofstream::out);
    if(this->isSolved) {
        if (_print) {cout << this->steps.size() << endl;}
        outfile << this->steps.size() << endl;
        for (long index = steps.size() - 1; index >= 0; index--) {
            switch (this->steps[index]) {
                case UP:
                    if(_print) {cout << "acima" << endl;}
                    outfile << "acima" << endl;
                    break;
                case DOWN:
                    if(_print) {cout << "abaixo" << endl;}
                    outfile << "abaixo" << endl;
                    break;
                case RIGHT:
                    if(_print) {cout << "direita" << endl;}
                    outfile << "direita" << endl;
                    break;
                case LEFT:
                    if(_print) {cout << "esquerda" << endl;}
                    outfile << "esquerda" << endl;
                    break;
            }
        }
    } else {
        outfile << "Sem solução" << endl;
    }
    return this->isSolved;
}



/*
 * Private Methods
 */


/*
 * Misplaced Tiles
 */
int Game::heuristicA(State *_state) {
    int distance = 0, condA = 0, condB = 0;
    
    for (int row = 0; row < _state->getSize(); row++) {
        for (int col = 0; col < _state->getSize(); col++) {
            if(_state->getElement(row, col) != BLANK) {
                condA = ( abs((_state->getElement(row, col) /  _state->getSize()) - row) != 0 );
                condB = ( abs((_state->getElement(row, col) %  _state->getSize()) - col) != 0 );
                if(condA or condB) {
                    distance++;
                }
            }
        }
    }
    return distance;
}

/*
 * Manhattan Distance
 */
int Game::heuristicB(State *_state) {
    int distance = 0, calcA = 0, calcB = 0;
    
    for (int row = 0; row < _state->getSize(); row++) {
        for (int col = 0; col < _state->getSize(); col++) {
            if(_state->getElement(row, col) != BLANK) {
                calcA = abs( (_state->getElement(row, col) /  _state->getSize()) - row );
                calcB = abs( (_state->getElement(row, col) %  _state->getSize()) - col );
                distance = distance + calcA + calcB;
            }
        }
    }
    return distance;
}

/*
 * 2 X Manhattan Distance
 */
int Game::heuristicC(State *_state) {
    int distance = 0, calcA = 0, calcB = 0;
    
    for (int row = 0; row < _state->getSize(); row++) {
        for (int col = 0; col < _state->getSize(); col++) {
            if(_state->getElement(row, col) != BLANK) {
                calcA = abs( (_state->getElement(row, col) /  _state->getSize()) - row );
                calcB = abs( (_state->getElement(row, col) %  _state->getSize()) - col );
                distance = distance + calcA + calcB;
            }
        }
    }
    return (2 * distance);
}
