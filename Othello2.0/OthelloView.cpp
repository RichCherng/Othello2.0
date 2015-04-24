#include "OthelloView.h"

using namespace std;

void OthelloView::PrintBoard(std::ostream &s) const {
   s << "- ";
   for (int i = 0; i < BOARD_SIZE; i++) {
      s << i << " ";
   }
   for (int row = 0; row < BOARD_SIZE; row++) {
      s << endl << row << " ";
      for (int col = 0; col < BOARD_SIZE; col++) {
         if (mOthelloBoard->mBoard[row][col] == 0)
            s << ". ";
         else if (mOthelloBoard->mBoard[row][col] == 1)
            s << "B ";
         else if (mOthelloBoard->mBoard[row][col] == -1)
            s << "W ";
      }
   }
   s << endl << endl;
}


std::ostream& operator<< (std::ostream &lhs, const OthelloView &rhs) {
   rhs.PrintBoard(lhs);
   return lhs;
}