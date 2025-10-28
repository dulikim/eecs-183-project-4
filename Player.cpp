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
     // TODO: write implementation here.
     return;
 }
 
 void Player::attack(Player &opponent, Position pos) {
     int r = pos.get_row();
     int c = pos.get_col();
     
     //if pos hasn't been hit yet
     
     //Print "miss" if pos has been hit yet
     if (opponent.grid[r][c] == HIT_LETTER || opponent.grid[r][c] == MISS_LETTER) {
         cout << name << " " << pos << " miss" << endl;
         return;
     }
     //when the ship sink
     if (opponent.grid[r][c] )
         
         
         
     return;
 }
 
 void Player::announce_ship_sunk(int size) {
     // TODO: write implementation here.
     return;
 }
 
 bool Player::load_grid_file(string filename) {
     // TODO: write implementation here.
     return false;
 }
 
 bool Player::destroyed() {
     // TODO: write implementation here.
     return false;
 }
 
 // Your code goes above this line.
 // Don't change the implementations below!
 
 void Player::print_grid() {
     ::print_grid(grid);
 }
 
 void Player::print_guess_grid() {
     ::print_grid(guess_grid);
 }
 