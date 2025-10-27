/**
 * Copyright 2025 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 8885f2d9f10d2f99bc099aa9c3fc0543
 *
 * Project 4: Battleship
 * 
 * Duli Kim & Sally Koh
 * dulikim & sykoh
 * 
 * Contains functions for testing classes in the project. 
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "Position.h"
#include "Ship.h"
#include "Player.h"
#include "Game.h"
#include "utility.h"

using namespace std;

void test_position();
void test_ship();
void test_player();
void test_game();
void test_project_setup();

void startTests() {
    test_project_setup();
    test_position();
    test_ship();
    test_player();
    
    return;
}

void test_position() {
    cout << "TESTING: Position Class" << endl;
    
    // test of default constructor
    Position p1;
    // test of the other constructor
    Position p2(3, 9);

    // test of member function: set_row(int row_in)
    p1.set_row(5);
    // test of member function: set_col(int col_in)
    p1.set_col(3);

    // test of member functions get_row() and get_col()
    cout << "(" << p1.get_row()
         << ", " << p1.get_col()
         << ")" << endl;

    // you can also do cin >> p1;
    p1.read(cin);
    cout << p1 << endl;

    // test of check range
    p1.set_row(20);
    p1.set_col(-4);
    cout <<"Expected: (8,A), ";
    cout << "Out of range (20,-4) adjusted: ";
    p1.write(cout);
    cout << endl;

    // Read() function
    cout << "Enter position: ";
    p1.read(cin);
    cout << "You entered: ";
    p1.write(cout);
    cout << endl;

    // Test lowercase input with stringstream
    istringstream input("(5,g)");
    Position p3;
    p3.read(input);
    cout << "Expected: (5,G), ";
    cout << "Read from '(5,g)': ";
    p3.write(cout);
    cout << endl;

}

void test_ship() {
    cout << "===============================" << endl;
    cout << "TESTING: Ship Class" << endl;
    cout << "===============================" << endl;

    // 1. Test default constructor 
    Ship s_default;
    cout << "Default Constructor:" << endl;
    cout << "Start: " << s_default.get_start() << " | End: " << s_default.get_end()
         << " | Size: " << s_default.get_size() << endl;
    cout << endl;

    // 2. Test non-default constructor (horizontal)
    Position p1(1, 1);   // (1, A)
    Position p2(1, 3);   // (1, C)
    Ship s1(p1, p2);

    cout << "Horizontal Ship Constructor:" << endl;
    cout << "Expected size = 3 -> Got: " << s1.get_size() << endl;
    cout << "Expected horizontal = 1 -> Got: " << s1.is_horizontal() << endl;
    cout << "Has (1,2)? Expected 1 -> Got: " << s1.has_position(Position(1, 2)) << endl;
    cout << "Has (2,2)? Expected 0 -> Got: " << s1.has_position(Position(2, 2)) << endl;
    cout << endl;

    // 3. Test non-default constructor (vertical) ===
    Position p3(3, 5);   // (3, E)
    Position p4(6, 5);   // (6, E)
    Ship s2(p3, p4);

    cout << "Vertical Ship Constructor:" << endl;
    cout << "Expected size = 4 -> Got: " << s2.get_size() << endl;
    cout << "Expected horizontal = 0 -> Got: " << s2.is_horizontal() << endl;
    cout << "Has (5,5)? Expected 1 -> Got: " << s2.has_position(Position(5, 5)) << endl;
    cout << "Has (5,6)? Expected 0 -> Got: " << s2.has_position(Position(5, 6)) << endl;
    cout << endl;

    // 4. Test reversed order (end before start)
    Position p5(7, 7);   // (7, G)
    Position p6(7, 3);   // (7, C)
    Ship s3(p5, p6);     // reversed horizontally

    cout << "Reversed Horizontal Ship:" << endl;
    cout << "Expected size = 5 -> Got: " << s3.get_size() << endl;
    cout << "Has (7,5)? Expected 1 -> Got: " << s3.has_position(Position(7, 5)) << endl;
    cout << "Has (7,2)? Expected 0 -> Got: " << s3.has_position(Position(7, 2)) << endl;
    cout << endl;

    // 5. Test hit() and has_sunk()
    Ship s4(Position(2, 2), Position(2, 4)); // size 3

    cout << "Hit & Sunk Tests:" << endl;
    cout << "Expected sunk = 0 -> Got: " << s4.has_sunk() << endl;

    s4.hit();
    cout << "After 1 hit -> Sunk? Expected 0 -> Got: " << s4.has_sunk() << endl;

    s4.hit();
    s4.hit();
    cout << "After 3 hits -> Sunk? Expected 1 -> Got: " << s4.has_sunk() << endl;

    // Try hitting more than size (should not increment further)
    s4.hit();
    cout << "After extra hit -> Still sunk? Expected 1 -> Got: " << s4.has_sunk() << endl;

    cout << endl;
}

void test_player() {
    // Write your tests here
    return;
}

void test_project_setup() {
    // open file to verify setup
    ifstream ins;
    ins.open("grid1.txt");

    // check for fail state
    if (ins.fail()) {
        cout << "Project was not created correctly." << endl;
        cout << "Text files are not in the correct folder." << endl;
        cout << "Check the project specification "
            << "for how to set up your project." << endl;
    }
    else {
        cout << "Project set up correctly, file opened." << endl;
    }

    return;
}
