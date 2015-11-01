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
    this->deallocate();
}

pair<int, int> State::findBlank() {
    pair<int, int> position;
    
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            if (this->board[row][col] == BLANK) {
                position = make_pair(row, col);
            }
        }
    }
    
    return position;
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


State& State::operator=(State &_state) {
    if (this != &_state) {
        if (this->size != _state.getSize()) {
            this->deallocate();
        }
        
        if (this->board == NULL) {
            this->allocate(_state.getSize());
        }
        
        this->cost = _state.getCost();
        this->size = _state.getSize();
        for (int row = 0; row < this->size; row++) {
            for (int col = 0; col < this->size; col++) {
                this->board[row][col] = _state.getElement(row, col);
            }
        }
    }
    
    return (*this);
}

State State::swap(const int move) {
    State state = *(this);
    int **matrix = state.getBoard();
    pair<int, int> pos = this->findBlank();
    
    switch (move) {
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
    this->toString();
    state.toString();
    return state;
}


void State::toString() {
    cout << "Size: " << this->size << "\n";
    for (int row = 0; row < this->size; row++) {
        for (int col = 0; col < this->size; col++) {
            cout << this->board[row][col] << " ";
        }
        cout << "\n";
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
    }
    
    return true;
}


bool State::initialize() {
    this->cost = 0;
    this->board = NULL;
    this->size = 0;
    
    return true;
}