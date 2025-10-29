/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Game.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * <Duli Kim & Sally Koh>
 * <dulikim & sykoh>
 *
 * Project 4: Battleship
 *
 * Implements the main game flow and controls player actions.
 */

#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

// === Constructors ===
Game::Game() {
    p1 = Player();
    p2 = Player();
}

Game::Game(Player player1, string grid1, Player player2, string grid2) {
    p1 = player1;
    p2 = player2;

    // === p1 setup ===
    if (!grid1.empty()) {
        bool loaded = p1.load_grid_file(grid1);
        if (!loaded) {
            cout << "Generating random grid for " << p1.get_name() << endl;
            generate_random_grid(p1);
        }
    } else {
        cout << "Generating random grid for " << p1.get_name() << endl;
        generate_random_grid(p1);
    }

    // === p2 setup ===
    if (!grid2.empty()) {
        bool loaded = p2.load_grid_file(grid2);
        if (!loaded) {
            cout << "Generating random grid for " << p2.get_name() << endl;
            generate_random_grid(p2);
        }
    } else {
        cout << "Generating random grid for " << p2.get_name() << endl;
        generate_random_grid(p2);
    }
}

// === Accessors ===
Player Game::get_p1() {
    return p1;
}

Player Game::get_p2() {
    return p2;
}

// === Input and Validation ===
string Game::get_move(string player_name) {
    string move;
    cout << player_name << " enter your move:" << endl;
    cin >> move;
    return move;
}

bool Game::check_valid_move(string move) {
    // Error 1: check string length
    if (move.length() != 2) {
        cout << p1.get_name() << " you entered an invalid input" << endl;
        return false;
    }

    // Extract row/col
    char rowChar = move[0];
    char colChar = move[1];

    // Convert lowercase letter
    colChar = toupper(colChar);

    // Error 2: check bounds
    if (rowChar < '1' || rowChar > '8' || colChar < 'A' || colChar > 'H') {
        cout << p1.get_name() << " you entered an invalid position" << endl;
        return false;
    }

    // Valid
    return true;
}

// === Main Game Loop ===
void Game::start(char difficulty, int max_num_rounds) {
    int round = 0;

    while (!p1.destroyed() && !p2.destroyed() && round < max_num_rounds) {
        round++;

        // --- Player 1 Turn ---
        string move = get_move(p1.get_name());
        while (!check_valid_move(move)) {
            move = get_move(p1.get_name());
        }

        Position pos(move);
        p1.attack(p2, pos);

        cout << "Your grid" << endl;
        p1.print_grid();

        cout << p2.get_name() << "'s grid" << endl;
        p1.print_guess_grid();

        if (p2.destroyed()) {
            cout << "Game over, winner is " << p1.get_name()
                 << " in " << round << " rounds" << endl;
            return;
        }

        // --- Player 2 Turn ---
        opponent_make_move(difficulty);

        cout << "Your grid" << endl;
        p1.print_grid();

        cout << p2.get_name() << "'s grid" << endl;
        p1.print_guess_grid();

        if (p1.destroyed()) {
            cout << "Game over, winner is " << p2.get_name()
                 << " in " << round << " rounds" << endl;
            return;
        }
    }

    // --- End condition ---
    if (!p1.destroyed() && !p2.destroyed() && round == max_num_rounds) {
        cout << "Game over, winner is no one in "
             << round << " rounds" << endl;
    }
}

// === Random Grid Generation ===
void Game::generate_random_grid(Player &p) {
    bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};

    for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
        int i = p.get_num_ships() + 1;
        if (i > 2) {
            i--;
        }

        int row = get_random_number() % MAX_GRID_SIZE;
        int col = get_random_number() % MAX_GRID_SIZE;
        Position pos1(row, col);

        if (!grid[row][col]) {
            Position pos2;
            if (row + i < MAX_GRID_SIZE) {
                pos2 = Position(row + i, col);
            } else if (col + i < MAX_GRID_SIZE) {
                pos2 = Position(row, col + i);
            } else if (col - i >= 0) {
                pos2 = Position(row, col - i);
            } else if (row - i >= 0) {
                pos2 = Position(row - i, col);
            } else {
                continue;
            }

            Ship s(pos1, pos2);
            bool pos2_taken = false;

            if (s.is_horizontal()) {
                int start = min(pos1.get_col(), pos2.get_col());
                int end = max(pos1.get_col(), pos2.get_col());
                for (int j = start; j <= end; j++) {
                    if (grid[pos1.get_row()][j]) {
                        pos2_taken = true;
                        break;
                    }
                }
                for (int j = start; j <= end; j++) {
                    grid[pos1.get_row()][j] = true;
                }
            } else {
                int start = min(pos1.get_row(), pos2.get_row());
                int end = max(pos1.get_row(), pos2.get_row());
                for (int j = start; j <= end; j++) {
                    if (grid[j][pos1.get_col()]) {
                        pos2_taken = true;
                        break;
                    }
                }
                for (int j = start; j <= end; j++) {
                    grid[j][pos1.get_col()] = true;
                }
            }

            if (pos2_taken) {
                continue;
            }

            p.add_ship(s);
        }
    }
}

// === CPU AI ===
void Game::opponent_make_move(char difficulty) {
    if (difficulty == EMULATE) {
        Position next;
        cout << "Enter CPU emulation move: ";
        cin >> next;
        cout << endl;
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
    }

    else if (difficulty == EASY) {
#ifndef NOCPU
        int randRow = get_random_number() % MAX_GRID_SIZE;
        int randCol = get_random_number() % MAX_GRID_SIZE;
        Position randCoord(randRow, randCol);
        p2.attack(p1, randCoord);
        cout << "You received an attack at " << randCoord << endl << endl;
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    }

    else if (difficulty == MEDIUM) {
#ifndef NOCPU
        static int lastRow = -1;
        static int lastCol = -1;
        int nextRow, nextCol;

        // If no previous hit, random
        if (lastRow == -1 && lastCol == -1) {
            nextRow = get_random_number() % MAX_GRID_SIZE;
            nextCol = get_random_number() % MAX_GRID_SIZE;
        } else {
            // Check surrounding positions
            if (lastCol + 1 < MAX_GRID_SIZE) {
                nextRow = lastRow;
                nextCol = lastCol + 1;
            } else if (lastRow + 1 < MAX_GRID_SIZE) {
                nextRow = lastRow + 1;
                nextCol = lastCol;
            } else if (lastCol - 1 >= 0) {
                nextRow = lastRow;
                nextCol = lastCol - 1;
            } else if (lastRow - 1 >= 0) {
                nextRow = lastRow - 1;
                nextCol = lastCol;
            } else {
                nextRow = get_random_number() % MAX_GRID_SIZE;
                nextCol = get_random_number() % MAX_GRID_SIZE;
            }
        }

        Position next(nextRow, nextCol);
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;

        // Remember if last hit
        if (p1.get_grid_at(nextRow, nextCol) == HIT_LETTER) {
            lastRow = nextRow;
            lastCol = nextCol;
        } else {
            lastRow = -1;
            lastCol = -1;
        }
#else
        Position next;
        cin >> next;
        if (cin.fail()) {
            cin.clear();
            next = Position(7, 4);
        }
        p2.attack(p1, next);
        cout << "You received an attack at " << next << endl << endl;
#endif
    }
}
