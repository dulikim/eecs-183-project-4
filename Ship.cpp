/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Ship.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * <Duli Kim & Sally Koh>
 * <dulikim & sykoh>
 *
 * Project 4: Battleship
 *
 * <Implements the Ship class for the Battleship game>
 */

#include <cmath>

#include "Ship.h"


Ship::Ship() {
    start = Position();
    end = Position();
    size = 0;
    num_hits = 0;
}

Ship::Ship(Position start_in, Position end_in) {
    start = start_in;
    end = end_in;
    num_hits = 0;

    // computing size for horizontal
    if (is_horizontal()) {
        size = abs(start.get_col() - end.get_col()) + 1;
    }
    else {
        size = abs(start.get_row() - end.get_row()) + 1;
    }
}

Position Ship::get_start() {
    return start;
}

Position Ship::get_end() {
    return end;
}

int Ship::get_size() {
    return size;
}

bool Ship::is_horizontal() {
    return start.get_row() == end.get_row();
}

bool Ship::has_position(Position pos) {
    int pos_row = pos.get_row();
    int pos_col = pos.get_col();

    if (is_horizontal()) {
        // Same row, check column range
        if (pos_row == start.get_row()) {
            int min_col = min(start.get_col(), end.get_col());
            int max_col = max(start.get_col(), end.get_col());
            return (pos_col >= min_col && pos_col <= max_col);
        }
    }
    else {
        // Same column, check row range
        if (pos_col == start.get_col()) {
            int min_row = min(start.get_row(), end.get_row());
            int max_row = max(start.get_row(), end.get_row());
            return (pos_row >= min_row && pos_row <= max_row);
        }
    }

    return false;
}

void Ship::hit() {
    if (num_hits < size) {
        num_hits++;
    }
}

bool Ship::has_sunk() {
    if (num_hits == size) {
        return true;
    }
    else {
        return false;
    }
}
