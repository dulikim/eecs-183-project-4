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
 * Implements the Game class which controls the battleship game by interacting between players, grids, and difficulty levels 
 */

 #include <fstream>

 #include "Game.h"
 
 Game::Game() {
     p1 = Player();
     p2 = Player();
 }
 
 Game::Game(Player player1, string grid1, Player player2, string grid2) {
     p1 = player1;
     p2 = player2;
 
     // p1 setup
     if (!grid1.empty()) {
         // Try to load from file
         bool loaded = p1.load_grid_file(grid1);
         if (!loaded) {
             cout << "Generating random grid for " << p1.get_name() << endl;
             generate_random_grid(p1);
         }
     }
     else {
         // No filename provided → random grid
         cout << "Generating random grid for " << p1.get_name() << endl;
         generate_random_grid(p1);
     }
 
     // p2 setup
     if (!grid2.empty()) {
         bool loaded = p2.load_grid_file(grid2);
         if (!loaded) {
             cout << "Generating random grid for " << p2.get_name() << endl;
             generate_random_grid(p2);
         }
     }
     else {
         cout << "Generating random grid for " << p2.get_name() << endl;
         generate_random_grid(p2);
     }
 }
 
 
 Player Game::get_p1() {
     return p1;
 }
 
 Player Game::get_p2() {
     return p2;
 }
 
 string Game::get_move(string player_name) {
     string move;
     cout << player_name << " enter your move: ";
     cin >> move;
     return move;
 }
 
 bool Game::check_valid_move(string move) {
     // Error 1: checking string length
     if (move.length() != 2) {
         cout << p1.get_name() << " you entered an invalid input" << endl;
         return false;
     }
 
     // extracting row and col chars from string
     char rowChar = move[0];
     char colChar = move[1];
 
     // converting lowercase to uppercase
     if (colChar >= 'a' && colChar <= 'h') {
         colChar = toupper(colChar);
     }
 
     // Error 2: checking row and column range
     if (rowChar < '1' || rowChar > '8' || colChar < 'A' || colChar > 'H') {
         cout << p1.get_name() << " you entered an invalid position" << endl;
         return false;
     }
 
     // Valid Move: passed both checks
     return true;
 }
 
 void Game::start(char difficulty, int max_num_rounds) {
     int round = 0;
 
     // continue until someone wins or we reach the round limit
     while (!p1.destroyed() && !p2.destroyed() && round < max_num_rounds) {
         round++;
 
         // p1 turn
         string move = get_move(p1.get_name());
         while (!check_valid_move(move)) {
             move = get_move(p1.get_name());
         }
 
         // converting move string to positions
         Position pos(move);
         p1.attack(p2, pos);
 
         // print grids
         cout << "Your grid" << endl;
         p1.print_grid();
 
         cout << p2.get_name() << "'s grid" << endl;
         p1.print_guess_grid();
 
         // check if p1 won
         if (p2.destroyed()) {
             cout << "Game over, winner is " << p1.get_name()
                  << " in " << round << " rounds" << endl;
             break; // Don’t let CPU move after p1 wins
         }
 
         // p2 turn (CPU)
         opponent_make_move(difficulty);
 
         // print grids
         cout << "Your grid" << endl;
         p1.print_grid();
 
         cout << p2.get_name() << "'s grid" << endl;
         p1.print_guess_grid();
 
         // check if p2 wins
         if (p1.destroyed()) {
             cout << "Game over, winner is " << p2.get_name()
                  << " in " << round << " rounds" << endl;
             break;
         }
     }
 
     // If game ended due to reaching max rounds and no one destroyed
     if (!p1.destroyed() && !p2.destroyed() && round == max_num_rounds) {
         cout << "Game over, winner is " << p1.get_name()
              << " in " << round << " rounds" << endl;
     }
 }
 
 // Your code goes above this line.
 // Don't change the implementations below!
 
 void Game::generate_random_grid(Player &p) {
     // grid to check which position has been taken
     bool grid[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{false}};
 
     for (int k = 0; k < 10 && p.get_num_ships() < 5; k++) {
         // i is the length of the ship to be made
         // decrementing i to create 2 ships of size 3
         int i = p.get_num_ships() + 1;
         if (i > 2) {
             i--;
         }
 
         // generate random position 1
         int row = get_random_number() % MAX_GRID_SIZE;
         int col = get_random_number() % MAX_GRID_SIZE;
         Position pos1(row, col);
 
         if (!grid[row][col]) {
             Position pos2;
             // Check if creating position two is not off the grid relative to
             // position 1 inthe order of bottom, right, left, top
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
                 // start and end depends on if pos1 is to the left of pos2
                 int start = pos1.get_col() < pos2.get_col() ?
                             pos1.get_col() : pos2.get_col();
                 int end = pos1.get_col() < pos2.get_col() ?
                           pos2.get_col() : pos1.get_col();
                 // Loop through start and end to check if any of the positions
                 // has been taken
                 for (int j = start; j <= end; j++) {
                     // break out of the loop if any of the position is taken
                     if (grid[pos1.get_row()][j]) {
                         pos2_taken = true;
                         break;
                     }
                 }
 
                 // If none of the positions were taken, set them as taken
                 for (int j = start; j <= end; j++) {
                     grid[pos1.get_row()][j] = true;
                 }
             } else {
                 // start and end depends on if pos1 is to the left of pos2
                 int start = pos1.get_row() < pos2.get_row() ?
                             pos1.get_row() : pos2.get_row();
                 int end = pos1.get_row() < pos2.get_row() ?
                           pos2.get_row() : pos1.get_row();
                 // Loop through start and end to check if any of the positions
                 // has been taken
                 for (int j = start; j <= end; j++) {
                     // break out of the loop if any of the position is taken
                     if (grid[j][pos1.get_col()]) {
                         pos2_taken = true;
                         break;
                     }
                 }
 
                 // If none of the positions were taken, set them as taken
                 for (int j = start; j <= end; j++) {
                     grid[j][pos1.get_col()] = true;
                 }
             }
 
             // Restart from beginning
             if (pos2_taken) {
                 continue;
             }
 
             // Add the ship to p2's ships
             p.add_ship(s);
         }
     }
 }
 
 void Game::opponent_make_move(char difficulty) {
     if (difficulty == EMULATE) {
         Position next;
         cout << "Enter CPU emulation move: ";
         cin >> next;
         cout << endl;
         p2.attack(p1, next);
         cout << "You received an attack at " << next << endl << endl;
     } else if (difficulty == EASY) {
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
     } else if (difficulty == MEDIUM) {
         // Simple AI that checks right, bottom, left, top of hit position
 #ifndef NOCPU
         static int lastRow = -1;
         static int lastCol = -1;
 
         int nextRow;
         int nextCol;
         
         // Call the random row and column when it hasn't been hit before
         if (lastRow == -1 && lastCol == -1) {
             nextRow = get_random_number() % MAX_GRID_SIZE;
             nextCol = get_random_number() % MAX_GRID_SIZE;
         }
         else {
         //Check right, bottom, left, top of the hit position if it has been hit before
             if (lastCol + 1 < MAX_GRID_SIZE) {
                 nextRow = lastRow;
                 nextCol = lastCol + 1;
             }
             else if (lastRow + 1 < MAX_GRID_SIZE) {
                 nextRow = lastRow + 1;
                 nextCol = lastCol;
             }
             else if (lastCol - 1 >= 0) {
                 nextRow = lastRow;
                 nextCol = lastCol - 1;
             }
             else if (lastRow - 1 >= 0) {
                 nextRow = lastRow - 1;
                 nextCol = lastCol;
             }
             else {
                 nextRow = get_random_number() % MAX_GRID_SIZE;
                 nextCol = get_random_number() % MAX_GRID_SIZE;
             }
         }
         Position next(nextRow, nextCol);
         p2.attack(p1, next);
         cout << "You received an attack at " << next << endl << endl;
         
         //Remember the position when the attack was successful
         if (p1.get_grid_at(nextRow, nextCol) == HIT_LETTER) {
             lastRow = nextRow;
             lastCol = nextCol;
         }
         else {
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
 
 
 