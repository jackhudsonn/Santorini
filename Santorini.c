#include <stdio.h>
#include "Santorini.h"

int get_move_score(int board[][BOARD_SIZE], int x, int y, int opponent_row, int opponent_col);

int end_game_check(int board[][BOARD_SIZE]);

void print_board(int board[][BOARD_SIZE], int player_row, int player_col, int opponent_row, int opponent_col,
                 int iterations);

int one_away(int new_cell_X, int new_cell_Y, int old_cell_X, int old_cell_Y);

int main(void) {
    // initialize board
    int board[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = START_LEVEL;
        }
    }
    print_board(board, INVALID, INVALID, INVALID, INVALID, INVALID);

    // starting game
    int computer_X_options[NUM_OF_POSSIBLE_MOVES];
    int computer_Y_options[NUM_OF_POSSIBLE_MOVES];
    int iterations = 0;

    // user prompted for first move
    int player_row;
    int player_col;

    do {
        printf("Enter your starting row and column, both numbers must be between 1 and 6 (inclusive):\n");
        scanf("%d %d", &player_row, &player_col);
    } while ((player_row < 1 || player_row > 6) || (player_col < 1 || player_col > 6));
    printf("\n");

    // computer first move
    int computer_row;
    int computer_col;

    if (player_row > 3) {
        computer_row = player_row - 1;
    } else {
        computer_row = player_row + 1;
    }
    computer_col = player_col;

    print_board(board, player_row, player_col, computer_row, computer_col, iterations);
    iterations++;

    while (TRUE) {
        // user prompted for a move
        int prev_player_row = player_row;
        int prev_player_col = player_col;
        do {
            printf("Enter your starting row and column, both numbers must be between 1 and 6 (inclusive):\n");
            scanf("%d %d", &player_row, &player_col);
        } while ((player_row < 1 || player_row > 6 || player_col < 1 || player_col > 6) || // out of bounds
                 (player_row == computer_row && player_col == computer_col) || // computer in the way
                 (!one_away(player_row, player_col, prev_player_row, prev_player_col)));
        printf("\n");


        // init stop: boolean array terminates necessary conditions
        // inner if-statements do not execute when extending line hits an edge or another player
        // outer loop terminates when line extensions are done in all directions
        int stop[9] = {FALSE};

        for (int i = 1; !stop[ALL]; i++) {
            // update player northern cells
            if (player_row - 1 - i >= 0 && !stop[NORTH]) {
                if (player_row - i == computer_row && player_col == computer_col) {
                    stop[NORTH] = TRUE;
                } else if (board[player_row - 1 - i][player_col - 1] < MAX_LEVEL) {
                    board[player_row - 1 - i][player_col - 1]++;
                }
            } else {
                stop[NORTH] = TRUE;
            }

            // update player eastern cells
            if (player_col - 1 + i < BOARD_SIZE && !stop[EAST]) {
                if (player_col + i == computer_col && player_row == computer_row) {
                    stop[EAST] = TRUE;
                } else if (board[player_row - 1][player_col - 1 + i] < MAX_LEVEL) {
                    board[player_row - 1][player_col - 1 + i]++;
                }
            } else {
                stop[EAST] = TRUE;
            }

            // update player southern cells
            if (player_row - 1 + i < BOARD_SIZE && !stop[SOUTH]) {
                if (player_row + i == computer_row && player_col == computer_col) {
                    stop[SOUTH] = TRUE;
                } else if (board[player_row - 1 + i][player_col - 1] < MAX_LEVEL) {
                    board[player_row - 1 + i][player_col - 1]++;
                }
            } else {
                stop[SOUTH] = TRUE;
            }

            // update player western cells
            if (player_col - 1 - i >= 0 && !stop[WEST]) {
                if (player_col - i == computer_col && player_row == computer_row) {
                    stop[WEST] = TRUE;
                } else if (board[player_row - 1][player_col - 1 - i] < MAX_LEVEL) {
                    board[player_row - 1][player_col - 1 - i]++;
                }
            } else {
                stop[WEST] = TRUE;
            }

            // update player north-eastern cells
            if (player_row - 1 - i >= 0 && player_col - 1 + i < BOARD_SIZE && !stop[NORTH_EAST]) {
                if (player_row - i == computer_row && player_col + i == computer_col) {
                    stop[NORTH_EAST] = TRUE;
                } else if (board[player_row - 1 - i][player_col - 1 + i] < MAX_LEVEL) {
                    board[player_row - 1 - i][player_col - 1 + i]++;
                }
            } else {
                stop[NORTH_EAST] = TRUE;
            }

            // update player north-western cells
            if (player_row - 1 - i >= 0 && player_col - 1 - i >= 0 && !stop[NORTH_WEST]) {
                if (player_row - i == computer_row && player_col - i == computer_col) {
                    stop[NORTH_WEST] = TRUE;
                } else if (board[player_row - 1 - i][player_col - 1 - i] < MAX_LEVEL) {
                    board[player_row - 1 - i][player_col - 1 - i]++;
                }
            } else {
                stop[NORTH_WEST] = TRUE;
            }

            // update player south-eastern cells
            if (player_row - 1 + i < BOARD_SIZE && player_col - 1 + i < BOARD_SIZE && !stop[SOUTH_EAST]) {
                if (player_row + i == computer_row && player_col + i == computer_col) {
                    stop[SOUTH_EAST] = TRUE;
                } else if (board[player_row - 1 + i][player_col - 1 + i] < MAX_LEVEL) {
                    board[player_row - 1 + i][player_col - 1 + i]++;
                }
            } else {
                stop[SOUTH_EAST] = TRUE;
            }

            // update player south-western cells
            if (player_row - 1 + i < BOARD_SIZE && player_col - 1 - i >= 0 && !stop[SOUTH_WEST]) {
                if (player_row + i == computer_row && player_col - i == computer_col) {
                    stop[SOUTH_WEST] = TRUE;
                } else if (board[player_row - 1 + i][player_col - 1 - i] < MAX_LEVEL) {
                    board[player_row - 1 + i][player_col - 1 - i]++;
                }
            } else {
                stop[SOUTH_WEST] = TRUE;
            }

            // end loop condition
            if (stop[NORTH] && stop[EAST] && stop[SOUTH] && stop[WEST] && stop[NORTH_EAST] && stop[NORTH_WEST] &&
                stop[SOUTH_EAST] && stop[SOUTH_WEST]) {
                stop[ALL] = TRUE;
            }
        }

        // display state are check for win
        print_board(board, player_row, player_col, computer_row, computer_col, iterations);
        if(end_game_check(board) == 1) {
            return 0;
        }
        iterations++;

        // get computer options
        for (int x = computer_row - 1, i = 0; x < computer_row + 2; x++) {
            for (int y = computer_col - 1; y < computer_col + 2; y++, i++) {
                if (x <= 0 || y <= 0 || x > BOARD_SIZE || y > BOARD_SIZE ||
                    (x == computer_row && y == computer_col) ||
                    (x == player_row && y == player_col)) {
                    computer_X_options[i] = BAD_MOVE;
                    computer_Y_options[i] = BAD_MOVE;
                } else {
                    computer_X_options[i] = x;
                    computer_Y_options[i] = y;
                }
            }
        }

        // find the best move
        int max_score = INVALID;
        int max_score_i = INVALID;

        for (int i = 0; i < NUM_OF_POSSIBLE_MOVES; i++) {
            int score = get_move_score(board, computer_X_options[i], computer_Y_options[i], player_row, player_col);
            if (score > max_score) {
                max_score = score;
                max_score_i = i;
            }
        }

        if (max_score_i == INVALID) {
            printf("ERROR!");
            return 1;
        } else {
            computer_row = computer_X_options[max_score_i];
            computer_col = computer_Y_options[max_score_i];
        }

        // reset values to FALSE for computer use of the stop "boolean" array
        for (int i = 0; i < NUM_OF_POSSIBLE_MOVES; i++) {
            stop[i] = FALSE;
        }

        for (int i = 1; !stop[ALL]; i++) {
            // update computer northern cells
            if (computer_row - 1 - i >= 0 && !stop[NORTH]) {
                if (computer_row - i == player_row && player_col == computer_col) {
                    stop[NORTH] = TRUE;
                } else if (board[computer_row - 1 - i][computer_col - 1] > 0) {
                    board[computer_row - 1 - i][computer_col - 1]--;
                }
            } else {
                stop[NORTH] = TRUE;
            }

            // update computer eastern cells
            if (computer_col - 1 + i < BOARD_SIZE && !stop[EAST]) {
                if (computer_col + i == player_col && player_row == computer_row) {
                    stop[EAST] = TRUE;
                } else if (board[computer_row - 1][computer_col - 1 + i] > 0) {
                    board[computer_row - 1][computer_col - 1 + i]--;
                }
            } else {
                stop[EAST] = TRUE;
            }

            // update computer southern cells
            if (computer_row - 1 + i < BOARD_SIZE && !stop[SOUTH]) {
                if (computer_row + i == player_row && player_col == computer_col) {
                    stop[SOUTH] = TRUE;
                } else if (board[computer_row - 1 + i][computer_col - 1] > 0) {
                    board[computer_row - 1 + i][computer_col - 1]--;
                }
            } else {
                stop[SOUTH] = TRUE;
            }

            // update computer western cells
            if (computer_col - 1 - i >= 0 && !stop[WEST]) {
                if (computer_col - i == player_col && player_row == computer_row) {
                    stop[WEST] = TRUE;
                } else if (board[computer_row - 1][computer_col - 1 - i] > 0) {
                    board[computer_row - 1][computer_col - 1 - i]--;
                }
            } else {
                stop[WEST] = TRUE;
            }

            // update computer north-eastern cells
            if (computer_row - 1 - i >= 0 && computer_col - 1 + i < BOARD_SIZE && !stop[NORTH_EAST]) {
                if (computer_row - i == player_row && computer_col + i == player_col) {
                    stop[NORTH_EAST] = TRUE;
                } else if (board[computer_row - 1 - i][computer_col - 1 + i] > 0) {
                    board[computer_row - 1 - i][computer_col - 1 + i]--;
                }
            } else {
                stop[NORTH_EAST] = TRUE;
            }

            // update computer north-western cells
            if (computer_row - 1 - i >= 0 && computer_col - 1 - i >= 0 && !stop[NORTH_WEST]) {
                if (computer_row - i == player_row && computer_col - i == player_col) {
                    stop[NORTH_WEST] = TRUE;
                } else if (board[computer_row - 1 - i][computer_col - 1 - i] > 0) {
                    board[computer_row - 1 - i][computer_col - 1 - i]--;
                }
            } else {
                stop[NORTH_WEST] = TRUE;
            }

            // update computer south-eastern cells
            if (computer_row - 1 + i < BOARD_SIZE && computer_col - 1 + i < BOARD_SIZE && !stop[SOUTH_EAST]) {
                if (computer_row + i == player_row && computer_col + i == player_col) {
                    stop[SOUTH_EAST] = TRUE;
                } else if (board[computer_row - 1 + i][computer_col - 1 + i] > 0) {
                    board[computer_row - 1 + i][computer_col - 1 + i]--;
                }
            } else {
                stop[SOUTH_EAST] = TRUE;
            }

            // update computer south-western cells
            if (computer_row - 1 + i < BOARD_SIZE && computer_col - 1 - i >= 0 && !stop[SOUTH_WEST]) {
                if (computer_row + i == player_row && computer_col - i == player_col) {
                    stop[SOUTH_WEST] = TRUE;
                } else if (board[computer_row - 1 + i][computer_col - 1 - i] > 0) {
                    board[computer_row - 1 + i][computer_col - 1 - i]--;
                }
            } else {
                stop[SOUTH_WEST] = TRUE;
            }

            // update computer northern cells
            if (stop[NORTH] && stop[EAST] && stop[SOUTH] && stop[WEST] && stop[NORTH_EAST] && stop[NORTH_WEST] &&
                stop[SOUTH_EAST] && stop[SOUTH_WEST]) { // break condition
                stop[ALL] = TRUE;
            }
        }

        // display state are check for win
        print_board(board, player_row, player_col, computer_row, computer_col, iterations);
        if(end_game_check(board) == 1) {
            return 0;
        }
        iterations++;
    }
}

int get_move_score(int board[][BOARD_SIZE], int x, int y, int opponent_row, int opponent_col) {
    if (x == BAD_MOVE || y == BAD_MOVE) {
        return BAD_MOVE;
    } else {
        int score = 0;
        int stop[9] = {FALSE};

        // get score
        for (int i = 1; !stop[ALL]; i++) {
            // northern cell score
            if (x - 1 - i >= 0 && !stop[NORTH]) {
                if (x - i == opponent_row && y == opponent_col) {
                    stop[NORTH] = TRUE;
                } else {
                    score += board[x - 1 - i][y - 1];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) { // extra point awarded for MAX_LEVEL cells
                        score++;
                    }
                }
            } else {
                stop[NORTH] = TRUE;
            }

            // eastern cell score
            if (y - 1 + i < BOARD_SIZE && !stop[EAST]) {
                if (y + i == opponent_col && x == opponent_row) {
                    stop[EAST] = TRUE;
                } else {
                    score += board[x - 1][y - 1 + i];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[EAST] = TRUE;
            }

            // southern cell score
            if (x - 1 + i < BOARD_SIZE && !stop[SOUTH]) {
                if (x + i == opponent_row && y == opponent_col) {
                    stop[SOUTH] = TRUE;
                } else {
                    score += board[x - 1 + i][y - 1];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[SOUTH] = TRUE;
            }

            // western cell score
            if (y - 1 - i >= 0 && !stop[WEST]) {
                if (y - i == opponent_col && x == opponent_row) {
                    stop[WEST] = TRUE;
                } else {
                    score += board[x - 1][y - 1 - i];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[WEST] = TRUE;
            }

            // north-eastern cell score
            if (x - 1 - i >= 0 && y - 1 + i < BOARD_SIZE && !stop[NORTH_EAST]) {
                if (x - i == opponent_row && y + i == opponent_col) {
                    stop[NORTH_EAST] = TRUE;
                } else {
                    score += board[x - 1 - i][y - 1 + i];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[NORTH_EAST] = TRUE;
            }

            // north-western cell score
            if (x - 1 - i >= 0 && y - 1 - i >= 0 && !stop[NORTH_WEST]) {
                if (x - i == opponent_row && y - i == opponent_col) {
                    stop[NORTH_WEST] = TRUE;
                } else {
                    score += board[x - 1 - i][y - 1 - i];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[NORTH_WEST] = TRUE;
            }

            // south-eastern cell score
            if (x - 1 + i < BOARD_SIZE && y - 1 + i < BOARD_SIZE && !stop[SOUTH_EAST]) {
                if (x + i == opponent_row && y + i == opponent_col) {
                    stop[SOUTH_EAST] = TRUE;
                } else {
                    score += board[x - 1 + i][y - 1 + i];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[SOUTH_EAST] = TRUE;
            }

            // south-western cell score
            if (x - 1 + i < BOARD_SIZE && y - 1 - i >= 0 && !stop[SOUTH_WEST]) {
                if (x + i == opponent_row && y - i == opponent_col) {
                    stop[SOUTH_WEST] = TRUE;
                } else {
                    score += board[x - 1 + i][y - 1 - i];
                    if (board[x - 1][y - 1 + i] == MAX_LEVEL) {
                        score++;
                    }
                }
            } else {
                stop[SOUTH_WEST] = TRUE;
            }

            if (stop[NORTH] && stop[EAST] && stop[SOUTH] && stop[WEST] && stop[NORTH_EAST] && stop[NORTH_WEST] &&
                stop[SOUTH_EAST] && stop[SOUTH_WEST]) { // break condition
                stop[ALL] = TRUE;
            }
        }
        return score;
    }
}


int end_game_check(int board[][BOARD_SIZE]) {
    int player_counter = 0;
    int computer_counter = 0;

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == MAX_LEVEL) {
                player_counter++;
            } else if (board[row][col] == MIN_LEVEL) {
                computer_counter++;
            }
        }
    }

    if (computer_counter >= 10 && player_counter >= 10) {
        if (computer_counter == player_counter) {
            printf("YOU TIED!\n");
            return 1;
        } else if (computer_counter > player_counter) {
            printf("YOU LOSE!\n");
            return 1;
        } else {
            printf("YOU WIN!\n");
            return 1;
        }
    } else if (computer_counter >= 10) {
        printf("YOU LOSE!\n");
        return 1;
    } else if (player_counter >= 10) {
        printf("YOU WIN!\n");
        return 1;
    }
    return 0;
}

void print_board(int board[][BOARD_SIZE], int player_row, int player_col, int opponent_row, int opponent_col,
                 int iterations) {
    if (iterations == 0) {
        printf("YOU ARE PLAYER (P), PLAYING AGAINST COMPUTER (A)\n");
    } else if (iterations % 2 == 1) {
        printf("PLAYER | TURN #%d\n", iterations);
    } else if (iterations % 2 == 0) {
        printf("COMPUTER | TURN #%d\n", iterations);
    } else {
        printf("WELCOME TO JACK HUDSON'S GAME OF SANTORINI\n");
    }

    printf("   1 2 3 4 5 6\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d  ", i + 1);
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i + 1 == player_row && j + 1 == player_col) {
                printf("P ");
            } else if (i + 1 == opponent_row && j + 1 == opponent_col) {
                printf("A ");
            } else {
                printf("%d ", board[i][j]);
            }
            //printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int one_away(int new_cell_X, int new_cell_Y, int old_cell_X, int old_cell_Y) {
    int x = new_cell_X - old_cell_X;
    int y = new_cell_Y - old_cell_Y;

    if (x < 0) {
        x *= -1;
    }
    if (y < 0) {
        y *= -1;
    }

    return (x == 0 && y == 1) || (x == 1 && y == 1) || (x == 1 && y == 0);
}