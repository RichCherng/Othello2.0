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
   // Initialization
   OthelloBoard board; // the state of the game board
   OthelloView v(&board); // a View for outputting the board via operator<<
   string userInput; // a string to hold the user's command choice
   vector<OthelloMove *> possMoves; // a holder for possible moves
   OthelloMove *m = nullptr;

   
   // Start with this DEBUGGING CODE to make sure your basic OthelloMove and 
   // OthelloBoard classes work, then remove it when you are ready to work
   // on the real main.

   /*
   cout << "Initial board:" << endl;
   cout << v << endl;
   OthelloMove *m = board.CreateMove();
   *m = "(3, 2)";
   cout << "Applying the move " << (string)(*m) << endl;
   board.ApplyMove(m);
   cout << endl << v << endl; // should show a changed board.

   m = board.CreateMove();
   *m = "(4, 2)";
   cout << "Applying the move " << (string)(*m) << endl;
   board.ApplyMove(m);
   cout << endl << v << endl;

   m = board.CreateMove();
   *m = "(5, 2)";
   cout << "Applying the move " << (string)(*m) << endl;
   board.ApplyMove(m);
   cout << endl << v << endl;
   // END OF DEBUGGING CODE
   */




   // Main loop
   do {
	   // Print the game board using the OthelloView object
      cout << v << endl;
      // Print all possible moves
      board.GetPossibleMoves(&possMoves);
      for (OthelloMove* i : possMoves) {
         cout << (string)(*i) << " ";
      }
      cout << endl;
      if (board.GetNextPlayer() > 0) {

         cout << "Black Turn" << endl;
      }
      else
         cout << "White Turn" << endl;
      // Ask to input a command
      string command;
      getline(std::cin, command);
      stringstream ss(command);
      ss >> command;
      if (command == "move") {
         if (!ss.eof()) {
            ss >> command;
            m = board.CreateMove();
            try { *m = command; 
            }
            catch (OthelloException &e) {
               delete m;
               cout << e.what() << endl;
            }
            
            bool valid = false;
            for (OthelloMove* i : possMoves) {
               if ((*i) == (*m)) {
                  valid = true;
                  board.ApplyMove(m);
               }
            }
            if (!valid && !m->IsPass())
               cout << "Invalid move" << endl;
            else if (m->IsPass()){
               board.ApplyMove(m);
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
     /* if (command == "pass") {
         *m = command;
         board.ApplyMove(m);
      }*/
      if (command == "showHistory") {
         
         /*for (OthelloMove* m : (*board.GetMoveHistory())) {
            cout << (string)(*m) << endl;
         }*/
         vector<OthelloMove*> lis(*(board.GetMoveHistory()));
         for (int i = lis.size(); i > 0; i--) {
            cout << (string)(*lis[i-1]) << endl;
         }
      }

      if (command == "quit") {
         break;
      }

     for (OthelloMove* i : possMoves) {
         delete i;
      }
      possMoves.clear();

      // Command loop:
         // move (r,c)
         // undo n
         // showValue
         // showHistory
         // quit
      
   } while (!board.IsFinished()); 
}