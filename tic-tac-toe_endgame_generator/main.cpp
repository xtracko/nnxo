/**
  * Tic tac toe endgame generator
  * @author Marie Drábková
  *
  * Generates all valid terminal boards.
  * Both x and o could have started the game.
  * Doesn't exclude symmetrical solutions.
  * x is encoded as "1", o as "-1", blank as "0"
  *
  * output format:
  *     top-left top-middle top-right middle-left
  *     middle-middle middle-right bottom-left bottom-middle
  *     bottom-right, x_has_won o_has_won draw
  *
  */

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>

using namespace std;

/**
 * @brief x_won
 * @param board
 * @return true, if there are 3 xs in a row
 */
bool x_won(std::vector<int> board) {
    if ((board[0]==1 && board[4]==1 && board[8]==1) ||
            (board[2]==1 && board[4]==1 && board[6]==1) ||
            (board[0]==1 && board[3]==1 && board[6]==1) ||
            (board[1]==1 && board[4]==1 && board[7]==1) ||
            (board[2]==1 && board[5]==1 && board[8]==1) ||
            (board[0]==1 && board[1]==1 && board[2]==1) ||
            (board[3]==1 && board[4]==1 && board[5]==1) ||
            (board[6]==1 && board[7]==1 && board[8]==1)) {
        return true;
    }
    return false;
}

/**
 * @brief o_won
 * @param board
 * @return true, if there are 3 os in a row
 */
bool o_won(std::vector<int> board){
    if ((board[0]==-1 && board[4]==-1 && board[8]==-1) ||
            (board[2]==-1 && board[4]==-1 && board[6]==-1) ||
            (board[0]==-1 && board[3]==-1 && board[6]==-1) ||
            (board[1]==-1 && board[4]==-1 && board[7]==-1) ||
            (board[2]==-1 && board[5]==-1 && board[8]==-1) ||
            (board[0]==-1 && board[1]==-1 && board[2]==-1) ||
            (board[3]==-1 && board[4]==-1 && board[5]==-1) ||
            (board[6]==-1 && board[7]==-1 && board[8]==-1)) {
        return true;
    }
    return false;
}

/**
 * @brief check_if_valid
 * @param board
 * @return true, if board is valid
 *
 * 1) it's at least 5th turn
 * 2) there is either same number of xs and os, or there is one more x than o
 * 3) only one of the players has won
 * 4) one of the players has one if it's not 9th turn yet
 * 5) x cannot win in o's turn
 * 6) o cannot win in x's turn
 */
bool check_if_valid(std::vector<int> board) {
    int turn = 0;
    int sum = 0;
    for (int i = 0; i < 9; i++) {
        if (board[i] != 0) turn++;
        sum += board[i];
    }

    bool x_has_won = x_won(board);
    bool o_has_won = o_won(board);

    if (turn < 5) return false; // 1) it's at least 5th turn
    if (sum != 1 && sum != 0) return false; // 2) there is either same number of xs and os, or there is one more x than o
    if (x_has_won && o_has_won) return false; // 3) only one of the players has won
    if (turn != 9 && !o_has_won && !x_has_won) return false; // 4) one of the players has one if it's not 9th turn yet
    if (sum == 0 && x_has_won) return false; // 5) x cannot win in o's turn
    if (sum == 1 && o_has_won) return false; // 6) o cannot win in x's turn

    return true;
}

int main()
{
    int xwins = 0;
    int owins = 0;
    int draws = 0;
    std::vector<int> board;
    bool valid;
    int turn_5 = 0;
    int turn_6 = 0;
    int turn_7 = 0;
    int turn_8 = 0;
    int turn_9 = 0;

    int dividing_dummy = 0;
    int training_set_n = 0;
    int validation_set_n = 0;
    int testing_set_n = 0;

    // open file
    ofstream* output;
    ofstream output_training;
    output_training.open("output_training.txt");

    ofstream output_validation;
    output_validation.open("output_validation.txt");

    ofstream output_testing;
    output_testing.open("output_testing.txt");

    // check if open
    if (!output_training.is_open() || !output_validation.is_open() || !output_testing.is_open()) {
        cerr << "file couldn't open" << endl;
        return 1;
    }

    // create all possible boards, print valid boards to output file
    for (int i = 0; i < pow(3,9); i++) {
        int c = i;
        for (int j = 0; j < 9; j++) {
            board.push_back((c % 3) - 1);
            c /= 3;
        }

        valid = check_if_valid(board);

        bool x_has_won = x_won(board);
        bool o_has_won = o_won(board);
        int draw = 0;
        if (!x_has_won && !o_has_won) draw = 1;

        int turn = 0;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 0) turn++;
        }


        if (valid) {
            // count wins
            if (x_has_won) xwins++;
            if (o_has_won) owins++;
            if (draw == 1) draws++;

            // count turns
            switch(turn) {
                case 5:
                    turn_5++;
                    break;
                case 6:
                    turn_6++;
                    break;
                case 7:
                    turn_7++;
                    break;
                case 8:
                    turn_8++;
                    break;
                case 9:
                    turn_9++;
                    break;
            }


            switch(dividing_dummy) {
                case 0:
                    output = &output_training;
                    training_set_n++;
                    break;
                case 1:
                    output = &output_validation;
                    validation_set_n++;
                    break;
                case 2:
                    output = &output_training;
                    training_set_n++;
                    break;
                case 3:
                    output = &output_testing;
                    testing_set_n++;
                    break;
                case 4:
                    output = &output_training;
                    training_set_n++;
                    break;
            }


            // print board
            for (int k = 0; k < 9; k++) {
               *output << board[k];
               if (k != 8) *output << " ";
            }

            // print who has won or draw
            *output <<", " << x_has_won << " ";
            *output << o_has_won << " ";
            *output << draw << endl;

            dividing_dummy = (dividing_dummy + 1) % 5;
        }
        board.clear();
    }

    output->close();
    output_training.close();
    output_validation.close();
    output_testing.close();

    // print how many time has x or o won, or the game ended in draw
    cout << xwins + owins + draws << " valid games, " << "x has won "<< xwins << " times, o has won  "
         << owins << " times, " << draws  << " draws\n" << endl;

    cout << "5th turn: " << turn_5 << "\n6th turn: " << turn_6 << "\n7th turn: " << turn_7 << "\n8th turn: "
            << turn_8 << "\n9th turn: " << turn_9 << endl;


    return 0;
}

