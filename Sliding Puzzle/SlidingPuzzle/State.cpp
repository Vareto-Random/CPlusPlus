//
//  State.cpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/31/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "State.hpp"

/*
 * Public Methods
 */

State::State() {
    this->initialize();
}


State::State(State &_state) {
    this->initialize();
    
    this->allocate(_state.getSize());
    this->copy(_state.getBoard());
    this->cost = _state.getCost();
    this->size = _state.getSize();
}


State::State(int _size) {
    this->initialize();
    
    this->allocate(_size);
    
    int index = 0;
    for (int row = 0; row < _size; row++) {
        for (int col = 0; col < _size; col++) {
            this->board[row][col] = index;
            index++;
        }
    }
    this->board[0][0] = BLANK;
}


State::State(int _size, const vector<string> _board) {
    this->initialize();
    
    this->allocate(_size);
    
    int index = 0;
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            try {
                this->board[row][col] = stoi(_board[index]);
            } catch (invalid_argument exception) {
                this->board[row][col] = BLANK;
            }
            index++;
        }
    }
}


State::~State() {
    cout << "State::~State invoked" << endl;
    this->deallocate();
}


int State::calcHash() {
    int checkSum = 0;
    
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            checkSum += ( (this->board[row][col] * row) + col );
        }
    }
    
    return checkSum;
}


int ** State::getBoard() {
    return this->board;
}


int State::getCost() {
    return this->cost;
}


int State::getElement(int row, int col) {
    return this->board[row][col];
}


int State::getLevel() {
    return this->level;
}


int State::getSize() {
    return this->size;
}


bool State::setBoard(const int _size, const int **_board) {
    if(this->size != _size) {
        return false;
    }
    
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            this->board[row][col] = _board[row][col];
        }
    }
    
    return true;
}


bool State::setCost(int _cost) {
    this->cost = _cost;
    return true;
}


bool State::setLevel(int _level) {
    this->level = _level;
    return true;
}


bool State::setParent(State *_parent) {
    this->parent = _parent;
    return true;
}


bool State::operator()(State *_stateA, State *_stateB) {
    return _stateA->getCost() < _stateB->getCost();
}


bool State::operator<(State *_state) {
    return this->cost < _state->getCost();
}


bool State::operator>(State *_state) {
    return this->cost > _state->getCost();
}


bool State::operator==(State *_state) {
    if ((this != _state) and (this->size == _state->getSize())) {
        int **matrix = _state->getBoard();
        for (int row = 0; row < this->size; row++) {
            for (int col = 0; col < this->size; col++) {
                if (this->board[row][col] != matrix[row][col]) {
                    return false;
                }
            }
        }
    }
    return true;
}


State& State::operator=(State *_state) {
    if (this != _state) {
        if (this->size != _state->getSize()) {
            this->deallocate();
        }
        
        if (this->board == NULL) {
            this->allocate(_state->getSize());
        }
        
        this->cost = _state->getCost();
        this->level = _state->getLevel();
        this->size = _state->getSize();
        
        for (int row = 0; row < this->size; row++) {
            for (int col = 0; col < this->size; col++) {
                this->board[row][col] = _state->getElement(row, col);
            }
        }
    }
    
    return (*this);
}


State * State::getParent() {
    return this->parent;
}


vector<State *> State::getNeighbors() {
    pair<int, int> pos = this->getBlank();
    vector<int> moves = this->getMoves(pos.first, pos.second);
    vector<State *> neighbors;
    
    for (int index = 0; index < moves.size(); index++) {
        State *neighbor = new State(*this);
        int **matrix = neighbor->getBoard();
        
        switch (moves[index]) {
            case UP:
                matrix[pos.first][pos.second] = matrix[pos.first-1][pos.second];
                matrix[pos.first-1][pos.second] = BLANK;
                break;
            case DOWN:
                matrix[pos.first][pos.second] = matrix[pos.first+1][pos.second];
                matrix[pos.first+1][pos.second] = BLANK;
                break;
            case RIGHT:
                matrix[pos.first][pos.second] = matrix[pos.first][pos.second+1];
                matrix[pos.first][pos.second+1] = BLANK;
                break;
            case LEFT:
                matrix[pos.first][pos.second] = matrix[pos.first][pos.second-1];
                matrix[pos.first][pos.second-1] = BLANK;
                break;
        }
        neighbors.push_back(neighbor);
    }
    
    return neighbors;
}


void State::toString() {
    cout << "Cost: " << this->cost << "\n";
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            printf("%6d ", this->board[row][col]);
        }
        printf("\n");
    }
}

/*
 * Private Methods
 */

bool State::allocate(int _size) {
    if ((_size <= 0) or (this->board != NULL)) {
        return false;
    }
    
    this->board = new int* [_size];
    this->size = _size;
    for (int index = 0; index < _size; index++) {
        this->board[index] = new int [_size];
    }
    
    return true;
}

bool State::copy(int **_board) {
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            this->board[row][col] = _board[row][col];
        }
    }
    
    return true;
}

bool State::deallocate() {
    if (this->board != NULL) {
        for (int index = 0; index < this->size; index++) {
            if(this->board[index] != NULL) {
                delete [] this->board[index];
                this->board[index] = NULL;
            }
        }
    
        delete [] this->board;
        this->board = NULL;
        this->cost = 0;
        this->hash = 0;
        this->level = 0;
        this->parent = NULL;
        this->size = 0;
    }
    
    return true;
}


bool State::initialize() {
    this->board = NULL;
    this->cost = 0;
    this->hash = 0;
    this->level = 0;
    this->parent = NULL;
    this->size = 0;
    
    return true;
}


pair<int, int> State::getBlank() {
    pair<int, int> position;
    
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            if (this->board[row][col] == BLANK) {
                position = make_pair(row, col);
                return position;
            }
        }
    }
    
    return position;
}


vector<int> State::getMoves(const int x, const int y) {
    vector<int> moves;
    
    if ((x > 0) and (x < this->size)) {
        moves.push_back(UP);
    }
    if ((y >= 0) and (y < this->size - 1)) {
        moves.push_back(RIGHT);
    }
    if ((x >= 0) and (x < this->size - 1)) {
        moves.push_back(DOWN);
    }
    if ((y > 0) and (y < this->size)) {
        moves.push_back(LEFT);
    }
    
    return moves;
}


/*
 * Class Comparator
 */

bool Queue::operator()(State *_stateA, State *_stateB)
{
    return (_stateA->getCost() > _stateB->getCost());
}


bool Set::operator()(State *_stateA, State *_stateB) {
//    if (_stateA == _stateB) {
//        return false;
//    } else {
        int **matrixA = _stateA->getBoard();
        int **matrixB = _stateB->getBoard();
            
        for (int row = 0; row < _stateA->getSize(); row++) {
            for (int col = 0; col < _stateA->getSize(); col++) {
                if (matrixA[row][col] != matrixB[row][col]) {
                    return true;
                }
            }
        }
        return false;
//    }
}