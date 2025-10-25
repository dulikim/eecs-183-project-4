/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Position.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * <#Name#>
 * <#Uniqname#>
 *
 * Project 4: Battleship
 *
 * <#description#>
 */

#include "Position.h"
#include "utility.h"


Position::Position() {
    // TODO: write implementation here.
}

Position::Position(int row_in, int col_in) {
    // TODO: write implementation here.
}

Position::Position(char row_in, char col_in) {
    // TODO: write implementation here.
}

int Position::get_row() {
    // TODO: write implementation here.
    return -1;
}

void Position::set_row(int row_in) {
    // TODO: write implementation here.
    return;
}

int Position::get_col() {
    // TODO: write implementation here.
    return -1;
}

void Position::set_col(int col_in) {
    // TODO: write implementation here.
    return;
}

void Position::write(ostream &os) {
    // TODO: write implementation here.
    return;
}

int Position::check_range(int val) {
    // TODO: write implementation here.
    return -1;
}

void Position::read(istream& is) {
    // This function is **partially** implemented for you
    // add your code below after the TODO comment
    char trash = 't';
    int row_in = 0;
    char col_in = 'c';

    // read format 1A
    is >> row_in >> col_in;

    // if stream failed, must read format (1,A)
    if (is.fail()) {
        is.clear();
        is >> trash >> row_in >> trash >> col_in >> trash;
    }

    // TODO: set row and col here


    return;
}

// Your code goes above this line.
// Don't change the implementations below!

istream &operator>>(istream &is,  Position &pos) {
    pos.read(is);
    return is;
}

ostream &operator<<(ostream &os, Position pos) {
    pos.write(os);
    return os;
}

