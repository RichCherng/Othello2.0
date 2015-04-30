#include "OthelloExceptions.h"
#include "OthelloBoard.h"
#include "OthelloView.h"
#include "OthelloMove.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]) {
   OthelloBoard board; // the state of the game board
   OthelloView v(&board); // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   vector<OthelloMove *> possMoves; // a holder for possible moves
   OthelloMove *m = nullptr;
   do {
      cout << v << endl;
      board.GetPossibleMoves(&possMoves);
      cout << "Board Possible Move: ";
      for (OthelloMove* i : possMoves) {
         cout << (string)(*i) << " ";
      }
      cout << endl;
      if (board.GetNextPlayer() > 0) {

         cout << "Black Turn" << endl;
      }
      else
         cout << "White Turn" << endl;
      string command;
      getline(std::cin, command);
      stringstream ss(command);
      ss >> command;
      if (command == "move") {
         if (!ss.eof()) {
            ss >> command;
            m = board.CreateMove();
            try {
               *m = command;
               bool valid = false;

               for (OthelloMove* i : possMoves) {
                  if ((*i) == (*m)) {
                     valid = true;
                     board.ApplyMove(m);
                  }
               }
               if (!valid) {
                  delete m;
                  cout << "Invalid move" << endl;
               }
            }
            catch (OthelloException &e) {
               delete m;
               cout << e.what() << endl;
            }
         }
         else
            cout << "Invalid input" << endl;
      }

      if (command == "undo") {
         if (!ss.eof()) {
            ss >> command;
            istringstream buffer(command);
            int undoMove;
            buffer >> undoMove;
            for (int i = 0; i < undoMove; i++) {
               board.UndoLastMove();
            }
         }
      }
      if (command == "showValue") {
         cout << "Board Value: " << board.GetValue() << endl;
      }
      if (command == "showHistory") {
         vector<OthelloMove*> lis(*(board.GetMoveHistory()));
         int turnCount = lis.size();
         for (int i = lis.size(); i > 0; i--) {
            if (i % 2 == 1) {
               cout << "Black ";
            }
            else
               cout << "White";
            cout << (string)(*lis[i - 1]) << endl;
         }
      }
      if (command == "quit") {
         break;
      }
      for (OthelloMove* i : possMoves) {
         delete i;
      }
      possMoves.clear();
   } while (!board.IsFinished());
   if (board.GetValue() > 0) {
      cout << "Black wins" << endl;
   }
   else
      cout << "White win!" << endl;
   system("pause");
}