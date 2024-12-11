#include <iostream>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "color_class.hpp"
#include "dice_class.hpp"
#include "grid_class.hpp"
#include "logger_class.hpp"

using namespace std;

class Dice {
private:
    int sides;

public:
    Dice(int sides = 6) : sides(sides) { srand(time(0)); }
    int roll() { return rand() % sides + 1; }
};

class Grid {
private:
    int cells[3][3];

public:
    Grid() { 
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cells[i][j] = 0;
            }
        }
    }

    bool place_dice(int col, int value) {
        for (int row = 2; row >= 0; --row) {
            if (cells[row][col] == 0) {
                cells[row][col] = value;
                return true;
            }
        }
        return false; // Column is full
    }

    void remove_dice(int col, int value) {
        for (int row = 0; row < 3; ++row) {
            if (cells[row][col] == value) {
                cells[row][col] = 0;
                return;
            }
        }
    }

    int get_score() const {
        int score = 0;
        for (int col = 0; col < 3; ++col) {
            int col_score = 0;
            for (int row = 0; row < 3; ++row) {
                if (cells[row][col] != 0) {
                    col_score += cells[row][col];
                }
            }
            score += col_score;
        }
        return score;
    }

    void display_grid(int x, int y) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                mvprintw(y + row, x + col * 4, "%d", cells[row][col]);
            }
        }
    }

    bool is_full() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (cells[i][j] == 0) {
                    return false;
                }
            }
        }
        return true;
    }
};

class Player {
private:
    string name;
    Grid player_grid;
    int score;

public:
    Player(string name) : name(name), score(0) {}

    string get_name() const { return name; }
    int get_score() const { return player_grid.get_score(); }

    bool take_turn(Dice &dice) {
        int roll = dice.roll();
        mvprintw(0, 0, "%s rolled a %d!", name.c_str(), roll);
        refresh();

        int col;
        while (true) {
            mvprintw(1, 0, "Enter column (0-2) to place the die: ");
            refresh();
            char input = getch();
            if (input >= '0' && input <= '2') {
                col = input - '0';
                if (player_grid.place_dice(col, roll)) {
                    break; // valid move, exit loop
                }
            }
            mvprintw(2, 0, "Invalid move. Please enter a valid column (0-2).");
            attron(COLOR_PAIR(2)); // Use red color for error
            mvprintw(3, 0, "Column is full or invalid. Try again.");
            attroff(COLOR_PAIR(2)); // Reset color
            refresh();
        }
        return true;
    }

    void display_grid(int x, int y) { player_grid.display_grid(x, y); }

    Grid& get_grid() { return player_grid; } // Add this getter for the grid
};

class Game {
private:
    Player *players[2];
    Dice dice;
    int current_player;

public:
    Game(string player1_name, string player2_name) {
        players[0] = new Player(player1_name);
        players[1] = new Player(player2_name);
        current_player = 0;
    }

    ~Game() {
        delete players[0];
        delete players[1];
    }

    void play() {
        initscr();
        start_color();
        use_default_colors();

        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);

        while (true) {
            clear();
            mvprintw(0, 0, "Player 1: %s | Score: %d", players[0]->get_name().c_str(), players[0]->get_score());
            mvprintw(1, 0, "Player 2: %s | Score: %d", players[1]->get_name().c_str(), players[1]->get_score());

            players[0]->display_grid(0, 3);
            players[1]->display_grid(20, 3);

            mvprintw(10, 0, "%s's turn!", players[current_player]->get_name().c_str());
            refresh();

            if (!players[current_player]->take_turn(dice)) {
                continue;
            }

            if (is_game_over()) {
                end_game();
                break;
            }

            current_player = 1 - current_player;
        }

        endwin();
    }

    bool is_game_over() {
        // Game over if the grid is full
        return players[0]->get_score() + players[1]->get_score() == 18 || players[0]->get_grid().is_full() || players[1]->get_grid().is_full();
    }

    void end_game() {
        clear();
        int score1 = players[0]->get_score();
        int score2 = players[1]->get_score();

        if (score1 > score2) {
            mvprintw(0, 0, "Player 1 (%s) wins with %d points!", players[0]->get_name().c_str(), score1);
        } else if (score2 > score1) {
            mvprintw(0, 0, "Player 2 (%s) wins with %d points!", players[1]->get_name().c_str(), score2);
        } else {
            mvprintw(0, 0, "It's a tie! Both players scored %d points!", score1);
        }
        refresh();
        getch();
    }
};

int main() {
    // Initialize ncurses
    initscr();
    cbreak();  // Disable line buffering
    noecho();  // Don't show input
    curs_set(0); // Hide the cursor

    // Initialize color pairs
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);

    // Get player names
    string player1_name, player2_name;
    mvprintw(0, 0, "Enter name for Player 1: ");
    refresh();
    char name1[50];
    getstr(name1);
    player1_name = name1;

    mvprintw(1, 0, "Enter name for Player 2: ");
    refresh();
    char name2[50];
    getstr(name2);
    player2_name = name2;

    // Create the game object
    Game game(player1_name, player2_name);

    // Start the game
    game.play();

    // End ncurses
    endwin();
    return 0;
}