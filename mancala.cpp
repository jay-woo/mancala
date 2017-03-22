#include <iostream>
using namespace std;

#define NUM_HOLES 14 // (6 regular holes + 1 score hole) * 2 players = 14
#define PLAYER1_SCORE_HOLE 0
#define PLAYER2_SCORE_HOLE 7

class MancalaBoard {
  int* board;

  public:
    MancalaBoard() {
      board = new int[NUM_HOLES];

      // Put 4 pieces in every hole, except for the score holes
      for (int i = 0; i < NUM_HOLES; i++) {
        if (i != PLAYER1_SCORE_HOLE && i != PLAYER2_SCORE_HOLE) {
          board[i] = 4;
        }
      }
    }

    // Play a game of mancala between two playerIsFirst
    void playGame() {
      bool playerIsFirst = true; // Is it the first player's turn?
      int playerInput;
      bool goAgain;

      printBoard();

      while (!isGameOver()) {
        if (playerIsFirst) {
          cout << "Player 1: Select a hole from 1 to 5." << endl;
        }
        else {
          cout << "Player 2: Select a hole from 8 to 12." << endl;
        }
        cin >> playerInput;
        goAgain = updateBoard(playerInput, playerIsFirst);

        if (!goAgain) {
          playerIsFirst = !playerIsFirst;
        }
      }
    }

    // Update the mancala board after a player has made a move
    //  Inputs;
    //    int hole: Index of the hole to take stones from
    //    bool playerIsFirst: Did the player start the game?
    //  Output:
    //    bool: True if the player may take another turn
    bool updateBoard(int hole, bool playerIsFirst) {
      bool isValid = checkValidMove(hole, playerIsFirst);
      if (!isValid) {
        cout << "Invalid move. Try a different hole." << endl;
        return false;
      }

      // Remove the stones
      int stones = board[hole];
      board[hole] = 0;

      // Goes around the board in a loop and deposits stones along the way
      while (stones > 0) {
        hole = (hole + 1) % NUM_HOLES;

        // Skip the hole if it's the opposite player's score hole
        if (playerIsFirst && hole == PLAYER2_SCORE_HOLE) {
          hole = (hole + 1) % NUM_HOLES;
        }
        else if (!playerIsFirst && hole == PLAYER1_SCORE_HOLE) {
          hole = (hole + 1) % NUM_HOLES;
        }

        board[hole] += 1;
        stones--;
      }

      printBoard();

      // Player goes again if they land in their own hole
      if (playerIsFirst && hole == PLAYER1_SCORE_HOLE) {
        return true;
      }
      else if (!playerIsFirst && hole == PLAYER2_SCORE_HOLE) {
        return true;
      }
      return false;
    }

    // Check if the move is valid for the given player
    //  Inputs;
    //    int hole: Index of the hole to take stones from
    //    bool playerIsFirst: Did the player start the game?
    //  Output:
    //    bool: True if the move is valid
    bool checkValidMove(int hole, bool playerIsFirst) {
      // Invalid if player picks hole on opposite side or from score hole
      if (playerIsFirst) {
        if (hole == PLAYER1_SCORE_HOLE || hole >= PLAYER2_SCORE_HOLE) {
          return false;
        }
      }
      else {
        if (hole == PLAYER2_SCORE_HOLE || hole < PLAYER2_SCORE_HOLE) {
          return false;
        }
      }

      return true;
    }

    // Print the current state of the board
    void printBoard() {
      cout << "\nCURRENT BOARD" << endl;
      cout << "Player 1's Side" << endl;
      for (int i = 0; i < PLAYER2_SCORE_HOLE; i++) {
        cout << board[i] << ' ';
      }

      cout << endl;
      for (int i = NUM_HOLES-1; i >= PLAYER2_SCORE_HOLE; i--) {
        cout << board[i] << ' ';
      }
      cout << "\nPlayer 2's Side\n\n";
    }

    // Check if the game has ended (if one player's side has been depleted)
    bool isGameOver() {
      for (int i = PLAYER1_SCORE_HOLE+1; i < PLAYER2_SCORE_HOLE; i++) {
        if (board[i] != 0) {
          return false;
        }
      }

      for (int i = PLAYER2_SCORE_HOLE+1; i < NUM_HOLES; i++) {
        if (board[i] != 0) {
          return false;
        }
      }

      return true;
    }
};

class Player {
  int score;

  public:
    void updateScore(int newScore) {
      score = newScore;
    }

    int getScore() {
      return score;
    }
};

int main() {
  MancalaBoard * b = new MancalaBoard();
  b->playGame();
  return 0;
}
