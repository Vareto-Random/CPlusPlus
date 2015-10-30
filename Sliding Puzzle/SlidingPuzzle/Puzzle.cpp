//
//  Puzzle.cpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/30/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Puzzle.hpp"

Puzzle::Puzzle() {
    this->matrix = NULL;
    this->ready = false;
    this->size = 0;
}

Puzzle::Puzzle(int _size) {
    this->allocate(_size);
}

Puzzle::Puzzle(int _size, int **_matrix) {
    this->allocate(_size, _matrix);
}

Puzzle::~Puzzle() {
    for (int index = 0; index < this->size; index++) {
        delete [] this->matrix[index];
    }
    delete [] this->matrix;
}

bool Puzzle::readFile(string _fileName) {
    return false;
}

bool Puzzle::solve() {
    return false;
}

bool Puzzle::allocate(int _size) {
    this->ready = false;
    if (_size <= 0) {
        return false;
    }
    
    this->size = _size;
    this->matrix = new int*[this->size];
    for (int index = 0; index < this->size; index++) {
        matrix[index] = new int[this->size];
    }
    return true;
}

bool Puzzle::allocate(int _size, int **_matrix) {
    if ((_size == 0) or (_matrix == NULL)) {
        this->ready = false;
        return false;
    }
    
    this->allocate(_size);
    this->copyMatrix(_size, _matrix);

    return true;
}

void Puzzle::copyMatrix(int _size, int** _matrix) {
    for (int row = 0; row < _size; row++) {
        for (int column = 0; column < _size; column++) {
            this->matrix[row][column] = _matrix[row][column];
        }
    }
}

