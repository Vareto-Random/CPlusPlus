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
    this->size = SIZE;
    this->allocate(this->size);
}


State::State(unsigned int _size) {
    this->size = _size;
    this->allocate(this->size);
}


State::State(unsigned int _size, int **_board) {
    this->size = _size;
    this->allocate(this->size);
    
    for (int row = 0; row < this->size; row++) {
        for (int column = 0; column < this->size; column++) {
            this->board[row][column] = _board[row][column];
        }
    }
}


State::~State() {
    for (int index = 0; index < this->size; index++) {
        delete [] this->board[index];
    }
    delete [] this->board;
}


int ** State::getBoard() {
    return this->board;
}


unsigned int State::getCost() {
    return this->cost;
}


int State::getElement(unsigned int row, unsigned int col) {
    return this->board[row][col];
}


unsigned int State::getSize() {
    return this->size;
}


bool State::setBoard(unsigned int _size, int **_board) {
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


bool State::setCost(unsigned int _cost) {
    this->cost = _cost;
    return true;
}


State State::operator=(State &_state) {
    if ((this != &_state) and (this->size == _state.getSize())) {
        for (int row = 0; row < this->size; row++) {
            for (int col = 0; col < this->size; col++) {
                this->board[row][col] = _state.getElement(row, col);
            }
        }
    }
    
    return (*this);
}

/*
 * Private Methods
 */

bool State::allocate(unsigned int _size) {
    if (_size <= 0) {
        return false;
    }
    
    this->board = new int* [this->size];
    for (int index = 0; index < this->size; index++) {
        this->board[index] = new int [this->size];
    }
    
    return true;
}