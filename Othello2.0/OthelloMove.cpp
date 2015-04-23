
#include <sstream>
#include "OthelloMove.h"
#include "OthelloBoard.h"
#include "OthelloExceptions.h"

int OthelloMove::mOnHeap = 0;

using namespace std;

OthelloMove::OthelloMove()
   :mRow(-1), mCol(-1) {

}

OthelloMove::OthelloMove(int row, int col)
   : mRow(row), mCol(col) {

}

OthelloMove& OthelloMove::operator=(const std::string &move) {
   if (move == "pass") {
      mRow = -1;
      mCol = -1;
      return *this;
   }
   else {
      stringstream ss(move);
      char temp;
      ss >> temp >> mRow >> temp >> mCol >> temp;
      if (OthelloBoard::InBounds(mRow, mCol) ){
         return *this;
      }
      throw OthelloException("Fail BRuh!!!");
   }
}

bool operator==(const OthelloMove &lhs, const OthelloMove &rhs) {
   return (lhs.mRow == rhs.mRow) && (lhs.mCol == rhs.mCol);
}

OthelloMove::operator std::string() const {
   if (mRow == -1 && mCol == -1) {
      //cout << mRow << endl << mCol << endl;
      return "pass";
   }
   std::ostringstream s;
   s << "(" << mRow << ", " << mCol << ")";
   return s.str();
}


