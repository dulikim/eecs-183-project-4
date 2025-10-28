/**
 * Copyright 2025 University of Michigan EECS183
 *
 * Player.cpp
 * Project UID 95f0d1fcee98fd521df7bce6625c2263
 *
 * Sally Koh, Duli Kim
 * sykoh, dulikim
 *
 * Project 4: Battleship
 *
 * <#description#>
 */

 #include <fstream>

 #include "Player.h"
 
 
 Player::Player() {
     name = "";
     num_ships = 0;
     remaining_ships = 0;
     init_grid();
 }
 
 Player::Player(string name_val) {
     name = name_val;
     num_ships = 0;
     remaining_ships = 0;
     init_grid();
 }
 
 void Player::init_grid() {
     for (int r = 0; r < MAX_GRID_SIZE; ++r) {
             for (int c = 0; c < MAX_GRID_SIZE; ++c) {
                 grid[r][c] = EMPTY_LETTER;
                 guess_grid[r][c] = EMPTY_LETTER;
             }
         }
 }
 
 string Player::get_name() {
     return name;
 }
 
 int Player::get_num_ships() {
     return num_ships;
 }
 
 int Player::get_remaining_ships() {
     return remaining_ships;
 }
 
 char Player::get_grid_at(int row, int col) {
     return grid[row][col];
 }
 
 char Player::get_guess_grid_at(int row, int col) {
     return guess_grid[row][col];
 }
 
 void Player::add_ship(Ship ship) {
    // if player has the max num of ships, don't add more
    if (num_ships == MAX_NUM_SHIPS) {
        return;
    }

    // adds ship in the player's ship's array
    ships[num_ships] = ship; 

    // updating ship counters
    num_ships++;
    remaining_ships++;
    
    // get start & end positions of the ship
    Position start = ship.get_start();
    Position end = ship.get_end();

    int start_row = start.get_row();
    int start_col = start.get_col();
    int end_row = end.get_row();
    int end_col = end.get_col();

    // placing the ship on the grid
    if (ship.is_horizontal()) {
        // horizontal ship => same row with diff/multiple columns
        int left = min(start_col, end_col);
        int right = max(start_col, end_col);
        
        // for loop to update ship letter
        for (int c = left; c <= right; ++c) {
            grid[start_row][c] = SHIP_LETTER;
        }
    } else {
        // vertical ship => same col with diff/multiple rows
        int top = min(start_row, end_row);
        int bottom = max(start_row, end_row);

        // for loop to update ship letter
        for (int r = top; r <= bottom; ++r) {
            grid[r][start_col] = SHIP_LETTER;
        }
    }
 }
 
 void Player::attack(Player &opponent, Position pos) {
     int r = pos.get_row();
     int c = pos.get_col();
     
     //Print "miss" if pos has been hit yet
     if (opponent.grid[r][c] == HIT_LETTER || opponent.grid[r][c] == MISS_LETTER) {
         cout << name << " " << pos << " miss" << endl;
         return;
     }
     
     //Mark as SHIP_LETTER if it has been hit
     if (opponent.grid[r][c] == SHIP_LETTER) {
         opponent.grid[r][c] = HIT_LETTER;
         guess_grid[r][c] = HIT_LETTER;
         cout << name << " " << pos << " hit" << endl;
         
         //Check which ship has been hit
         for (int i = 0; i < opponent.num_ships; ++i) {
             if (opponent.ships[i].has_position(pos)) {
                 opponent.ships[i].hit();
                 //Check if the ship has sunk
                 if (opponent.ships[i].has_sunk()) {
                     opponent.remaining_ships--;
                     announce_ship_sunk(opponent.ships[i].get_size());
                 }
             }
         }
     }
     //Mark as MISS_LETTER if it hit the empty space
     else {
         opponent.grid[r][c] = MISS_LETTER;
         guess_grid[r][c] = MISS_LETTER;
         cout << name << " " << pos << " miss" << endl;
         return;
         
     }
 }
 
 void Player::announce_ship_sunk(int size) {
     if (size == 2) {
         cout << "Congratulations " << name << "! You sunk a Destroyer" << endl;
     }
     else if (size == 3) {
         cout << "Congratulations " << name << "! You sunk a Submarine" << endl;
     }
     else if (size == 4) {
         cout << "Congratulations " << name << "! You sunk a Battleship" << endl;
     }
     else if (size == 5) {
         cout << "Congratulations " << name << "! You sunk a Carrier" << endl;
     }
 }
 
 bool Player::load_grid_file(string filename) {
    ifstream file(filename);

    // if file can't be open then return false
    if (!file.is_open()) {
        return false;
    }

    Position start;
    Position end;

    while (file >> start >> end) {
        Ship ship(start, end);
        add_ship(ship);
    }

    file.close();
    return true;
 }
 
 bool Player::destroyed() {
     return remaining_ships == 0;
 }

 // Your code goes above this line.
 // Don't change the implementations below!
 
 void Player::print_grid() {
     ::print_grid(grid);
 }
 
 void Player::print_guess_grid() {
     ::print_grid(guess_grid);
 }
 