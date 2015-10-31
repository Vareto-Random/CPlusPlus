//
//  Puzzle.cpp
//  SlidingPuzzle
//
//  Created by Rafael Vareto on 10/30/15.
//  Copyright © 2015 Universidade Federal de Minas Gerais. All rights reserved.
//

#include "Puzzle.hpp"

/*
 * Public Methods
 */

Puzzle::Puzzle(const string _fileName) {
    this->initialize();
    this->readFile(_fileName);
    this->allocate(this->size);
    this->populate(this->rawMatrix);
}


Puzzle::Puzzle(const int _size) {
    this->initialize();
    this->allocate(_size);
}


Puzzle::Puzzle(const int _size, const int **_matrix) {
    this->initialize();
    this->allocate(_size, _matrix);
}


Puzzle::~Puzzle() {
    if(this->matrix != NULL) {
        for (int index = 0; index < this->size; index++) {
            delete [] this->matrix[index];
        }
        delete [] this->matrix;
    }
    
    if(this->goal != NULL) {
        for (int index = 0; index < this->size; index++) {
            delete [] this->goal[index];
        }
        delete [] this->goal;
    }
}


bool Puzzle::populate(const vector<string> &_rawFile) {
    if (((this->size * this->size) != _rawFile.size())
        or (this->goal == NULL) or (this->matrix == NULL)) {
        return false;
    }
    
    int index = 0;
    for (int row = 0; row < this->size; row++) {
        for (int column = 0; column < this->size; column++) {
            try {
                this->goal[row][column] = index;
                this->matrix[row][column] = stoi(this->rawMatrix[index]);
            } catch (invalid_argument exception) {
                this->goal[row][column] = index;
                this->matrix[row][column] = BLANK;
            }
            index++;
        }
    }
    
    this->goal[0][0] = BLANK;
    this->ready = true;
    return true;
}


bool Puzzle::readFile(const string _fileName) {
    string tile;
    ifstream infile(_fileName, ifstream::in);
    
    if (infile.is_open()) {
        if (infile.good()) {
            infile >> this->size;
        }
        while (infile.good()) {
            infile >> tile;
            this->rawMatrix.push_back(tile);
        }
        return true;
    } else {
        cerr << "SlidingPuzzle could not read input file.\n";
        return false;
    }
}


bool Puzzle::solve() {
    if (!this->ready) {
        return false;
    }
    
    
    return true;
}

/*
 * Private Methods
 */

bool Puzzle::allocate(const int _size) {
    if (_size <= 0) {
        this->goal = NULL;
        this->matrix = NULL;
        this->ready = false;
        this->size = 0;
        return false;
    }
    
    this->goal = new int*[this->size];
    this->matrix = new int*[this->size];
    this->size = _size;
    this->ready = false;
    
    for (int index = 0; index < this->size; index++) {
        this->goal[index] = new int[this->size];
        this->matrix[index] = new int[this->size];
    }
    
    return true;
}


bool Puzzle::allocate(const int _size, const int **_matrix) {
    bool conA = this->allocate(_size);
    bool conB = this->copy(_size, _matrix);
    return (conA and conB);
}


bool Puzzle::copy(const int _size, const int** _matrix) {
    if ((this->size != _size) or (_matrix ==  NULL) or (this->matrix == NULL)) {
        this->ready = false;
        return false;
    }
    
    for (int row = 0; row < _size; row++) {
        for (int column = 0; column < _size; column++) {
            this->matrix[row][column] = _matrix[row][column];
        }
    }
    
    this->size = _size;
    this->ready = true;
    return true;
}


bool Puzzle::initialize(){
    this->goal = NULL;
    this->matrix = NULL;
    this->ready = false;
    this->size = 0;
    return true;
}
